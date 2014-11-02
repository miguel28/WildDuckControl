/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File main.cpp

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

#include "main.h" //// Include main.h definitions

/*
Takes 0 Arguments
Return void Argument

This subroutine polls the arm and disarm condition by using 
Start/Select Buttons of PS2 controller. This Routine its called
from UpdateControls() Subroutine.
*/
void ArmFunction()
{
	//// If L1 is held pressed it means that you're trying to arm KK2 
	//// If L1 isn't held pressed it meas that you're trying yo arm NAZA
	if (joy->ButtonHeld(L1))
		report.Command |=0x08u;

	if (joy->ButtonHeld(Start)) //// If the start button it gets heldpressed 
	{							//// then set command for getting armed KK2 or NAZA
		report.Command |= 0x01u;  //// Set bit 0 of command nibble
		CalcThrottle = 0.0f;	//// Also set throttle to Zero
		Arming = true;			//// Set flag to the the program
	}
	else if (joy->ButtonHeld(Select))   //// If the start button it gets heldpressed 
	{									//// then set command for getting disarmed KK2 or NAZA
		report.Command |= 0x02u;			//// set bit 1 of command nibble
		CalcThrottle = 0.0f;			//// Also set throttle to Zero
		Arming = true;					//// Set flag to the the program
	}
}

