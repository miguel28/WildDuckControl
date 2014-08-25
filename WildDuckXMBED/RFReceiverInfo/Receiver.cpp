#include "Receiver.h"

//Serial rf(PTE16, PTE17); // tx, rx
//Serial rfTx(D14, D15); // tx, rx
//Ticker sendTicker;
DigitalOut led2(LED1);

RFInfoReceiver::RFInfoReceiver(bool attachReveicer)
{
	rf = new Serial(NC, PTE17); // tx, rx
	rf->baud(9600);

#ifndef PC_UART_DEBUG
	rfTx = new BufferedSerial(PTE20, NC); // tx, rx
	rfTx->baud(9600);
#else
	rfTx = new Serial(USBTX, USBRX); // tx, rx
	rfTx->baud(9600);
#endif

	sendTicker = new Ticker();

	bufferBusy = false;
    lastChar = 0x00;
	ReportRequest = Sensors;
    
	_SsensorsReport.Elevation = 50;
	_SsensorsReport.Front = 0;
	_SsensorsReport.Back = 0;
	_SsensorsReport.Left = 0;
	_SsensorsReport.Right = 0;

    if(attachReveicer) {
        rf->attach (this, &RFInfoReceiver::GetReport);
        buffer = new char[MAXBUFFER];
        ReceivedReport = new char[REPORTLENGTH];
        bufPointer = 0;
        ClearBuffer();
    }
}
RFInfoReceiver::~RFInfoReceiver()
{
    delete ReceivedReport;
    delete buffer;
}

ControllerReport RFInfoReceiver::GetControllerReport()
{
	return _controllerReport;
}
EmergencyLanding RFInfoReceiver::GetEmergencyLandingReport()
{
    return _emergencyLanding;
}
Constants1 RFInfoReceiver::GetConstants1()
{
    return _constants1;
}
Constants2 RFInfoReceiver::GetConstants2()
{
    return _constants2;
}
Constants3 RFInfoReceiver::GetConstants3()
{
    return _constants3;
}

void RFInfoReceiver::SetControllerReport(ControllerReport report)
{
    _ScontrollerReport = report;
}
void RFInfoReceiver::SetSensorsReport(SensorsReport report)
{
    _SsensorsReport = report;
}
void RFInfoReceiver::SetEmergencyLandingReport(EmergencyLanding report)
{
    _SemergencyLanding = report;
}
void RFInfoReceiver::SetConstants1(Constants1 report)
{
    _Sconstants1 = report;
}
void RFInfoReceiver::SetConstants2(Constants2 report)
{
    _Sconstants2 = report;
}
void RFInfoReceiver::SetConstants3(Constants3 report)
{
    _Sconstants3 = report;
}

