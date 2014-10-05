#include "main.h"

void ConstructAllModules()
{
#ifdef PC_UART_DEBUG
	pc = new BufferedSerial(USBTX, USBRX);
#endif
	reporter = new DataReporter();

#ifdef TEST_SENSORS
	HighSensor = new SRF08(D14, D15, 0xE0);
	FrontSensor1 = new SRF05(D8, D9);
	//FrontSensor2 = new SRF05(D8, D9);
	BackSensor1 = new SRF05(D10, D11);
	//BackSensor2 = new SRF05(D8, D9);
	//LeftSensor1 = new SRF05(D8, D9);
	//LeftSensor2 = new SRF05(D8, D9);
	//RightSensor1 = new SRF05(D8, D9);
	//RightSensor2 = new SRF05(D8, D9);
#else

#ifdef USE_HIGH_SENSOR
	HighSensor = new SRF08(D14, D15, 0xE0);
#endif
#ifdef USE_FRONT_SENSOR
	FrontSensor1 = new SRF05(PTB0, D8);
	FrontSensor2 = new SRF05(PTB0, D9);
#endif
#ifdef USE_BACK_SENSOR
	BackSensor1 = new SRF05(PTB0, D10);
	BackSensor2 = new SRF05(PTB0, D11);
#endif
#ifdef USE_LEFT_SENSOR
	LeftSensor1 = new SRF05(PTB0, D12);
	LeftSensor2 = new SRF05(PTB0, D13);
#endif
#ifdef USE_RIGHT_SENSOR
	RightSensor1 = new SRF05(PTB0, PTA15);
	RightSensor2 = new SRF05(PTB0, PTA14);
#endif

#endif

}
void DestructAllModules()
{
#ifdef PC_UART_DEBUG
	delete pc;
#endif
	delete reporter;

#ifdef TEST_SENSORS
	delete HighSensor;
	delete FrontSensor1;
	//delete FrontSensor2;
	delete BackSensor1;
	//delete BackSensor2;
	//delete LeftSensor1;
	//delete LeftSensor2;
	//delete RightSensor1;
	//delete RightSensor2;
#else

#ifdef USE_HIGH_SENSOR
	delete HighSensor;
#endif
#ifdef USE_FRONT_SENSOR
	delete FrontSensor1;
	delete FrontSensor2;
#endif
#ifdef USE_BACK_SENSOR
	delete BackSensor1;
	delete BackSensor2;
#endif
#ifdef USE_LEFT_SENSOR
	delete LeftSensor1;
	delete LeftSensor2;
#endif
#ifdef USE_RIGHT_SENSOR
	delete RightSensor1;
	delete RightSensor2;
#endif

#endif
}
float Minor(float s1, float s2)
{
	if (s1 <= s2)
		return s1;
	else
		return s2;
}

