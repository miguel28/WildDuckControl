#include "main.h"

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
		CalcThrottle += 100.0f;
	if (joy->ButtonNewpress(DOWN)) //// When press digital pad Substracts to the throttle 10% every new press
		CalcThrottle -= 100.0f;

	float tmpThortle = joy->GetAxis(1, JOY_DEATH_ZONE); //// Get Axis 1 (Throttle) os joystick

	if (tmpThortle <= 0.0f) //// Throttle UP when axis result is less that 0.0f
		CalcThrottle += -tmpThortle * (SENSIBILITY / 50.0f); //// Calc sensibility of up throttle axis
	else /// Throttle DOWN when  axis result is grater than 0.0f;
		CalcThrottle += -tmpThortle * ((SENSIBILITY * 1.25f) / 50.0f); //// Calc sensibility of down throttle axis, downs 25% more.

	if (CalcThrottle <= 0.0f) //// If throttle is lesser or equal that 0.0f
		CalcThrottle = 0.0f;  //// then set throttle to 0.0f. This is for preventing get negative throttles even if user try down more
	if (CalcThrottle >= 1022.0f) //// If throttle is greater or equal that 0.0f
		CalcThrottle = 1022.0f; //// then set throttle to 0.0f. This is for preventing get overload throttles even if user try up more

	if (joy->ButtonNewpress(Circle)) //// Emergency Set Throttle to Zero if press Circle Button of Joystick
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
		report.UChannel = 220u; //// Constand Pwmout signal of NAZA, to tells them that the controller it is in manual mode
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

	//pc.printf("Throttle %d, %d \r\n", bar->Throttle, bar->value);
	if (joy->ButtonNewpress(UP))
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
		pc.printf("Cross \r\n");
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

	buffer[6] = temp5;//// ^
	buffer[7] = (unsigned char)report.ElevationTarget; //// Send elevation target 
	buffer[8] = (unsigned char)report.UChannel;        //// Send UChannel for
	buffer[9] = (unsigned char)report.UseTargetMode;   //// Send commnad of use target Mode, always 0x00 in this case

	WriteReport(buffer);

	if (Arming)
	{
		armingCounter += UPDATE_RATE;
		if (armingCounter >= 0.4f)
		{
			Arming = false;
			armingCounter = 0.0f;
		}
	}
}
void WriteReport(unsigned char* data)
{
#ifdef USE_RF
	int i;
	for (i = 0; i<10; i++)
	{
		while (!rf.writeable());
		rf.putc(data[i]);
	}
	while (!rf.writeable());
	rf.putc((char)0xff);
	while (!rf.writeable());
	rf.putc((char)0xff);
#endif
}
void SetupBar()
{
	bar = new LedBar();
	wait_us(10);
	bar->SetPin(0, A0);
	wait_us(10);
	bar->SetPin(1, A1);
	wait_us(10);
	bar->SetPin(2, A2);
	wait_us(10);
	bar->SetPin(3, A3);
	wait_us(10);
	bar->SetPin(4, A4);
	wait_us(10);
	bar->SetPin(5, A5);
	wait_us(10);
	bar->SetPin(6, D2);
	wait_us(10);
	bar->SetPin(7, D5);
	wait_us(10);
	bar->SetPin(8, D7);
	wait_us(10);
}
void SetupJoystick()
{
	joy = new Joystick();
	int res = joy->init();

#ifdef __DEBUG_PC_
	if (res == 0)
		pc.printf("Joystick Opened\r\n");
	else
		pc.printf("Joystick NOT Opened\r\n");
#endif

	if (res != 0)
		while (1);
}
int main() {
	rf.baud(19200);
	wait_ms(1000);

	SetupBar();
	SetupJoystick();

    while(1) 
	{
		wait(UPDATE_RATE);
		UpdateControls();

		onlineLed = !onlineLed;
    }
}