void RFInfoReceiver::SendReport()
{
	char* buffer = new char[10];
	char temp1, temp2, temp3, temp4, temp5;
	ReportRequest = Sensors;

	switch(ReportRequest)
	{
	case Joystick:
		
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0xef;

		buffer[2] = (char)(_ScontrollerReport.Throttle & 0xff);
		buffer[3] = (char)(_ScontrollerReport.Rudder & 0xff);
		buffer[4] = (char)(_ScontrollerReport.Aileron & 0xff);
		buffer[5] = (char)(_ScontrollerReport.Elevator & 0xff);

		temp1 = (char)((char)((_ScontrollerReport.Throttle >> 8) << 6) & 0xff);
		temp2 = (char)((char)((_ScontrollerReport.Rudder >> 8) << 4) & 0xff);
		temp3 = (char)((char)((_ScontrollerReport.Aileron >> 8) << 2) & 0xff);
		temp4 = (char)((char)((_ScontrollerReport.Elevator >> 8) << 0) & 0xff);
		temp5 = (char)((temp1 | temp2 | temp3 | temp4) & 0xff);

		buffer[6] = temp5;
		buffer[7] = (char)_ScontrollerReport.ElevationTarget;
		buffer[8] = (char)_ScontrollerReport.UChannel;
		buffer[9] = (char)_ScontrollerReport.UseTargetMode;

		Send(buffer);
		break;
		

	case Sensors:	
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0xdf;
		buffer[2] = _SsensorsReport.Elevation;
		buffer[3] = _SsensorsReport.Front;
		buffer[4] = _SsensorsReport.Back;
		buffer[5] = _SsensorsReport.Left;
		buffer[6] = _SsensorsReport.Right;
		buffer[7] = (char)0x00;
		buffer[8] = (char)0x00;
		buffer[9] = (char)0x00;

		Send(buffer);
		break;
		

	case cEmergencyLanding:
		
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0xcf;
		buffer[2] = _SemergencyLanding.UseEmergencyLanding;
		buffer[3] = _SemergencyLanding.ConnectionTimeOut;
		buffer[4] = _SemergencyLanding.BreakOutOffHeight;
		buffer[5] = (char)(_SemergencyLanding.DownDecrementCoeficient & 0xff);
		buffer[6] = (char)((_SemergencyLanding.DownDecrementCoeficient >> 8) & 0xff);
		buffer[7] = _SemergencyLanding.DecrementTime;
		buffer[8] = (char)0x00;
		buffer[9] = (char)0x00;

		Send(buffer);
		break;

	case cConstants1:
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0xbf;
		buffer[2] = _Sconstants1.UseProtection;
		buffer[3] = _Sconstants1.ProtectionDistance;
		buffer[4] = _Sconstants1.HS_High_Limit;
		buffer[5] = _Sconstants1.HS_Medium_Limit;
		buffer[6] = _Sconstants1.HS_Low_Limit;
		buffer[7] = (char)0x00;
		buffer[8] = (char)0x00;
		buffer[9] = (char)0x00;
		Send(buffer);
		break;

	case cConstants2:
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0xaf;
		buffer[2] = (char)((_Sconstants2.HS_UltraHigh_Correction >> 0) & 0x0ff);
		buffer[3] = (char)((_Sconstants2.HS_UltraHigh_Correction >> 8) & 0x0ff);
		buffer[4] = (char)((_Sconstants2.HS_High_Correction >> 0) & 0x0ff);
		buffer[5] = (char)((_Sconstants2.HS_High_Correction >> 8) & 0x0ff);
		buffer[6] = (char)((_Sconstants2.HS_Medium_Correction >> 0) & 0x0ff);
		buffer[7] = (char)((_Sconstants2.HS_Medium_Correction >> 8) & 0x0ff);
		buffer[8] = (char)((_Sconstants2.HS_Low_Correction >> 0) & 0x0ff);
		buffer[9] = (char)((_Sconstants2.HS_Low_Correction >> 8) & 0x0ff);
		Send(buffer);
		break;

	case cConstants3:
		buffer[0] = (char)ReportRequest;
		buffer[1] = (char)0x9f;
		buffer[2] = _Sconstants3.Prot_Medium_Limit;
		buffer[3] = _Sconstants3.Prot_Low_Limit;
		buffer[4] = (char)((_Sconstants3.Prot_High_Correction >> 0) & 0xff);
		buffer[5] = (char)((_Sconstants3.Prot_High_Correction >> 8) & 0xff);
		buffer[6] = (char)((_Sconstants3.Prot_Medium_Correction >> 0) & 0xff);
		buffer[7] = (char)((_Sconstants3.Prot_Medium_Correction >> 8) & 0xff);
		buffer[8] = (char)((_Sconstants3.Prot_Low_Correction >> 0) & 0xff);
		buffer[9] = (char)((_Sconstants3.Prot_Low_Correction >> 8) & 0xff);
		Send(buffer);
		break;
	}
}
void RFInfoReceiver::GetReport()
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
                led2 = !led2;
            }
            bufPointer = 0;
        }
        lastChar = c;
    }
}

