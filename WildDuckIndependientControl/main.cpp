#include "main.h"

void ArmFunction()
{
	if (joy->ButtonNewpress(10))
	{
		report.Command = 0x01;
		Arming = true;
	}
	else if (joy->ButtonNewpress(9))
	{
		report.Command = 0x02;
		Arming = true;
	}
		
}
void UpdateControls()
{
	joy->Update();

	if (joy->ButtonNewpress(UP))
		CalcThrottle += 100.0f;
	if (joy->ButtonNewpress(DOWN))
		CalcThrottle -= 100.0f;

	float tmpThortle = joy->GetAxis(1, JOY_DEATH_ZONE);
	CalcThrottle += -tmpThortle * (SENSIBILITY / 50.0f);
	if (CalcThrottle <= 0.0f)
		CalcThrottle = 0.0f;
	if (CalcThrottle >= 1022.0f)
		CalcThrottle = 1022.0f;

	if (joy->ButtonNewpress(2))
		CalcThrottle = 0.0f;

	ArmFunction();

	if (!Arming)
	{
		report.Throttle = (unsigned short)(CalcThrottle);
		report.Rudder = (unsigned short)(joy->GetAxis(0, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
		report.Aileron = (unsigned short)(joy->GetAxis(3, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
		report.Elevator = (unsigned short)(joy->GetAxis(2, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
		report.UChannel = 220u;
	}
	
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
	buffer[1] = 0x0fu;

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

	WriteReport(buffer);

	if (Arming)
	{
		armingCounter += UPDATE_RATE;
		if (armingCounter >= 2.0f)
		{
			Arming = false;
			armingCounter = 0.0f;
		}
	}
}
void WriteReport(unsigned char* data)
{
	/*
	int i;
	for (i = 0; i<10; i++)
	{
		while (!rf->writeable());
		rf->putc(data[i]);
	}
	while (!rf->writeable());
	rf->putc((char)0xff);
	while (!rf->writeable());
	rf->putc((char)0xff);*/
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
		wait(UPDATE_RATE);
		UpdateControls();
		SendCommand();
		myled = !myled;
    }
}
