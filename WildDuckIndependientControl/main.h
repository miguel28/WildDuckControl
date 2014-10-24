/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File main.h

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

#include "mbed.h"        //// Include mbed main runtime library check www.mbed.org
#include "Joystick.h"    //// include Joystick class
#include "LedBar.h"      //// include led bar class

/*
structure of ControllerReport
define a serialized 8 bytes in a 
byte per byte uart protocol.
*/
typedef struct
{
	unsigned short Throttle;       //// 10 bits var for throttle
	unsigned short Rudder;         //// 10 bits var for rudder
	unsigned short Aileron;		   //// 10 bits var for aileron
	unsigned short Elevator;       //// 10 bits var for elevator
	unsigned char ElevationTarget; //// 8 bits var for for elevation target
	unsigned char UChannel;        //// 8 bits var for uchannel naza
	unsigned char UseTargetMode;   //// 8 bits var for target mode command
	unsigned char Command;         //// 4 bits var nibble for command
}ControllerReport;

#define JOY_DEATH_ZONE 0.10f   //// Defined a constant of deathzone for joystick
#define MAX_AXIS 1.0f          //// Porportional constant of axis
#define SENSIBILITY 200		   //// This is a Sensibility Factor
#define UPDATE_RATE 0.049f

//#define __DEBUG_PC_  //// This is a flag macro for enables pc serial port debugging
#define USE_RF         //// This macro flag is for compiles the pertinents instructions

#ifdef __DEBUG_PC_
Serial pc(USBTX, USBRX);
#endif

#ifdef USE_RF
Serial rf(D14, D15);
#endif

DigitalOut onlineLed(PTC0);
Joystick* joy;
LedBar* bar;

ControllerReport report;
float CalcThrottle = 0.0f;
bool Arming = false;
unsigned char buffer[12];
float armingCounter = 0.0f;

void WriteReport(unsigned char* data);
void UpdateControls();
void ArmFunction();
void SendCommand();
void SetupBar();
void SetupJoystick();
