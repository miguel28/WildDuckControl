#include "mbed.h"
#include "Joystick.h"
#include "LedBar.h"

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

#define JOY_DEATH_ZONE 0.25f
#define MAX_AXIS 0.7f
#define SENSIBILITY 200
#define __DEBUG_PC_

#ifdef __DEBUG_PC_
Serial pc(USBTX, USBRX);
#endif

DigitalOut myled(LED2);
Joystick* joy;
LedBar* bar;

ControllerReport report;
float CalcThrottle = 0.0f;
bool Arming = false;
unsigned char buffer[12];

void UpdateControls();
void ArmFunction();
void SendCommand();
void SetupBar();
void SetupJoystick();
