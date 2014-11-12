/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File Reports.cpp

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

#include "DataReporter.h" //// Includes the header of definition of DataReporter.h

/* in this block I declered a 3 led that indicates the conection status*/
DigitalOut led2(LED1);   //// this led toggles every data reportersended
DigitalOut Led(LED2);    //// GREEN LED if the green led toggle in a certain frecuecnty the controller is online
						 //// this led toggles every data reporter decoded
DigitalOut BlueLed(D13); //// same tha laste

////////////////////////////////////////////////////////////////////////
////       Public  Members
////////////////////////////////////////////////////////////////////////

/* the contructor creates a new instaces of certain objects and also
   set the initial value of the internal variables. 
*/
DataReporter::DataReporter()
{
	/* this block initializes the controller offline*/
	HeartBeat = 0;  
	LastHeartBeat = 0;
	HeartTolerance = 100;
	isOnline = false;
	//Led = 1;

	/* This block initializes tehe reports array buffers*/
	bufferBusy = false;
	lastChar = 0x00;
	ReportRequest = Sensors;
	revBuffer = new char[REPORTLENGTH];
	changed = true;
	idle = true;
	InitReports(); //// Calls the report initialization

	/* Create a new instance of the Serial Module in rf pointer, and
	   also attaches the interrupt handlers
	*/
	rf = new Serial(PTE16, PTE17); // tx, rx
	rf->baud(BAUDRATE);
	tickWatchDog = new Ticker();
	rf->attach(this, &DataReporter::GetReport);
	tickWatchDog->attach(this, &DataReporter::WatchDog, 0.1f);


	buffer = new char[MAXBUFFER];
	ReceivedReport = new char[REPORTLENGTH];
	bufPointer = 0;

}

/* The dectuctor deletes all array buffers*/
DataReporter::~DataReporter()
{
    delete ReceivedReport;
    delete buffer;
	delete rf;
	delete revBuffer;
}

/* returns the value fo the private member "changed"
   this is for check if a constant value have changed
*/
bool DataReporter::ConstantsHaveChanged()
{
	bool ret = changed;
	changed = false;
	return ret;
}

/* returns the value fo the private member "idle"
   this is for check if the controller has receiver a new constant
*/
bool DataReporter::IsIdle()
{
	return idle;
}

/* returns the value fo the private member "isOnline"
this is for check if the controller is online or not.
*/
bool DataReporter::IsOnline()
{
	return isOnline;
}

/* this methods initializes the default values of the structures*/
void DataReporter::InitReports()
{
	_controllerReport.Throttle = 0;
	_controllerReport.Rudder = 512;
	_controllerReport.Aileron = 512;
	_controllerReport.Elevator = 512;
	_controllerReport.ElevationTarget = 0;
	_controllerReport.UChannel = 220;
	_controllerReport.UseTargetMode = 0;

	_SsensorsReport.Elevation = 0;
	_SsensorsReport.Front = 0;
	_SsensorsReport.Back = 0;
	_SsensorsReport.Left = 0;
	_SsensorsReport.Right = 0;

	_emergencyLanding.UseEmergencyLanding = 1;
	_emergencyLanding.ConnectionTimeOut = 5;//10 - 1 Seconds
	_emergencyLanding.BreakOutOffHeight = 200;
	_emergencyLanding.DownDecrementCoeficient = 5;////
	_emergencyLanding.DecrementTime = 2;

	_constants1.UseProtection = 0;
	_constants1.ProtectionDistance = 0;
	_constants1.HS_High_Limit = 60;
	_constants1.HS_Medium_Limit = 30;
	_constants1.HS_Low_Limit = 10;
	_constants1.Sensibility = 0.3f;

	_constants2.HS_UltraHigh_Correction = 320;
	_constants2.HS_High_Correction = 120;
	_constants2.HS_Medium_Correction = 35;
	_constants2.HS_Low_Correction = 12;

	_constants3.Prot_Medium_Limit = 20;
	_constants3.Prot_Low_Limit = 12;
	_constants3.Prot_High_Correction = 1000;
	_constants3.Prot_Medium_Correction = 1000;
	_constants3.Prot_Low_Correction = 200;
}

/*Get reports methods, only returns the last decoded structres */
ControllerReport DataReporter::GetControllerReport()
{
	return _controllerReport;
}
EmergencyLanding DataReporter::GetEmergencyLandingReport()
{
    return _emergencyLanding;
}
Constants1 DataReporter::GetConstants1()
{
    return _constants1;
}
Constants2 DataReporter::GetConstants2()
{
    return _constants2;
}
Constants3 DataReporter::GetConstants3()
{
    return _constants3;
}

