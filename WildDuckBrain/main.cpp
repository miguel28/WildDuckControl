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

#else
SRF05 HighSensor(D8, D9);

#endif

ControllerReport creport;
Constants1 Conts1Report;

void UpdateSensors()
{
	SensorsReport report;
	report.Elevation = HighSensor.GetInches();
	report.Front = 0;
	report.Back = 0;
	report.Left = 0;
	report.Right = 0;

	reporter.SetSensorsReport(report);
}

void UpdateThrottle()
{
	if (creport.UseTargetMode)
	{
		int target = creport.ElevationTarget;
		int ErrorDif = target - HighSensor.GetInches();
		int FinalThrottle = IDLE_CONSTANT; // Constante Throttle IDLE probablemente no sea cero
		int CalThrottleDif = 0;
		float ScaleFactor;
		float Gain;

		if (ErrorDif > 3)/// Quad por debajo del target
		{
			if (ErrorDif > HS_High_Limit) /// Diferencia es Grande 60
			{
				FinalThrottle = HS_UltraHigh_Correction;
			}
			else if (ErrorDif > HS_Medium_Limit) /// Diferencia es Media 30
			{
				ScaleFactor = (float)(HS_High_Limit - HS_Medium_Limit) / (float)HS_High_Limit;
				Gain = 
				
				FinalThrottle = Error
			}
			else if (ErrorDif > HS_Low_Limit) /// Diferencia es Minima 10
			{

			}
			else if (ErrorDif > 3) /// Diferencia es Muy Minima
			{

			}
		}
		else if (ErrorDif < -3) /// Quad por encima del target
		{
			if (ErrorDif < -HS_High_Limit) /// Diferencia es Grande
			{

			}
			else if (ErrorDif < -HS_Medium_Limit) /// Diferencia es Media
			{

			}
			else if (ErrorDif > HS_Low_Limit) /// Diferencia es Minima
			{

			}
			else if (ErrorDif > 3) /// Diferencia es Muy Minima
			{

			}
		}
		
		FinalThrottle += CalThrottleDif;
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
	Conts1Report = reporter.GetConstants1();

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
#ifdef PC_UART_DEBUG
#ifdef TEST_SENSORS
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
