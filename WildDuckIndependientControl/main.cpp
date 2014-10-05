#include "main.h"

void ArmFunction()
{
#if FLY_CONTROL == KK2 
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
#else
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
#endif
}
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

	ArmFunction();

	if (Arming)
		return;

	report.Throttle = (unsigned short)(CalcThrottle);
	report.Rudder = (unsigned short)(joy->GetAxis(0, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
	report.Aileron = (unsigned short)(joy->GetAxis(3, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
	report.Elevator = (unsigned short)(joy->GetAxis(2, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
	report.UChannel = 220u;

	*bar = report.Throttle;
	SendCommand();

#ifdef __DEBUG_PC_
	//pc.printf("Throttle %d \r\n", report.Throttle);
	pc.printf("Throttle %d, %d \r\n", bar->Throttle, bar->value);
#endif
}
void SendCommand()
{
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

	buffer[0] = 0x00u;
	buffer[1] = 0x00u;

	buffer[2] = (unsigned char)(report.Throttle & 0xff);
	buffer[3] = (unsigned char)(report.Rudder & 0xff);
	buffer[4] = (unsigned char)(report.Aileron & 0xff);
	buffer[5] = (unsigned char)(report.Elevator & 0xff);

	unsigned char temp1 = (unsigned char)((unsigned char)((report.Throttle >> 8) << 6) & 0xff);
	unsigned char temp2 = (unsigned char)((unsigned char)((report.Rudder >> 8) << 4) & 0xff);
	unsigned char temp3 = (unsigned char)((unsigned char)((report.Aileron >> 8) << 2) & 0xff);
	unsigned char temp4 = (unsigned char)((unsigned char)((report.Elevator >> 8) << 0) & 0xff);
	unsigned char temp5 = (unsigned char)((temp1 | temp2 | temp3 | temp4) & 0xff);

	buffer[6] = temp5;
	buffer[7] = (unsigned char)report.ElevationTarget;
	buffer[8] = (unsigned char)report.UChannel;
	buffer[9] = (unsigned char)report.UseTargetMode;

	//WriteReport(buffer);
}
void SetupBar()
{
	bar = new LedBar();
	bar->SetPin(0, A0);
	bar->SetPin(1, A1);
	bar->SetPin(2, A2);
	bar->SetPin(3, A3);
	bar->SetPin(4, A4);
	bar->SetPin(5, A5);
	bar->SetPin(6, D2);
	bar->SetPin(7, D5);
	bar->SetPin(8, D7);
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
	SetupBar();
	SetupJoystick();

    while(1) 
	{
		wait(0.05);
		UpdateControls();
		SendCommand();

		myled = !myled;
    }
}
