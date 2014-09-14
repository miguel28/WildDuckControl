#include "mbed.h"
#include "esc.h"
#include "SRF05.h"
#include "SRF08.h"
#include "DataReporter.h"

//#define PC_UART_DEBUG
//#define TEST_SENSORS
#define USE_HIGH_SENSOR
#define USE_FRONT_SENSOR
//#define USE_BACK_SENSOR
//#define USE_LEFT_SENSOR
//#define USE_RIGHT_SENSOR


#define IDLE_CONSTANT 511
#define REFRESH_TIMEOUT_MS 20
#define POWER_DELAY_MS 2000

#ifdef PC_UART_DEBUG
BufferedSerial pc(USBTX, USBRX);
#endif
DataReporter reporter;
ESC Aileron(D5);
ESC Elevator(D4);
ESC Throtle(D3);
ESC Rudder(D2);
ESC UChannel(D6);

#ifdef TEST_SENSORS
SRF08 HighSensor(D14, D15, 0xE0);
SRF05 FrontSensor1(D8, D9);
//SRF05 FrontSensor2(D8, D9);
SRF05 BackSensor1(D10, D11);
//SRF05 BackSensor2(D8, D9);
//SRF05 LeftSensor1(D8, D9);
//SRF05 LeftSensor2(D8, D9);
//SRF05 RightSensor1(D8, D9);
//SRF05 RightSensor2(D8, D9);
#else

#ifdef USE_HIGH_SENSOR
SRF08 HighSensor(D14, D15, 0xE0);
#endif
#ifdef USE_FRONT_SENSOR
SRF05 FrontSensor1(PTB0, D8);
SRF05 FrontSensor2(PTB0, D9);
#endif
#ifdef USE_BACK_SENSOR
SRF05 BackSensor1(PTB0, D10);
SRF05 BackSensor2(PTB0, D11);
#endif
#ifdef USE_LEFT_SENSOR
SRF05 LeftSensor1(PTB0, D12);
SRF05 LeftSensor2(PTB0, D13);
#endif
#ifdef USE_RIGHT_SENSOR
SRF05 RightSensor1(PTB0, PTA15);
SRF05 RightSensor2(PTB0, PTA14);
#endif

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

int HighRangeRead = 0;

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
