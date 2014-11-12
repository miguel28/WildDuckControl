/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File Reports.h

This program has been created by using mbed runtime libraries
for the platform FRDM-KL46Z in a offline project managed by
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

/*
	This header file define the Formats of a structures
	used to send via serial port byte per byte, in order
	to manage in the program as a abstract object, and 
	create a class that serialize the structure to make 
	sendable/readeable by UART RF module.
*/

#ifndef _REPORTS_H_  //// This prototype file is for avoid redefinitions of this files
#define _REPORTS_H_

/* This enum defines the IDs ofthe formats */
enum 
{
	Joystick = 0x00,
	Sensors = 0x01,
	cEmergencyLanding = 0x02,
	cConstants1 = 0x03,
	cConstants2 = 0x04,
	cConstants3 = 0x05,

	Nothing = 0x0f
};

/* This is the main structure that handles
   the data used for the quadcopter brain to update
   the PWM signals that has been send b te controller
   the same as a comercial controller.
*/
typedef struct
{
    unsigned short Throttle;
    unsigned short Rudder;
    unsigned short Aileron;
    unsigned short Elevator;
    unsigned char ElevationTarget;
    unsigned char UChannel;
    unsigned char UseTargetMode;
	unsigned char Command;
}ControllerReport;

/* This structure sends the sensors current state*/
typedef struct
{
    unsigned char Elevation;
    unsigned char Front;
    unsigned char Back;
    unsigned char Left;
    unsigned char Right;
	unsigned char Debug1;
	unsigned char Debug2;
	unsigned char Debug3;
}SensorsReport;

/* This structures handles certain contasts that can be 
   Updated on the go while the program is running without 
   connect the Freedom board to the PC.
*/
typedef struct
{
    unsigned char UseEmergencyLanding;
    unsigned char ConnectionTimeOut;
    unsigned char BreakOutOffHeight;
    unsigned short DownDecrementCoeficient;
    unsigned char DecrementTime;
}EmergencyLanding;

typedef struct
{
    unsigned char UseProtection;
    unsigned char ProtectionDistance;
    unsigned char HS_High_Limit;
    unsigned char HS_Medium_Limit;
    unsigned char HS_Low_Limit;
	unsigned char DangerProtectionDivide;
	float Sensibility;
}Constants1;

typedef struct
{
     unsigned short HS_UltraHigh_Correction;
     unsigned short HS_High_Correction;
     unsigned short HS_Medium_Correction;
     unsigned short HS_Low_Correction;
}Constants2;

typedef struct
{
    unsigned char Prot_Medium_Limit;
    unsigned char Prot_Low_Limit;
    unsigned short Prot_High_Correction;
    unsigned short Prot_Medium_Correction;
    unsigned short Prot_Low_Correction;
}Constants3;

#endif
//// end of Reports.h
