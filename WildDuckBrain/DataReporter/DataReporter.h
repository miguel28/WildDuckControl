#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "mbed.h"
#include "BufferedSerial.h"
#include "Reports.h"

#ifdef USBHOST
#include "USBHID.h"
#endif

#define MAXBUFFER 32
#define REPORTLENGTH 10 
#define SENDREPORTTIMEOUT 0.020f
#define REFRESH_TIMEOUT_MS 20
#define BAUDRATE 9600

class DataReporter
{
public:  
    
    DataReporter();   
    ~DataReporter();

	/*Get*/
    ControllerReport GetControllerReport();
    EmergencyLanding GetEmergencyLandingReport();
    Constants1 GetConstants1();
    Constants2 GetConstants2();
    Constants3 GetConstants3();
    
	/*Set*/
    void SetControllerReport(ControllerReport report);
    void SetSensorsReport(SensorsReport report);
    void SetEmergencyLandingReport(EmergencyLanding report);
    void SetConstants1(Constants1 report);
    void SetConstants2(Constants2 report);
    void SetConstants3(Constants3 report);

    
    char ReportRequest;
	bool ConstantsHaveChanged();
	bool IsIdle();
	bool IsOnline();
private:
	/////Comunicacion Variables
	char bufPointer;
	char *buffer;
	bool bufferBusy;
    char lastChar;  
    char *ReceivedReport; 
	char *revBuffer;

	bool changed;
	bool idle;
	unsigned short HeartBeat, LastHeartBeat,HeartTolerance;
	bool isOnline;


	Serial* rf;
	Ticker* tickWatchDog;
	void InitReports();
	void WatchDog();
#ifdef USBHOST
	void Send(HID_REPORT report);
#else
	void Send(char* data);
#endif
	void SendReport();
    void GetReport(); 

    void ClearBuffer();  
    void DecodeReport();
    void DecodeJoystick();
    void DecodeEmergency();
    void DecodeConstants1();
    void DecodeConstants2();
    void DecodeConstants3();

    ControllerReport _controllerReport;
    EmergencyLanding _emergencyLanding;
    Constants1 _constants1;
    Constants2 _constants2;
    Constants3 _constants3;  
    
    ControllerReport _ScontrollerReport;
    SensorsReport _SsensorsReport;
    EmergencyLanding _SemergencyLanding;
    Constants1 _Sconstants1;
    Constants2 _Sconstants2;
    Constants3 _Sconstants3; 
};

#endif