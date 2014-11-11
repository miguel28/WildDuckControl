/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File PS_PAD.h

PlayStation Controller library
* Copyright (c) 2013 Hiroshi Suga - 2014 Miguel Silva

This program has been created by using mbed runtime libraries
for the platform FRDM-KL25Z in a offline project managed by
arm-gcc compiler.

For more details see (http://www.mbed.org) for a gerneal
overview. And for the development se (http://developer.mbed.org/)

*This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>
******************************************************************/

#include "PS_PAD.h" //// Include the headers of PS_PAD.h also the definition of the class

#ifdef __DEBUG__ //// If the debug flag is on, construct a new serial pc port.
Serial pc(USBTX, USBRX);
#endif

/* public default constructor it takes the pin names for a software SPI */
PS_PAD::PS_PAD(PinName mosi, PinName miso, PinName sck, PinName cs) : _clk(sck), _mosi(mosi), _miso(miso), _cs(cs) {
	
	/* Initializes the initial State of all pins */
	_clk = 1;
	_mosi = 0;
	_cs = 1;

	/* set the vibration to 0*/
	_vib1 = 0;
	_vib2 = 0;

	/* Set not connected jet*/
	_connected = false;
}

/* Software SPI implementation
	uint8_t PS_PAD::SendSPI(uint8_t data)
	Takes  1 argument as data to send.
*/
uint8_t PS_PAD::SendSPI(uint8_t data)
{
	char i; //// fo loop iteration control
	uint8_t retData = 0x00; //// Received byte set to 0x00 (initial value)
	for (i = 0; i < 8; i++) //// Create a 8 cycles loop (for every bit on the word)
	{
		uint8_t sbit = (data >> i) & 0x01; //// Take the next one bit by using bitwise i positions 
		_mosi = sbit; //// set the master output of the selected bit of the data to send
		_clk = 0;     //// Send the SCK to dominant state 
		wait_us(10);  //// only for 10us

		retData |= (_miso << i); //// then retrieve the state of the miso pin by 
								 //// using bitwise to store the correct data
		_clk = 1;                //// put the SCK to a recesive state
		wait_us(10);			 //// wait 10 us to get the syncronization of the controller
								 //// and also complete the spi Cycle.
	} //// loop 8 times
	return retData; //// return the result data
}

int PS_PAD::init() {
	/* PS2 controller Initialization commands*/
	const char enter_config_mode[5] = { 0x01, 0x43, 0x00, 0x01, 0x00 };
	const char enable_analog_mode[9] = { 0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
	const char enable_vibration[9] = { 0x01, 0x4d, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff };
	const char exit_config_mode[9] = { 0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
	char buf[10];

	/* Frist send the "Enter configuration" command*/
	send(enter_config_mode, 5, buf);
	/* Check the resoponse of the controller*/
	if (buf[2] == 0xff) { //// if the 3rd byte if equal to 0xff something wrong happened in the communication
		return -1;        //// then returns -1, to indicates an fatal error
	}
	wait_ms(16); //// wait 16 ms
	send(enable_analog_mode, 9, buf); //// send anaglog sticks enabled
	wait_ms(16); //// wait 16 ms
	send(enable_vibration, 9, buf);   //// send vibration mode enabled
	wait_ms(16); //// wait 16 ms
	send(exit_config_mode, 9, buf);   //// send exit configuration command
	wait_ms(16); //// wait 16 ms
	return 0;
}

/* This method sends the command o retreive the new state of a PS2 controller*/
int PS_PAD::poll() {
	/* Command array for a new poll state */
	const char poll_command[9] = { 0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	int i; //// for loop iterator control
	char cmd[10], buf[10]; //// send reponse buffers

	//// copy the poll command to cmd buffer
	memcpy(cmd, poll_command, 9);

	/* set the vibration intensities*/
	cmd[3] = _vib1;
	cmd[4] = _vib2;

	/* Then , send the contructed poll command to the controller*/
	send(cmd, 9, buf);

	/* if we get a 0x5a we have a comunication error*/
	if (buf[2] != 0x5a) {
		return -1;   //// then returns -1 to indicates an error
	}

	/* retrieve a result data and stores in a _pad buffer*/
	for (i = 0; i < 6; i++) {
		_pad[i] = buf[3 + i];
	}
	//// Also set connected to true
	_connected = true;
	return 0; //// function exits success!
}

/* int read method 
   takes TYPE parameters (enum)
   */
int PS_PAD::read(TYPE t) {
	//// if the controller isn't connected return 0 or 128 if t is an axis
	if (!_connected) 
	{
		if (t <= BUTTONS)
			return 0;
		else 
			return 0x80; //// Center value of axis
	}

	//// Depends of the t request state returns the value of the
	//// last poll data retreived from the controller.
	switch (t) {
	case PAD_LEFT:
		return _pad[0] & 0x80 ? 0 : 1;
	case PAD_BOTTOM:
		return _pad[0] & 0x40 ? 0 : 1;
	case PAD_RIGHT:
		return _pad[0] & 0x20 ? 0 : 1;
	case PAD_TOP:
		return _pad[0] & 0x10 ? 0 : 1;
	case PAD_START:
		return _pad[0] & 0x08 ? 0 : 1;
	case ANALOG_LEFT:
		return _pad[0] & 0x04 ? 0 : 1;
	case ANALOG_RIGHT:
		return _pad[0] & 0x02 ? 0 : 1;
	case PAD_SELECT:
		return _pad[0] & 0x01 ? 0 : 1;
	case PAD_SQUARE:
		return _pad[1] & 0x80 ? 0 : 1;
	case PAD_X:
		return _pad[1] & 0x40 ? 0 : 1;
	case PAD_CIRCLE:
		return _pad[1] & 0x20 ? 0 : 1;
	case PAD_TRIANGLE:
		return _pad[1] & 0x10 ? 0 : 1;
	case PAD_R1:
		return _pad[1] & 0x08 ? 0 : 1;
	case PAD_L1:
		return _pad[1] & 0x04 ? 0 : 1;
	case PAD_R2:
		return _pad[1] & 0x02 ? 0 : 1;
	case PAD_L2:
		return _pad[1] & 0x01 ? 0 : 1;
	case BUTTONS:
		return ~((_pad[1] << 8) | _pad[0]) & 0xffff;
	case ANALOG_RX:
		return _pad[2] - 0x80;
	case ANALOG_RY:
		return _pad[3] - 0x80;
	case ANALOG_LX:
		return _pad[4] - 0x80;
	case ANALOG_LY:
		return _pad[5] - 0x80;
	}
	return 0;
}

/* int PS_PAD::vibration(int v1, int v2)
   Takes int argument v1
   Takes int argument v2
  
   Sets the controller vibration to a internal variables
   to send again in the next poll command.
*/
int PS_PAD::vibration(int v1, int v2) {
	_vib1 = v1 ? 1 : 0;
	if (v2 < 0) v2 = 0;
	if (v2 > 0xff) v2 = 0;
	_vib2 = v2;
	poll();
	return 0;
}

/*
   int PS_PAD::send(const char *cmd, int len, char *dat) 

   Takes 1 char command array
   Takes 1 int len to define the lenght of the command arrat
   Takes 1 pointes char * to store the reteived data.

   This functions handles the data flow of the comunication 
   between the master and the PS2 controller.
*/
int PS_PAD::send(const char *cmd, int len, char *dat) {
	int i; //// for loop interator

	_cs = 0; //// Set the chip select to 0 on a dominant state
			 //// to enable the comunication
			 //// between the PS2 and the master.
	wait_us(20); //// Wait 20 us
	for (i = 0; i < len; i++) //// for each *cmd byte send the current interator index pointer and receive from the controller
	{
		dat[i] = SendSPI(cmd[i]);
		wait_us(20); //// wait 20 us between every byte
	}

	/* If the debug flag is defined show in a serial pc terminal
	   tha comunication results */
#ifdef __DEBUG__
	pc.printf("Sended:   ");
	for (i = 0; i < len; i++)
		pc.printf("%p, ", cmd[i]);
	pc.printf("\r\n");
	pc.printf("Received: ");
	for (i = 0; i < len; i++)
		pc.printf("%p, ", dat[i]);
	pc.printf("\r\n");
#endif

	_cs = 1; //// Finally, set the Chip Select to recesive state
	return i;
}