void RFInfoReceiver::DecodeReport()
{
    ReportRequest = ReceivedReport[1];
    switch(ReceivedReport[0]) {
        case Joystick:
            DecodeJoystick();
            break;

        case Sensors:
            break;

        case cEmergencyLanding:
            DecodeJoystick();
            break;

        case cConstants1:
            DecodeConstants1();
            break;

        case cConstants2:
            DecodeConstants2();
            break;

        case cConstants3:
            DecodeConstants3();
            break;
    }
}
void RFInfoReceiver::DecodeJoystick()
{
    _controllerReport.Throttle = (ReceivedReport[2] | ((ReceivedReport[6] & 0xc0) <<2) );
    _controllerReport.Rudder = (ReceivedReport[3] | ((ReceivedReport[6] & 0x30) <<4) );
    _controllerReport.Aileron = (ReceivedReport[4] | ((ReceivedReport[6] & 0x0c) <<6) );
    _controllerReport.Elevator = (ReceivedReport[5] | ((ReceivedReport[6] & 0x03) <<8) );
    _controllerReport.ElevationTarget = ReceivedReport[7];
}
void RFInfoReceiver::DecodeEmergency()
{
    _emergencyLanding.UseEmergencyLanding = ReceivedReport[2];
    _emergencyLanding.ConnectionTimeOut = ReceivedReport[3];
    _emergencyLanding.BreakOutOffHeight = ReceivedReport[4];
    _emergencyLanding.DownDecrementCoeficient = ReceivedReport[5] | (ReceivedReport[6] << 8);
    _emergencyLanding.DecrementTime = ReceivedReport[7];
}
void RFInfoReceiver::DecodeConstants1()
{
    _constants1.UseProtection = ReceivedReport[2];
    _constants1.ProtectionDistance = ReceivedReport[3];
    _constants1.HS_High_Limit = ReceivedReport[4];
    _constants1.HS_Medium_Limit = ReceivedReport[5];
    _constants1.HS_Low_Limit = ReceivedReport[6];
}
void RFInfoReceiver::DecodeConstants2()
{
    _constants2.HS_UltraHigh_Correction = ReceivedReport[2] | (ReceivedReport[3] << 8);
    _constants2.HS_High_Correction = ReceivedReport[4] | (ReceivedReport[5] << 8);
    _constants2.HS_Medium_Correction = ReceivedReport[6] | (ReceivedReport[7] << 8);
    _constants2.HS_Low_Correction = ReceivedReport[8] | (ReceivedReport[9] << 8);
}
void RFInfoReceiver::DecodeConstants3()
{
    _constants3.Prot_Medium_Limit = ReceivedReport[2];
    _constants3.Prot_Low_Limit = ReceivedReport[3];
    _constants3.Prot_High_Correction = ReceivedReport[4] | (ReceivedReport[5] << 8);
    _constants3.Prot_Medium_Correction = ReceivedReport[6] | (ReceivedReport[7] << 8);
    _constants3.Prot_Low_Correction = ReceivedReport[8] | (ReceivedReport[9] << 8);
}

void RFInfoReceiver::ClearBuffer()
{
    int i;
    for(i=0; i<MAXBUFFER; i++ )
        buffer[i] = 0x00;
    bufPointer = 0;
}
#ifdef USBHOST
void RFInfoReceiver::Send(HID_REPORT report)
{
    int i;
    for(i = 0; i<10; i++) 
	{
        while(!rfTx->writeable());
        rfTx->putc(report.data[i]);
        wait_us(5);
    }
    rfTx->putc(char(0xff));
	wait_us(5);
    rfTx->putc(char(0xff));
	wait_us(5);
}
#else
void RFInfoReceiver::Send(char* data)
{
	/*int i;
    for(i = 0; i<10; i++)
    {
		while (!rfTx->writeable());
        rfTx->putc(data[i]);
        wait_us(500);
    }
	rfTx->putc(char(0xff));
	wait_us(500);
	rfTx->putc(char(0xff));
	wait_us(500);*/
	rfTx->printf("%c%c%c%c%c%c%c%c%c%c%c%c",
		data[0],
		data[1],
		data[2],
		data[3],
		data[4],
		data[5],
		data[6],
		data[7],
		data[8],
		data[9],
		0xff,
		0xff
		);
}
#endif
