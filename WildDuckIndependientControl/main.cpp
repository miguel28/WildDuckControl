#include "mbed.h"
#include "PS_PAD.h"

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

#ifndef __DEBUG__
Serial pc(USBTX, USBRX);
DigitalOut myled(LED2);
#endif

Joystick* joy;
ControllerReport report;
float CalcThrottle = 0.0f;
bool Arming = false;

void UpdateControls()
{
	joy->Update();

	float tmpThortle = joy->GetAxis(1, JOY_DEATH_ZONE);
	CalcThrottle += -tmpThortle * (SENSIBILITY / 50.0f);
	if (CalcThrottle <= 0.0f)
		CalcThrottle = 0.0f;
	if (CalcThrottle >= 1022.0f)
		CalcThrottle = 1022.0f;

	if (joy->ButtonNewpress(2))
		CalcThrottle = 0.0f;

	if (joy->ButtonHeld(10))
	{
		report.Throttle = 0;
		report.Rudder = 0;
		report.Aileron = 512;
		report.Elevator = 512;
		CalcThrottle = 0.0f;
		Arming = true;
	}
	else if (joy->ButtonHeld(9))
	{
		report.Throttle = 0;
		report.Rudder = 1022;
		report.Aileron = 512;
		report.Elevator = 512;
		CalcThrottle = 0.0f;
		Arming = true;
	}
	else Arming = false;
	if (Arming)
		return;

	report.Throttle = (unsigned short)(CalcThrottle);
	report.Rudder = (unsigned short)(joy->GetAxis(0, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
	report.Aileron = (unsigned short)(joy->GetAxis(3, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
	report.Elevator = (unsigned short)(joy->GetAxis(2, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;

#ifndef __DEBUG__
	pc.printf("Throttle %d \r\n", report.Throttle);
#endif
}

void SendCommand()
{

}

int main() {
	joy = new Joystick();
	int res = joy->init();

#ifndef __DEBUG__
	if (res ==0)
		pc.printf("Joystick Opened\r\n");
	else
	{
		pc.printf("Joystick NOT Opened\r\n");
		while (1);
	}
		
#endif
    while(1) 
	{
		wait(0.05);
		UpdateControls();
		SendCommand();

		myled = !myled;
    }
}