/**
int final = AxisProtection(range1, range2, target, ControlSignal);
trbControlOuput->Value = final;
**/
int CalcOposition(int range1, float target, int ControlAxis, bool *isInDanger)
{
	if (ControlAxis < 0)
		ControlAxis *= -1;

	float Oposition = 0;
	float Output = 0;

	//// Oposition is calculated number that reduce the control signal
	if (range1 >= target + Conts3Report.Prot_Medium_Limit)/// Positive Axis System protected
	{
		Oposition = 0;
		Output = (Oposition * ControlAxis);
	}
	else if (range1 >= target + Conts3Report.Prot_Low_Limit)/// The system is getting closer to a wall little oposition
	{
		float error = range1 - Conts3Report.Prot_Low_Limit - target;
		float maxError = Conts3Report.Prot_Medium_Limit - Conts3Report.Prot_Low_Limit;
		float gain = 1.0f - (error / maxError);
		float correction = (Conts3Report.Prot_Low_Correction / 1000.0f);
		Oposition = gain * correction;

		Output = (Oposition * ControlAxis);
	}
	else if (range1 >= target)/// The System is very close to the target oposition Oposition total (oposition equal to control signal)
	{
		float error = range1 - target;
		float maxError = Conts3Report.Prot_Low_Limit - 0;
		float gain = 1.0f - (error / maxError);
		float correction = (Conts3Report.Prot_Medium_Correction / 1000.0f);
		Oposition = gain * correction;

		Output = (Oposition * ControlAxis);
	}
	else /// The sytem is in danger negative oposition.
	{
		float error = range1 - target;
		float maxError = target;
		float gain = -(error / maxError);
		float correction = (Conts3Report.Prot_High_Correction / 1000.0f) + 1.0f;
		Oposition = gain * correction;
		Output = (Oposition * 511);// +ControlAxis;
		*isInDanger = true;
	}

	return Output;
}
int AxisProtection(float range1, float range2, int target, int ControlSignal)
{
	float Output1 = 0;
	float Output2 = 0;
	bool Danger1 = false;
	bool Danger2 = false;
	int FinalValue = 0;

	Output1 = CalcOposition((int)range1, (int)target, ControlSignal - 511, &Danger1);
	Output2 = CalcOposition((int)range2, (int)target, ControlSignal - 511, &Danger2);

	FinalValue = ControlSignal;
	if (Danger1 || Danger2)
	{
		FinalValue = 511;
		if (Danger1 && Danger2)
		{
			Output1 /= 4;
			Output2 /= 4;
		}

		if (Danger1)
			FinalValue -= Output1;
		if (Danger2)
			FinalValue += Output2;
	}
	else
	{
		if (ControlSignal >= 511)
			FinalValue = ControlSignal - Output1;
		else
			FinalValue = ControlSignal + Output2;
	}

	if (FinalValue <= 0)
		FinalValue = 0;
	if (FinalValue >= 1022)
		FinalValue = 1022;

	return FinalValue;
}
int ThrottleCorrection(int ErrorDif)
{
	float CalThrottleDif = 0;
	float MaxLimit = 0, MinLimit = 0, MinCorrection = 0, MaxCorrection = 0;
	bool Negative = false;

	if (ErrorDif > 2)/// Quad por debajo del target
	{
		Negative = false;
	}
	else if (ErrorDif < -2) /// Quad por encima del target
	{
		Negative = true;
		ErrorDif *= -1;
	}

	if (ErrorDif > Conts1Report.HS_High_Limit) /// Diferencia es Grande 60
	{
		MinLimit = Conts1Report.HS_High_Limit;
		MinCorrection = Conts2Report.HS_High_Correction;
		MaxLimit = 100;
		MaxCorrection = Conts2Report.HS_UltraHigh_Correction;
	}
	else if (ErrorDif > Conts1Report.HS_Medium_Limit) /// Diferencia es Media 30
	{
		MinLimit = Conts1Report.HS_Medium_Limit;
		MinCorrection = Conts2Report.HS_Medium_Correction;
		MaxLimit = Conts1Report.HS_High_Limit;
		MaxCorrection = Conts2Report.HS_High_Correction;
	}
	else if (ErrorDif > Conts1Report.HS_Low_Limit) /// Diferencia es Minima 10
	{
		MinLimit = Conts1Report.HS_Low_Limit;
		MinCorrection = Conts2Report.HS_Low_Correction;
		MaxLimit = Conts1Report.HS_Medium_Limit;
		MaxCorrection = Conts2Report.HS_Medium_Correction;
	}
	else if (ErrorDif > 2) /// Diferencia es Muy Minima
	{
		MinLimit = 2;
		MinCorrection = 0;
		MaxLimit = Conts1Report.HS_Low_Limit;
		MaxCorrection = Conts2Report.HS_Low_Correction;
	}
	float NetError = (ErrorDif - MinLimit);
	float NetScale = (MaxLimit - MinLimit);
	float NetGain = (MaxCorrection - MinCorrection);

	CalThrottleDif = ((NetError / NetScale) * NetGain) + MinCorrection;
	if(Negative)CalThrottleDif *= -1;

	return (int)CalThrottleDif;
}
void TargetControl(char Target)
{
	int ErrorDif = Target - sreport.Elevation;
	int FinalThrottle = IDLE_CONSTANT; // Constante Throttle IDLE probablemente no sea cero
	
	FinalThrottle += ThrottleCorrection(ErrorDif);

	freport.Throttle = FinalThrottle;
	Throtle = (float)((float)(FinalThrottle) / 1022.0f);
}
void EmergencyAttend()
{
	if (!UsingEmergency)
	{
		HighEmergency = sreport.Elevation;
		UsingEmergency = true;
		EAttemps = 0;
	}
	else
	{
		if (sreport.Elevation < eLanding.BreakOutOffHeight)
			PowerDown();
		else
		{
			EAttemps++;
			if (EAttemps > (eLanding.DecrementTime))
			{
				HighEmergency -= ((float)eLanding.DownDecrementCoeficient / (float)10000);
				EAttemps = 0;
			}
			TargetControl(HighEmergency);
		}
	}
}
void PowerUp()
{
	Throtle = 0.0f;
	Rudder = 1.0f;
	Elevator = 1.0f;
	Aileron = 0.0f;

	Aileron();
	Throtle();
	Elevator();
	Rudder();
	UChannel();

	wait_ms(POWER_DELAY_MS);
}
void PowerDown()
{
	Throtle = 0.0f;
	Rudder = 1.0f;
	Elevator = 1.0f;
	Aileron = 0.0f;

	Aileron();
	Throtle();
	Elevator();
	Rudder();
	UChannel();

	wait_ms(POWER_DELAY_MS);
}

