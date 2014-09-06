#include "mbed.h"
#include "esc.h"
#include "SRF05.h"
#include "DataReporter.h"

#define PC_UART_DEBUG
#define TEST_SENSORS


#define IDLE_CONSTANT 511

#ifdef PC_UART_DEBUG
BufferedSerial pc(USBTX, USBRX);
#endif

DataReporter reporter(true);
ESC Aileron(D5);
ESC Elevator(D4);
ESC Throtle(D3);
ESC Rudder(D2);
ESC UChannel(PTE31);

#ifdef TEST_SENSORS
SRF05 HighSensor(D8, D9);
//SRF05 FrontSensor1(D8, D9);
//SRF05 FrontSensor2(D8, D9);
//SRF05 BackSensor1(D8, D9);
//SRF05 BackSensor2(D8, D9);
//SRF05 LeftSensor1(D8, D9);
//SRF05 LeftSensor2(D8, D9);
//SRF05 RightSensor1(D8, D9);
//SRF05 RightSensor2(D8, D9);

#else
SRF05 HighSensor(D8, D9);
SRF05 FrontSensor1(D8, D9);
SRF05 FrontSensor2(D8, D9);
SRF05 BackSensor1(D8, D9);
SRF05 BackSensor2(D8, D9);
SRF05 LeftSensor1(D8, D9);
SRF05 LeftSensor2(D8, D9);
SRF05 RightSensor1(D8, D9);
SRF05 RightSensor2(D8, D9);
#endif

ControllerReport creport;
Constants1 Conts1Report;
Constants2 Conts2Report;
Constants3 Conts3Report;

void UpdateSensors()
{
	SensorsReport report;
#ifdef TEST_SENSORS
	report.Elevation = HighSensor.GetInches();
	report.Front = 0;
	report.Back = 0;
	report.Left = 0;
	report.Right = 0;
#else
	report.Elevation = HighSensor.GetInches();
	report.Front = FrontSensor1.Minor(FrontSensor2);
	report.Back = BackSensor1.Minor(BackSensor2);
	report.Left = LeftSensor1.Minor(LeftSensor2);
	report.Right = RightSensor1.Minor(RightSensor2);
#endif
	reporter.SetSensorsReport(report);
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
void UpdateThrottle()
{
	if (creport.UseTargetMode)
	{
		int ErrorDif = creport.ElevationTarget - HighSensor.GetInches();
		int FinalThrottle = IDLE_CONSTANT; // Constante Throttle IDLE probablemente no sea cero
		FinalThrottle += ThrottleCorrection(ErrorDif);
		Throtle = (float)((float)(FinalThrottle) / 1022.0f);
	}
	else Throtle = (float)((float)(creport.Throttle) / 1022.0f);
}
void UpdateMovements()
{
	if (Conts1Report.UseProtection)
	{

	}
	else
	{
		Aileron = (float)(((float)creport.Aileron) / 1022.0f);
		Elevator = (float)((float)(creport.Elevator) / 1022.0f);
		Rudder = (float)((float)(creport.Rudder) / 1022.0f);
	}

	UChannel = (float)((float)(creport.UChannel) / 254.0f);
}
void UpdateESC()
{
    creport = reporter.GetControllerReport();
	if (reporter.ConstantsHaveChanged())
	{
		Conts1Report = reporter.GetConstants1();
		Conts2Report = reporter.GetConstants2();
		Conts3Report = reporter.GetConstants3();
	}

	UpdateThrottle();
	UpdateMovements();

    Aileron();
    Throtle();    
    Elevator();
    Rudder();
    UChannel();
}

void ShowControllerReport()
{
#ifdef PC_UART_DEBUG
	ControllerReport report = reporter.GetControllerReport();
	pc.printf("Throttle #%d\r\n", report.Throttle);
    pc.printf("Rudder #%d\r\n",report.Rudder);
    pc.printf("Aileron #%d\r\n",report.Aileron);
    pc.printf("Elevator #%d\r\n",report.Elevator);
    pc.printf("Elevation #%d\r\n\r\n",report.ElevationTarget);
    pc.printf("UChannel #%d\r\n\r\n",report.UChannel);
#endif
} 
void ShowSensorsReport()
{
#ifdef TEST_SENSORS
#ifdef PC_UART_DEBUG
	pc.printf("%4.2f\r\n", HighSensor.GetInches());
#endif
#endif
}

int main() {

    while(1) 
    {
		UpdateSensors();
		UpdateESC();
		


		//ShowControllerReport();
		ShowSensorsReport();
		wait_ms(REFRESH_TIMEOUT_MS);
    }
}
