#include "main.h"

void ArmFunction()
{
	if (joy->ButtonNewpress(Start))
	{
		report.Command = 0x01;
		CalcThrottle = 0.0f;
		Arming = true;
	}
	else if (joy->ButtonNewpress(Select))
	{
		report.Command = 0x02;
		CalcThrottle = 0.0f;
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

	if (joy->ButtonNewpress(Circle))
		CalcThrottle = 0.0f;

	ArmFunction();

	if (!Arming)
	{
		report.Command = 0x00;
		if (joy->ButtonHeld(Square))
			report.Command |= 0x04;

		report.Throttle = (unsigned short)(CalcThrottle);
		report.Rudder = (unsigned short)((-joy->GetAxis(0, JOY_DEATH_ZONE)) * MAX_AXIS * 511.0f) + 511;
		report.Aileron = (unsigned short)(joy->GetAxis(3, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
		report.Elevator = (unsigned short)(joy->GetAxis(2, JOY_DEATH_ZONE) * MAX_AXIS * 511.0f) + 511;
		report.UChannel = 220u;
	}
	
	*bar = report.Throttle;
	SendCommand();

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

	buffer[0] = 0x00u | (report.Command << 4);
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