/*Set sen a new stucuture to send, when the controller asks for
certain report, the class sends the last defined in this methods
*/
void DataReporter::SetControllerReport(ControllerReport report)
{
    _ScontrollerReport = report;
}
void DataReporter::SetSensorsReport(SensorsReport report)
{
    _SsensorsReport = report;
}

/* this method clears the received buffer */
void DataReporter::ClearBuffer()
{
	int i;
	for (i = 0; i<MAXBUFFER; i++)
		buffer[i] = 0x00;
	bufPointer = 0;
}

//// if USBHOST is defined declare the apropiate send method.
//// this method send to the controller byte per byte in the Serial rf Module
#ifdef USBHOST
void DataReporter::Send(HID_REPORT report)
{
	Led = !Led;
	int i;
	for (i = 0; i<10; i++)
	{
		while (!rf->writeable());
		rf->putc(data[i]);
	}
	while (!rf->writeable());
	rf->putc((char)0xff);
	while (!rf->writeable());
	rf->putc((char)0xff);
}
#else
void DataReporter::Send(char* data)
{
	Led = !Led; //// Toggles the RED LED of the KL46Z board
	//// This macro could be undefined for debugging porpuses only.
	int i;    //// Declara our integer iterator variable (standard for a for loop)
	for (i = 0; i<10; i++)	//// make a loop from i = 0 to i = 9
	{						//// this loop writes the 10 first byte of the pakage
		while (!rf.writeable()); //// wait until the UART module it is available to write
		rf.putc(data[i]);		 //// then put a new character to write
	}
	while (!rf.writeable()); //// wait until the UART module it is available to write
	rf.putc((char)0xff);     //// then writes 0xff in the uart module
	while (!rf.writeable()); //// wait until the UART module it is available to write
	rf.putc((char)0xff);     //// then writes 0xff in the uart module
}
#endif

