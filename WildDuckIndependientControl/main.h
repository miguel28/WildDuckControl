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

#define JOY_DEATH_ZONE 0.10f
#define MAX_AXIS 1.0f
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
//DigitalOut myled(LED2);
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
