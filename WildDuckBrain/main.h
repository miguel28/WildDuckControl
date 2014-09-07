#include "mbed.h"
#include "esc.h"
#include "SRF05.h"
#include "DataReporter.h"


#define PC_UART_DEBUG
#define TEST_SENSORS
#define IDLE_CONSTANT 511
#define POWER_DELAY_MS 2000


#ifdef PC_UART_DEBUG
BufferedSerial pc(USBTX, USBRX);
#endif
DataReporter reporter;
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
///////////////Reports
ControllerReport creport;
Constants1 Conts1Report;
Constants2 Conts2Report;
Constants3 Conts3Report;
EmergencyLanding eLanding;

//////////// Variables
bool UsingEmergency = false;
float HighEmergency = 0.0f;
int EAttemps = 0;

int ThrottleCorrection(int ErrorDif);
void TargetControl(char Target);
void EmergencyAttend();
void PowerUp();
void PowerDown();
void UpdateThrottle();
void UpdateMovements();
void UpdateESC();
void ShowControllerReport();
void ShowSensorsReport();