////////////////////////////////////////////////////////////////////////
////       Private  Members
////////////////////////////////////////////////////////////////////////
void DataReporter::SendReport()
{
	/*
	This subroutine formats the data structure defined in main.h
	to a 12 bytes data pakage.
	*/

	char temp1, temp2, temp3, temp4, temp5;

	switch(ReportRequest)
	{
	case Joystick:
		
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;

		revBuffer[2] = (char)(_ScontrollerReport.Throttle & 0xff);
		revBuffer[3] = (char)(_ScontrollerReport.Rudder & 0xff);
		revBuffer[4] = (char)(_ScontrollerReport.Aileron & 0xff);
		revBuffer[5] = (char)(_ScontrollerReport.Elevator & 0xff);

		temp1 = (char)((char)((_ScontrollerReport.Throttle >> 8) << 6) & 0xff);
		temp2 = (char)((char)((_ScontrollerReport.Rudder >> 8) << 4) & 0xff);
		temp3 = (char)((char)((_ScontrollerReport.Aileron >> 8) << 2) & 0xff);
		temp4 = (char)((char)((_ScontrollerReport.Elevator >> 8) << 0) & 0xff);
		temp5 = (char)((temp1 | temp2 | temp3 | temp4) & 0xff);

		revBuffer[6] = temp5;
		revBuffer[7] = (char)_ScontrollerReport.ElevationTarget;
		revBuffer[8] = (char)_ScontrollerReport.UChannel;
		revBuffer[9] = (char)_ScontrollerReport.UseTargetMode;

		Send(revBuffer);
		break;
		

	case Sensors:	
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _SsensorsReport.Elevation;
		revBuffer[3] = _SsensorsReport.Front;
		revBuffer[4] = _SsensorsReport.Back;
		revBuffer[5] = _SsensorsReport.Left;
		revBuffer[6] = _SsensorsReport.Right;
		revBuffer[7] = _SsensorsReport.Debug1;
		revBuffer[8] = _SsensorsReport.Debug2;
		revBuffer[9] = _SsensorsReport.Debug3;
		Send(revBuffer);
		break;
		

	case cEmergencyLanding:
		
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _emergencyLanding.UseEmergencyLanding;
		revBuffer[3] = _emergencyLanding.ConnectionTimeOut;
		revBuffer[4] = _emergencyLanding.BreakOutOffHeight;
		revBuffer[5] = (char)(_emergencyLanding.DownDecrementCoeficient & 0xff);
		revBuffer[6] = (char)((_emergencyLanding.DownDecrementCoeficient >> 8) & 0xff);
		revBuffer[7] = _emergencyLanding.DecrementTime;
		revBuffer[8] = (char)0x00;
		revBuffer[9] = (char)0x00;
		Send(revBuffer);
		break;

	case cConstants1:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _constants1.UseProtection;
		revBuffer[3] = _constants1.ProtectionDistance;
		revBuffer[4] = _constants1.HS_High_Limit;
		revBuffer[5] = _constants1.HS_Medium_Limit;
		revBuffer[6] = _constants1.HS_Low_Limit;
		revBuffer[7] = (char)0x00;
		revBuffer[8] = (char)0x00;
		revBuffer[9] = (char)0x00;
		Send(revBuffer);
		break;

	case cConstants2:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = (char)((_constants2.HS_UltraHigh_Correction >> 0) & 0x0ff);
		revBuffer[3] = (char)((_constants2.HS_UltraHigh_Correction >> 8) & 0x0ff);
		revBuffer[4] = (char)((_constants2.HS_High_Correction >> 0) & 0x0ff);
		revBuffer[5] = (char)((_constants2.HS_High_Correction >> 8) & 0x0ff);
		revBuffer[6] = (char)((_constants2.HS_Medium_Correction >> 0) & 0x0ff);
		revBuffer[7] = (char)((_constants2.HS_Medium_Correction >> 8) & 0x0ff);
		revBuffer[8] = (char)((_constants2.HS_Low_Correction >> 0) & 0x0ff);
		revBuffer[9] = (char)((_constants2.HS_Low_Correction >> 8) & 0x0ff);
		Send(revBuffer);
		break;

	case cConstants3:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _constants3.Prot_Medium_Limit;
		revBuffer[3] = _constants3.Prot_Low_Limit;
		revBuffer[4] = (char)((_constants3.Prot_High_Correction >> 0) & 0xff);
		revBuffer[5] = (char)((_constants3.Prot_High_Correction >> 8) & 0xff);
		revBuffer[6] = (char)((_constants3.Prot_Medium_Correction >> 0) & 0xff);
		revBuffer[7] = (char)((_constants3.Prot_Medium_Correction >> 8) & 0xff);
		revBuffer[8] = (char)((_constants3.Prot_Low_Correction >> 0) & 0xff);
		revBuffer[9] = (char)((_constants3.Prot_Low_Correction >> 8) & 0xff);
		Send(revBuffer);
		break;
	}
}
/* This routine is called by a serial received 
   character interrupt.

   Then the serial receiver a new character this 
   methods stores the incomming character in the buffer array
   by using the bufPointer.

   The methods keeps storing the incoming 
   characters until the last two byte were 0xffu,

   two 0xffu means the end of a report

   the data pakage of 12 bytes can be contain in the body two 0xffu consecutives thats why
   the end of tha pakage must be 0xffu, 0xffu and the receiver can missunderstood the pakage
   as a invalid or incomplete pakage.

   Example :
                  {PakageID,  PkgRequested, 8 bytes data pakage body------------------------------,  2 end bytes 0xffu };
   char* pakage = {   0x01u,         0x0fu, 0x50u, 0x30u, 0xefu, 0x17u, 0x56u, 0x67u, 0x34u, 0x21u,  0xffu,    0xffu   };

   the receiver take bytes from RF UART module and check until it gets  the two 0xff bytes.

   thats why the following lines correct 255, 511, 1023 report values in order to avoid that
*/
void DataReporter::GetReport()
{
    int i; //// for loop interator control

    if(rf->readable()) { //// check if the rf serial is readable
        char c = rf->getc();  //// retrive the received character.
        buffer[bufPointer] = c;  //// stores the character in the buffers
        bufPointer++;   //// next buffer position

        if(lastChar == 0xFF && c == 0xFF) {        //// if we received two 0xff use this data as a valid report
            if(bufPointer>11) {                    //// the data needs to be grater to 11 bytes ( this is a protection of trunked data)
                for(i=0; i< REPORTLENGTH; i++)     //// so, next, put the received buffer data in a last received report.
                    ReceivedReport[i] = buffer[i]; 

                DecodeReport();   //// calls the methods that decodes the last received report in a abstrat structure.
				//wait_us(10);
				SendReport();     //// the funcion also reposes with a new data report that the controller have asked
                //led2 = !led2;
				BlueLed = !BlueLed;  //// Toggles the blue led
				HeartBeat++;         //// heart beat value incrase by 1 to refresh the connection
            }
            bufPointer = 0; //// resets the pointer to 0
        }
        lastChar = c; //// stores the last character received.
    }
}

