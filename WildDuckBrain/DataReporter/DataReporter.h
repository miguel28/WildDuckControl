/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File Reports.h

This program has been created by using mbed runtime libraries
for the platform FRDM-KL46Z in a offline project managed by
arm-gcc compiler.

For more details see (http://www.mbed.org) for a gerneal
overview. And for the development se (http://developer.mbed.org/)

*This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>
******************************************************************/

/* 
   This class manages the comunication between the quadcopter brain 
   and the controller and viceversa.

   Also traslated the structures format in a serializable 
   buffer to send byte per byte in a RF UART Module.

   This class manages the serial port the most.

   Also indicates if the control has been disconnected,
   (if is online or ofline).

*/
#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "mbed.h" //// Include mbed runtime libraries for KL46Z
#include "BufferedSerial.h" //// Include a modfication of a simplex serial class to make buffered serial port
#include "Reports.h"   //// Also includes the reports formats define in Reports.h

#ifdef USBHOST       //// if the USB host is defined also include 
#include "USBHID.h"  //// a USBHID header files to manage a Human interface device.
#endif

#define MAXBUFFER 32             //// the receive buffer is for 32-bits
#define REPORTLENGTH 10          //// the received report lenght only has 10 effective bytes
#define SENDREPORTTIMEOUT 0.020f //// Send report timeout
#define BAUDRATE 19200           //// Defines the default baud rate of the rf Module.

/* Definition of the class DataReporter*/
class DataReporter
{
	/*public members*/
public:  
    
    DataReporter();   //// Default contructor, create new instances of the controls
    ~DataReporter();  //// Default destructor

	/*Get reports methods, only returns the last decoded structres */
    ControllerReport GetControllerReport();
    EmergencyLanding GetEmergencyLandingReport();
    Constants1 GetConstants1();
    Constants2 GetConstants2();
    Constants3 GetConstants3();
    
	/*Set sen a new stucuture to send, when the controller asks for
	  certain report, the class sends the last defined in this methods
	*/
    void SetControllerReport(ControllerReport report);
    void SetSensorsReport(SensorsReport report);
    
    char ReportRequest; //// ID of report requested
	bool ConstantsHaveChanged();  //// check if the class has retrieved a new constants data
	bool IsIdle();   //// Check the state of the controller is this is ILDE if the last report has been a constant
	bool IsOnline();  //// Returns if the controller is Online or Offline (check void Watchdog() method).

	/* Private members*/
private:
	/////Comunicacion Variables
	unsigned char bufPointer; //// reveiced Buffer pointer
	char *buffer;         //// received buffer array (size 10 bytes)
	bool bufferBusy;      //// flag is the buffer is busy
    char lastChar;        //// last char received
    char *ReceivedReport; //// last received report array (size 10 byte)
	char *revBuffer;      //// array buffer to send

	bool changed;   //// flag that get is the constants have changed.
	bool idle;      //// flag that indicates if the comunication is IDLE
	unsigned short HeartBeat, LastHeartBeat,HeartTolerance; //// Online calculation variables
	bool isOnline;  //// flas if the controller is online

	Serial* rf;     //// Instance of a rf UART Module
	Ticker* tickWatchDog;  //// Ticker event handler for check the status of the controller every certain time.
	void InitReports();    //// init with the default values the stored structures
	void WatchDog();       //// fucnction called by the ticker tickWatchDog.

	//// if USBHOST is defined declare the apropiate send method.
	//// this method send to the controller byte per byte in the Serial rf Module
#ifdef USBHOST 
	void Send(HID_REPORT report);
#else
	void Send(char* data);
#endif

	/* this methods send the report requested for the controller*/
	void SendReport();

	/* This methos is called by a Serial interruption 
	   when is received a new character and check if the data buffer
	   has been received propertly and finally decodes it.
	*/
    void GetReport(); 

	/* This method clears the receiver buffer, sets all array to 0x00*/
    void ClearBuffer(); 

	/* this methods is for a char buffer received array */
    void DecodeReport();
    void DecodeJoystick();
    void DecodeEmergency();
    void DecodeConstants1();
    void DecodeConstants2();
    void DecodeConstants3();
	/* this methods is for a char buffer received array */

	/* Stored structured values received*/
    ControllerReport _controllerReport;
    EmergencyLanding _emergencyLanding;
    Constants1 _constants1;
    Constants2 _constants2;
    Constants3 _constants3;  
    
	/* Stored structured ready to send values */
    ControllerReport _ScontrollerReport;
    SensorsReport _SsensorsReport;

	/* Stored structured values */
};

#endif