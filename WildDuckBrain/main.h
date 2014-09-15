#include "mbed.h"
#include "esc.h"
#include "SRF05.h"
#include "SRF08.h"
#include "DataReporter.h"
#include "UltrasonicBase.h"

//#define PC_UART_DEBUG
//#define TEST_SENSORS
#define USE_HIGH_SENSOR
#define USE_FRONT_SENSOR
#define USE_BACK_SENSOR
#define USE_LEFT_SENSOR
#define USE_RIGHT_SENSOR

#define IDLE_CONSTANT 511
#define REFRESH_TIMEOUT_MS 20
#define POWER_DELAY_MS 2000

#ifdef PC_UART_DEBUG
BufferedSerial *pc;
#endif

DataReporter *reporter;
ESC Aileron(D5);
ESC Elevator(D4);
ESC Throtle(D3);
ESC Rudder(D2);
ESC UChannel(D6);

#ifdef TEST_SENSORS
SRF08 *HighSensor;
SRF05 *FrontSensor1;
//SRF05 *FrontSensor2;
SRF05 *BackSensor1;
//SRF05 *BackSensor2;
//SRF05 *LeftSensor1;
//SRF05 *LeftSensor2;
//SRF05 *RightSensor1;
//SRF05 *RightSensor2;
#else

#ifdef USE_HIGH_SENSOR
SRF08 *HighSensor;
#endif
#ifdef USE_FRONT_SENSOR
SRF05 *FrontSensor1;
SRF05 *FrontSensor2;
#endif
#ifdef USE_BACK_SENSOR
SRF05 *BackSensor1;
SRF05 *BackSensor2;
#endif
#ifdef USE_LEFT_SENSOR
SRF05 *LeftSensor1;
SRF05 *LeftSensor2;
#endif
#ifdef USE_RIGHT_SENSOR
SRF05 *RightSensor1;
SRF05 *RightSensor2;
#endif

#endif

///////////////Reports
ControllerReport creport;
Constants1 Conts1Report;
Constants2 Conts2Report;
Constants3 Conts3Report;
EmergencyLanding eLanding;

SensorsReport sreport;
//////////// Variables
bool UsingEmergency = false;
float HighEmergency = 0.0f;
int EAttemps = 0;
int HighRangeRead = 0;


void ConstructAllModules();
void DestructAllModules();
 
float Minor(float s1, float s2);
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
