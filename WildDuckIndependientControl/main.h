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
#define SENSIBILITY 200
#define UPDATE_RATE 0.049f

//#define __DEBUG_PC_
#define USE_RF

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