void UpdateSensors()
{
#ifdef USE_HIGH_SENSOR
	HighRangeRead++;
	if (HighRangeRead>8)
	{
		HighSensor->startRanging();
		HighRangeRead = 0;
	}
#endif

#ifdef TEST_SENSORS
	sreport.Elevation = HighSensor->GetInches();
	sreport.Front = FrontSensor1->GetInches();
	sreport.Back = BackSensor1->GetInches();
	sreport.Left = 0;
	sreport.Right = 0;
#else

#ifdef USE_HIGH_SENSOR
	sreport.Elevation = HighSensor->GetInches();
#else
	sreport.Elevation = 0;
#endif
#ifdef USE_FRONT_SENSOR
	sreport.Front = Minor(FrontSensor1->GetInches(), FrontSensor2->GetInches());
#else
	sreport.Front = 0;
#endif
#ifdef USE_BACK_SENSOR
	sreport.Back = Minor(BackSensor1->GetInches(), BackSensor2->GetInches());
#else
	sreport.Back = 0;
#endif
#ifdef USE_LEFT_SENSOR
	sreport.Left = Minor(LeftSensor1->GetInches(), LeftSensor2->GetInches());
#else
	sreport.Left = 0;
#endif
#ifdef USE_RIGHT_SENSOR
	sreport.Right = Minor(RightSensor1->GetInches(), RightSensor2->GetInches());
	sreport.Debug1 = RightSensor1->GetInches();
	sreport.Debug2 = RightSensor2->GetInches();
#else
	sreport.Right = 0;
#endif

#endif

	reporter->SetSensorsReport(sreport);
}
void UpdateThrottle()
{
	if (!reporter->IsOnline() && eLanding.UseEmergencyLanding)
	{
		EmergencyAttend();
		return;
	}
	else UsingEmergency = false;

	if (creport.UseTargetMode)
		TargetControl(creport.ElevationTarget);
	else
	{
		freport.Throttle = creport.Throttle;
		Throtle = (float)((float)(creport.Throttle) / 1022.0f);
	}
		
}
void UpdateMovements()
{
	if (Conts1Report.UseProtection)
	{
#ifdef USE_FRONT_SENSOR
#ifdef USE_BACK_SENSOR
		freport.Elevator = AxisProtection(sreport.Back, sreport.Front, Conts1Report.ProtectionDistance, creport.Elevator);
		Elevator = (float)((float)(freport.Elevator) / 1022.0f);
#endif
#endif
#ifdef USE_LEFT_SENSOR
#ifdef USE_RIGHT_SENSOR
		freport.Aileron = AxisProtection(sreport.Right, sreport.Left, Conts1Report.ProtectionDistance, creport.Aileron);
		Aileron = (float)((float)(freport.Aileron) / 1022.0f);
#endif
#endif
	}
	else
	{
		freport.Aileron = creport.Aileron;
		freport.Elevator = creport.Elevator;
		Aileron = (float)(((float)creport.Aileron) / 1022.0f);
		Elevator = (float)((float)(creport.Elevator) / 1022.0f);
	}

	freport.Rudder = creport.Rudder;
	freport.UChannel = creport.UChannel;
	Rudder = (float)((float)(creport.Rudder) / 1022.0f);
	UChannel = (float)((float)(creport.UChannel) / 254.0f);
}
void UpdateESC()
{
    creport = reporter->GetControllerReport();
	if (creport.Command == 0x01)
		PowerUp();
	if (creport.Command == 0x02)
		PowerDown();

	if (reporter->ConstantsHaveChanged())
	{
		Conts1Report = reporter->GetConstants1();
		Conts2Report = reporter->GetConstants2();
		Conts3Report = reporter->GetConstants3();
		eLanding = reporter->GetEmergencyLandingReport();
	}

	UpdateThrottle();
	UpdateMovements();

	reporter->SetControllerReport(freport);

    Aileron();
    Throtle();    
    Elevator();
    Rudder();
    UChannel();
}

void ShowControllerReport()
{
#ifdef PC_UART_DEBUG
	ControllerReport report = reporter->GetControllerReport();
	pc->printf("Throttle #%d\r\n", report.Throttle);
	pc->printf("Rudder #%d\r\n", report.Rudder);
	pc->printf("Aileron #%d\r\n", report.Aileron);
	pc->printf("Elevator #%d\r\n", report.Elevator);
	pc->printf("Elevation #%d\r\n\r\n", report.ElevationTarget);
	pc->printf("UChannel #%d\r\n\r\n", report.UChannel);
#endif
} 
void ShowSensorsReport()
{
#ifdef PC_UART_DEBUG
#ifdef TEST_SENSORS
	//pc->printf("%4.2f\r\n", HighSensor->GetInches());
#else
	//pc->printf("S1: %4.2f, S2: %4.2f\r\n", RightSensor1->GetInches(), RightSensor2->GetInches());
#endif
#endif
}

int main() {
	ConstructAllModules();

    while(1) 
    {
		UpdateSensors();
		UpdateESC();

		ShowControllerReport();
		//ShowSensorsReport();
		
		wait_ms(REFRESH_TIMEOUT_MS);
    }

	DestructAllModules();
}