/*
Takes 0 arguments
Return void argument

This subroutine polls the controller state and it's the reponsibe of
manage the joystick data in a structure ControllerReport and also 
call SendCommand() subroutine to send all data formated in 12 byte pakage.
*/
void UpdateControls()
{
	joy->Update(); /// Polls new axis and buttons state from joystick

	if (joy->ButtonNewpress(UP)) //// When press digital pad Adds to the throttle 10% every new press
		CalcThrottle += 30.0f;
	if (joy->ButtonNewpress(DOWN)) //// When press digital pad Substracts to the throttle 10% every new press
		CalcThrottle -= 30.0f;

	float tmpThortle = joy->GetAxis(1, JOY_DEATH_ZONE); //// Get Axis 1 (Throttle) os joystick

	if (tmpThortle <= 0.0f) //// Throttle UP when axis result is less that 0.0f
		CalcThrottle += -tmpThortle * ((SENSIBILITY * 0.5f)/ 50.0f); //// Calc sensibility of up throttle axis
	else /// Throttle DOWN when  axis result is grater than 0.0f;
		CalcThrottle += -tmpThortle * ((SENSIBILITY) / 50.0f); //// Calc sensibility of down throttle axis, downs 25% more.

	if (CalcThrottle <= 0.0f) //// If throttle is lesser or equal that 0.0f
		CalcThrottle = 0.0f;  //// then set throttle to 0.0f. This is for preventing get negative throttles even if user try down more
	if (CalcThrottle >= 1022.0f) //// If throttle is greater or equal that 0.0f
		CalcThrottle = 1022.0f; //// then set throttle to 0.0f. This is for preventing get overload throttles even if user try up more

	if (joy->ButtonHeld(Circle) || joy->ButtonHeld(Triangle)) //// Emergency Set Throttle to Zero if press Circle Button of Joystick
		CalcThrottle = 0.0f;		//// Set throttle to IDLE

	report.Command = 0x00u; /// Reset command Nibble (view Controller Report Structure in main.h)
	ArmFunction(); //// Call Arm subroutine

	if (!Arming)  //// If the flag is false, it means that we can send new Axis State of joystick
	{
		if (joy->ButtonHeld(R1)) //// If square button it is held pressed 
			report.Command |= 0x04;  //// Then send Motor command in bit 3 of nibble command.

		/*
		This part of subroutine formats the joystick data to Controller Report
		structure in main.h, to be ready to send via UART as a data stream byte per byte
		*/

		report.Throttle = (unsigned short)(CalcThrottle); //// Convert the CalcThrottle Var to usigned Short format (view Controller Report Structure in main.h)
		report.Rudder = (unsigned short)((-joy->GetAxis(0, JOY_DEATH_ZONE)) * MAX_AXIS * 511.0f) + 511; //// Convert Value of axis 0 to be a rudder value of control (get notice that this axis is inverted)
		report.Aileron = (unsigned short)(joy->GetAxis(3, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511; //// Convert value of axis 3 to be a aileron value of control
		report.Elevator = (unsigned short)(joy->GetAxis(2, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511; //// Convert value of axis 2 to be a elevator value of control
		report.UChannel = 45u; //// Constand Pwmout signal of NAZA, to tells them that the controller it is in manual mode
	}
	else /// if the flag is true create a synchronous timer to clear the flag
	{
		armingCounter += UPDATE_RATE; //// the armCounter addes the update rate in every vertical sync line
									  //// UPDATE_RATE is a macro defined in main.h
		if (armingCounter >= 0.4f)    //// if the timer counter is grater or equal than 0.4f
		{							  //// then
			Arming = false;			  //// clear the arming flag
			armingCounter = 0.0f;     //// reset Counter
		}
	}


	*bar = report.Throttle; //// Se to the var led the number of throttle we have calculated to turns on respectedly leds in power hand.
	SendCommand(); //// Cals Send Command Function once we have formated the joystick data in ControllerReport structure.

	/*
	This little _DEBUG_PC_ debug block is only to check the value in 
	serial terminal what button have been pressed in the joystick.
	It is useless in runtime if you comments the line where I define
	_DEBUG_PC_ macro in main.h 
	*/

#ifdef __DEBUG_PC_

	pc.printf("Throttle %d \r\n", report.Throttle);
	//pc.printf("Elevator %d \r\n", report.Elevator);
	/*if (joy->ButtonNewpress(UP))
		pc.printf("UP \r\n");
	if (joy->ButtonNewpress(DOWN))
		pc.printf("DOWN \r\n");
	if (joy->ButtonNewpress(LEFT))
		pc.printf("LEFT \r\n");
	if (joy->ButtonNewpress(RIGHT))
		pc.printf("RIGHT \r\n");

	if (joy->ButtonNewpress(L1))
		pc.printf("L1 \r\n");
	if (joy->ButtonNewpress(R1))
		pc.printf("R1 \r\n");
	if (joy->ButtonNewpress(L2))
		pc.printf("L2 \r\n");
	if (joy->ButtonNewpress(R2))
		pc.printf("R2 \r\n");

	if (joy->ButtonNewpress(Circle))
		pc.printf("CIRCLE \r\n");
	if (joy->ButtonNewpress(Square))
		pc.printf("SQUARE \r\n");
	if (joy->ButtonNewpress(Triangle))
		pc.printf("Triangle \r\n");
	if (joy->ButtonNewpress(Cross))
		pc.printf("Cross \r\n");*/
#endif
}

/*
Takes 0 Arguments
Returns void argument

This sub routine fixed some data that cand be handled by the byte per
byte data stream procotol in 12 byte pakage data over UART trasmision.

After that Calls the function WriteReport(char* buffer) subroutine.
*/
void SendCommand()
{
	/*
	This part of this subroutine fixed some data

	the data pakage of 12 bytes can be contain in the body two 0xffu consecutives thats why 
	the end of tha pakage must be 0xffu, 0xffu and the receiver can missunderstood the pakage
	as a invalid or incomplete pakage.

	Example :
				   {PakageID,  PkgRequested, 8 bytes data pakage body------------------------------,  2 end bytes 0xffu };
	char* pakage = {   0x01u,         0x0fu, 0x50u, 0x30u, 0xefu, 0x17u, 0x56u, 0x67u, 0x34u, 0x21u,  0xffu,    0xffu   };

	the receiver take bytes from RF UART module and check until it gets  the two 0xff bytes.

	thats why the following lines correct 255, 511, 1023 report values in order to avoid that
	*/
	
	if (report.Aileron == 255)
		report.Aileron = 256;

	if (report.Elevator == 255)
		report.Elevator = 256;

	if (report.Rudder == 255)
		report.Rudder = 256;

	if (report.Throttle == 255)
		report.Throttle = 256;

	if (report.Aileron == 511)
		report.Aileron = 512;

	if (report.Elevator == 511)
		report.Elevator = 512;

	if (report.Rudder == 511)
		report.Rudder = 512;

	if (report.Throttle == 511)
		report.Throttle = 512;

	if (report.Aileron >= 1022)
		report.Aileron = 1022;

	if (report.Elevator >= 1022)
		report.Elevator = 1022;

	if (report.Rudder >= 1022)
		report.Rudder = 1022;

	if (report.Throttle >= 1022)
		report.Throttle = 1022;

	/* 
	This part of subroutine formats the data structure defined in main.h
	to a 12 bytes data pakage.
	*/

	//// First byte contains 1st nibble of Report format and 2nd nibble of Commnads
	buffer[0] = 0x00u | (report.Command << 4); //// controllerReport ID is 0x00u and concats Commnad Nibble
	buffer[1] = 0x0fu; //// 0x0fu this a identifier of do not responds nothing from QuadCoper

	buffer[2] = (unsigned char)(report.Throttle & 0xff); //// Take the first 8 bits of Throttle usigned short (value could be between 0 - 1022)
	buffer[3] = (unsigned char)(report.Rudder & 0xff);   //// Take the first 8 bits of Rudder usigned short (value could be between 0 - 1022)
	buffer[4] = (unsigned char)(report.Aileron & 0xff);  //// Take the first 8 bits of Aileron usigned short (value could be between 0 - 1022)
	buffer[5] = (unsigned char)(report.Elevator & 0xff); //// Take the first 8 bits of Elevator usigned short (value could be between 0 - 1022)

	unsigned char temp1 = (unsigned char)((unsigned char)((report.Throttle >> 8) << 6) & 0xff); //// Take the last 2 bits of Throttle usigned short
	unsigned char temp2 = (unsigned char)((unsigned char)((report.Rudder >> 8) << 4) & 0xff);   //// Take the last 2 bits of Rudder usigned short
	unsigned char temp3 = (unsigned char)((unsigned char)((report.Aileron >> 8) << 2) & 0xff);  //// Take the last 2 bits of Aileron usigned short
	unsigned char temp4 = (unsigned char)((unsigned char)((report.Elevator >> 8) << 0) & 0xff); //// Take the last 2 bits of Elevator usigned short
	unsigned char temp5 = (unsigned char)((temp1 | temp2 | temp3 | temp4) & 0xff); //// Take this all last bits of every axis and concats in other byte (byte 6)

	buffer[6] = temp5;//// Asigned the contacted byte ^^^^^
	buffer[7] = (unsigned char)report.ElevationTarget; //// Send elevation target 
	buffer[8] = (unsigned char)report.UChannel;        //// Send UChannel for
	buffer[9] = (unsigned char)report.UseTargetMode;   //// Send commnad of use target Mode, always 0x00 in this case

	WriteReport(buffer); //// Calls write report subroutine, that takes 1 parameter a char* buffer with 12 char pointer size

}

/*
Take 1 argument, unsigned char pointer with minum data length 10.
return void argument

This function manage the use of byte per byte data sending in a uart 
module specified in rf objec.

This method polls in a while loop a waits untils the UART Module 
is available to write a new character, in fact in means that the las 
character that we have requested to send has been sent. For doing
this is only by calling bool writable() methad define in Serial 
class of mebed runtime library.

After that if a write new character by calling void putc(char c)
method of Serial Class define in mbed runtime library
(Check www.mbed.org Serial Handbook).
*/
void WriteReport(unsigned char* data) //// Take unsigned char* data pointer
{
#ifdef USE_RF //// If it is defined thar USE_RF macro in main.h compile the pollowing code
			  //// This macro could be undefined for debugging porpuses only.
	int i;    //// Declara our integer iterator variable (standar for a for loop)
	for (i = 0; i<10; i++)	//// make a loop from i = 0 to i = 9
	{						//// this loop writes the 10 first byte of the pakage
		while (!rf.writeable()); //// wait until the UART module it is available to write
		rf.putc(data[i]);		 //// then put a new character to write
	}
	while (!rf.writeable()); //// wait until the UART module it is available to write
	rf.putc((char)0xff);     //// then writes 0xff in the uart module
	while (!rf.writeable()); //// wait until the UART module it is available to write
	rf.putc((char)0xff);     //// then writes 0xff in the uart module
#endif
}

/*
Take 0 arguments
returns void parameter

this function asigned the hardware pins that can be used as pwmout defined
for the Freedom microcontroller FDRM-KL25Z, see www.mbed.org FDRM-KL25Z
Handbook. 

This function contructs the bar object with a defaul LedBar Contructor.

The funcion it take 9 pwmout pins, asigned with the imediate value of the
pin definitin by using the method void LedBar::SetPin(int numpin, PinName pin)
and waiting 10 us to se the next pin in order to avoid a current overload,
and also to avoid a program freezes.
*/
void SetupBar()
{
	bar = new LedBar(); //// Contruct the bar object
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(0, A0); //// Se segment 0 of the bar as a A0 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(1, A1); //// Se segment 1 of the bar as a A1 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(2, A2); //// Se segment 2 of the bar as a A2 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(3, A3); //// Se segment 3 of the bar as a A3 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(4, A4); //// Se segment 4 of the bar as a A4 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(5, A5); //// Se segment 5 of the bar as a A5 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(6, D2); //// Se segment 6 of the bar as a D2 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(7, D5); //// Se segment 7 of the bar as a D5 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
	bar->SetPin(8, D7); //// Se segment 8 of the bar as a D7 pin
	wait_us(10);        //// Wait 10 us to avoid current overload
}

/*
Takes 0 Arguments
returns void argument.

This function constructs a new Joystick instance in joy object,
and algo initalizes the PS2 controller (see Joystick.h and Joystick.cpp)

if any error in the moment of the initialization go to a infinite loop
*/
void SetupJoystick()
{
	joy = new Joystick(); //// creates a new instance of Joystick in joy object
	int res = joy->init();//// Initializes the joystick and stores the initialization result.
	////  if the result it is equal 0 the joystick was successfully opened
	/// if the result is diferent to 0 the joystick wasn't successfully opened

#ifdef __DEBUG_PC_ //// This define block if for pc debug only if the _DEBUG_PC_ is defined
				   //// writes in a serial terminal the result of the initialization.
	if (res == 0)  
		pc.printf("Joystick Opened\r\n");
	else
		pc.printf("Joystick NOT Opened\r\n");
#endif

	if (res != 0) //// if the result it's not equal to 0 the go to infinite loop.
		while (1); //// Infinite loop
}

/*
main c function of the program
*/
int main() {
	rf.baud(19200); //// first of all changes the baud rate to 19200 that's why the uart module 
					//// that previuosly have been programed from RF-Magic
	wait_ms(1000);  //// wait 1 second  to avoid current overload.z

	SetupBar();     //// Calls SetupBar() to asign the led bar pins
	SetupJoystick();//// Calls SetupJoystick() to initialize the joystick

    while(1) //// Main program infinite loop
	{
		wait(UPDATE_RATE); //// wait the Update rate define in main.h
		UpdateControls();  //// calls UpdatesControls() to poll new values of joystick and
						   //// and sent to the rf uart module.

		onlineLed = !onlineLed; /// Toggle led of a led on the 10th bar led
    }
}

/* End of file main.cpp */
