#include "mbed.h"
#include "esc.h"
#include "SRF05.h"
#include "SRF08.h"
#include "DataReporter.h"
#include "UltrasonicBase.h"

//#define PC_UART_DEBUG
//#define TEST_SENSORS
//#define USE_HIGH_SENSOR
//#define USE_FRONT_SENSOR
//#define USE_BACK_SENSOR
//#define USE_LEFT_SENSOR
//#define USE_RIGHT_SENSOR
//#define USE_MOTOR
#define USE_LCD

#define IDLE_CONSTANT 511
#define REFRESH_TIMEOUT_MS 30
#define POWER_DELAY_MS 50

#ifdef USE_LCD
#include "SLCD.h"
SLCD *slcd;
#endif

#ifdef PC_UART_DEBUG
BufferedSerial *pc;
#endif

#ifdef USE_MOTOR
ESC mpinMotor(D7);
#endif

DataReporter *reporter;
ESC *Aileron;
ESC *Elevator;
ESC *Throtle;
ESC *Rudder;
ESC *UChannel;

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
ControllerReport freport;
Constants1 Conts1Report;
Constants2 Conts2Report;
Constants3 Conts3Report;
EmergencyLanding eLanding;

SensorsReport sreport;

//////////// Variables
bool ESCPowerdOn = false;
bool UsingEmergency = false;
float HighEmergency = 0.0f;
int EAttemps = 0;
int HighRangeRead = 0;

///////////// Functions
void ConstructAllModules();
void DestructAllModules();

float Minor(float s1, float s2);
int CalcOposition(int range1, float target, int ControlAxis, bool *isInDanger);
int AxisProtection(float range1, float range2, int target, int ControlSignal);
int ThrottleCorrection(int ErrorDif);
void TargetControl(char Target);
void EmergencyAttend();

void SetUpdateESC();
void PowerOffESC();

void PowerArm();
void PowerDisArm();
void UpdateThrottle();
void UpdateMovements();
void UpdateESC();
float AjustAxis(float value, float percent);

void ShowLCD();
void ShowControllerReport();
void ShowSensorsReport();