/* this methods check what kind of report has been recived and
   also deserializes the data in a abstract structure
*/
void DataReporter::DecodeReport()
{
    ReportRequest = ReceivedReport[1];
    switch(ReceivedReport[0] & 0x0f) {
        case Joystick:
			idle = false;
            DecodeJoystick();
            break;

        case Sensors:
			idle = true;
            break;

        case cEmergencyLanding:
			idle = true;
			changed = true;
            DecodeEmergency();
            break;

        case cConstants1:
			idle = true;
			changed = true;
            DecodeConstants1();
            break;

        case cConstants2:
			idle = true;
			changed = true;
            DecodeConstants2();
            break;

        case cConstants3:
			idle = true;
			changed = true;
            DecodeConstants3();
            break;
    }
}
void DataReporter::DecodeJoystick()
{
    _controllerReport.Throttle = (ReceivedReport[2] | ((ReceivedReport[6] & 0xc0) <<2) );
    _controllerReport.Rudder = (ReceivedReport[3] | ((ReceivedReport[6] & 0x30) <<4) );
    _controllerReport.Aileron = (ReceivedReport[4] | ((ReceivedReport[6] & 0x0c) <<6) );
    _controllerReport.Elevator = (ReceivedReport[5] | ((ReceivedReport[6] & 0x03) <<8) );
    _controllerReport.ElevationTarget = ReceivedReport[7];
	_controllerReport.UChannel = ReceivedReport[8];
	_controllerReport.UseTargetMode = ReceivedReport[9];

	_controllerReport.Command = (ReceivedReport[0] >> 4) & 0x0f;
	if (_controllerReport.Command != 0)
		_controllerReport.Throttle = 0;
	if (!isOnline)
		_controllerReport.Command = 0;
}
void DataReporter::DecodeEmergency()
{
    _emergencyLanding.UseEmergencyLanding = ReceivedReport[2];
    _emergencyLanding.ConnectionTimeOut = ReceivedReport[3];
    _emergencyLanding.BreakOutOffHeight = ReceivedReport[4];
    _emergencyLanding.DownDecrementCoeficient = ReceivedReport[5] | (ReceivedReport[6] << 8);
    _emergencyLanding.DecrementTime = ReceivedReport[7];
}
void DataReporter::DecodeConstants1()
{
    _constants1.UseProtection = ReceivedReport[2];
    _constants1.ProtectionDistance = ReceivedReport[3];
    _constants1.HS_High_Limit = ReceivedReport[4];
    _constants1.HS_Medium_Limit = ReceivedReport[5];
    _constants1.HS_Low_Limit = ReceivedReport[6];
	_constants1.DangerProtectionDivide = ReceivedReport[7];
	_constants1.Sensibility = (float)ReceivedReport[8]/100.0f;
	
}
void DataReporter::DecodeConstants2()
{
    _constants2.HS_UltraHigh_Correction = ReceivedReport[2] | (ReceivedReport[3] << 8);
    _constants2.HS_High_Correction = ReceivedReport[4] | (ReceivedReport[5] << 8);
    _constants2.HS_Medium_Correction = ReceivedReport[6] | (ReceivedReport[7] << 8);
    _constants2.HS_Low_Correction = ReceivedReport[8] | (ReceivedReport[9] << 8);
}
void DataReporter::DecodeConstants3()
{
    _constants3.Prot_Medium_Limit = ReceivedReport[2];
    _constants3.Prot_Low_Limit = ReceivedReport[3];
    _constants3.Prot_High_Correction = ReceivedReport[4] | (ReceivedReport[5] << 8);
    _constants3.Prot_Medium_Correction = ReceivedReport[6] | (ReceivedReport[7] << 8);
    _constants3.Prot_Low_Correction = ReceivedReport[8] | (ReceivedReport[9] << 8);
}

/* This fucntion has been called every 20 ms in order to check the 
   status of the connection by using a heartbeat indicator
   if the Heart beat value isn't changed since the last scan 

   then begins to count in the HeartTolerance,

   if the HeartTolerance is greter that certain parameter 
   the connections status is offline, otherwise
   the HeartBeat has changed since the last scan, then 
   the controller is online.

   */
void DataReporter::WatchDog()
{
	if (HeartBeat == LastHeartBeat)
	{
		HeartTolerance++;
	}
	else
	{
		LastHeartBeat = HeartBeat;
		HeartTolerance = 0;
		isOnline = true;
	}
	
	if (HeartTolerance >= _emergencyLanding.ConnectionTimeOut)
		isOnline = false;
	else isOnline = true;

	//Led = !isOnline;
}
