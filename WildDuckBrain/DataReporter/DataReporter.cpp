#include "DataReporter.h"

DigitalOut led2(LED1);
DigitalOut Led(LED2);
////////////////////////////////////////////////////////////////////////
////       Public  Members
////////////////////////////////////////////////////////////////////////

DataReporter::DataReporter()
{
	HeartBeat = 0;
	LastHeartBeat = 0;
	HeartTolerance = 0;
	isOnline = false;

	bufferBusy = false;
	lastChar = 0x00;
	ReportRequest = Sensors;
	revBuffer = new char[REPORTLENGTH];
	changed = true;
	idle = true;
	InitReports();

	rf = new Serial(PTE16, PTE17); // tx, rx
	rf->baud(BAUDRATE);
	tickWatchDog = new Ticker();
	rf->attach(this, &DataReporter::GetReport);
	tickWatchDog->attach(this, &DataReporter::WatchDog, 0.1f);

	buffer = new char[MAXBUFFER];
	ReceivedReport = new char[REPORTLENGTH];
	bufPointer = 0;

}
DataReporter::~DataReporter()
{
    delete ReceivedReport;
    delete buffer;
	delete rf;
	delete revBuffer;
}
bool DataReporter::ConstantsHaveChanged()
{
	bool ret = changed;
	changed = false;
	return ret;
}
bool DataReporter::IsIdle()
{
	return idle;
}
bool DataReporter::IsOnline()
{
	return isOnline;
}

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

	_emergencyLanding.UseEmergencyLanding = 0;
	_emergencyLanding.ConnectionTimeOut = 50;// 5 Seconds
	_emergencyLanding.BreakOutOffHeight = 20;
	_emergencyLanding.DownDecrementCoeficient = 0;
	_emergencyLanding.DecrementTime = 0;

	_constants1.UseProtection = 0;
	_constants1.ProtectionDistance = 0;
	_constants1.HS_High_Limit = 60;
	_constants1.HS_Medium_Limit = 30;
	_constants1.HS_Low_Limit = 10;

	_constants2.HS_UltraHigh_Correction = 320;
	_constants2.HS_High_Correction = 120;
	_constants2.HS_Medium_Correction = 35;
	_constants2.HS_Low_Correction = 12;

	_constants3.Prot_Medium_Limit = 0;
	_constants3.Prot_Low_Limit = 0;
	_constants3.Prot_High_Correction = 0;
	_constants3.Prot_Medium_Correction = 0;
	_constants3.Prot_Low_Correction = 0;
}

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

void DataReporter::SetControllerReport(ControllerReport report)
{
    _ScontrollerReport = report;
}
void DataReporter::SetSensorsReport(SensorsReport report)
{
    _SsensorsReport = report;
}
void DataReporter::SetEmergencyLandingReport(EmergencyLanding report)
{
    _SemergencyLanding = report;
}
void DataReporter::SetConstants1(Constants1 report)
{
    _Sconstants1 = report;
}
void DataReporter::SetConstants2(Constants2 report)
{
    _Sconstants2 = report;
}
void DataReporter::SetConstants3(Constants3 report)
{
    _Sconstants3 = report;
}

void DataReporter::ClearBuffer()
{
	int i;
	for (i = 0; i<MAXBUFFER; i++)
		buffer[i] = 0x00;
	bufPointer = 0;
}
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
#endif

////////////////////////////////////////////////////////////////////////
////       Private  Members
////////////////////////////////////////////////////////////////////////
void DataReporter::SendReport()
{
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
		revBuffer[2] = _SemergencyLanding.UseEmergencyLanding;
		revBuffer[3] = _SemergencyLanding.ConnectionTimeOut;
		revBuffer[4] = _SemergencyLanding.BreakOutOffHeight;
		revBuffer[5] = (char)(_SemergencyLanding.DownDecrementCoeficient & 0xff);
		revBuffer[6] = (char)((_SemergencyLanding.DownDecrementCoeficient >> 8) & 0xff);
		revBuffer[7] = _SemergencyLanding.DecrementTime;
		revBuffer[8] = (char)0x00;
		revBuffer[9] = (char)0x00;
		Send(revBuffer);
		break;

	case cConstants1:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _Sconstants1.UseProtection;
		revBuffer[3] = _Sconstants1.ProtectionDistance;
		revBuffer[4] = _Sconstants1.HS_High_Limit;
		revBuffer[5] = _Sconstants1.HS_Medium_Limit;
		revBuffer[6] = _Sconstants1.HS_Low_Limit;
		revBuffer[7] = (char)0x00;
		revBuffer[8] = (char)0x00;
		revBuffer[9] = (char)0x00;
		Send(revBuffer);
		break;

	case cConstants2:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = (char)((_Sconstants2.HS_UltraHigh_Correction >> 0) & 0x0ff);
		revBuffer[3] = (char)((_Sconstants2.HS_UltraHigh_Correction >> 8) & 0x0ff);
		revBuffer[4] = (char)((_Sconstants2.HS_High_Correction >> 0) & 0x0ff);
		revBuffer[5] = (char)((_Sconstants2.HS_High_Correction >> 8) & 0x0ff);
		revBuffer[6] = (char)((_Sconstants2.HS_Medium_Correction >> 0) & 0x0ff);
		revBuffer[7] = (char)((_Sconstants2.HS_Medium_Correction >> 8) & 0x0ff);
		revBuffer[8] = (char)((_Sconstants2.HS_Low_Correction >> 0) & 0x0ff);
		revBuffer[9] = (char)((_Sconstants2.HS_Low_Correction >> 8) & 0x0ff);
		Send(revBuffer);
		break;

	case cConstants3:
		revBuffer[0] = (char)ReportRequest;
		revBuffer[1] = (char)Nothing;
		revBuffer[2] = _Sconstants3.Prot_Medium_Limit;
		revBuffer[3] = _Sconstants3.Prot_Low_Limit;
		revBuffer[4] = (char)((_Sconstants3.Prot_High_Correction >> 0) & 0xff);
		revBuffer[5] = (char)((_Sconstants3.Prot_High_Correction >> 8) & 0xff);
		revBuffer[6] = (char)((_Sconstants3.Prot_Medium_Correction >> 0) & 0xff);
		revBuffer[7] = (char)((_Sconstants3.Prot_Medium_Correction >> 8) & 0xff);
		revBuffer[8] = (char)((_Sconstants3.Prot_Low_Correction >> 0) & 0xff);
		revBuffer[9] = (char)((_Sconstants3.Prot_Low_Correction >> 8) & 0xff);
		Send(revBuffer);
		break;
	}
}
void DataReporter::GetReport()
{
    int i;

    if(rf->readable()) {
        char c = rf->getc();
        buffer[bufPointer] = c;
        bufPointer++;

        if(lastChar == 0xFF && c == 0xFF) {
            if(bufPointer>11) {
                for(i=0; i< REPORTLENGTH; i++)
                    ReceivedReport[i] = buffer[i];

                DecodeReport();
				//wait_us(10);
				SendReport();
                led2 = !led2;
				HeartBeat++;
            }
            bufPointer = 0;
        }
        lastChar = c;
    }
}

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

	_controllerReport.Command = (ReceivedReport[2] >> 4) & 0x0f;
	_ScontrollerReport = _controllerReport;
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
	

	
}