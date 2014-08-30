#include "RFTransfer.h"

DigitalOut led2(LED2);
Serial pc(USBTX, USBRX);

RFInfoReport::RFInfoReport(HID_REPORT* rep)
{
	HeartBeat = 0;
	report = rep;
	rf = new Serial(D14,D15); // tx, rx
	rfRx = new Serial(PTE22,PTE23);
	rfRx->attach(this, &RFInfoReport::GetReport);
}

#ifdef USBHOST
void RFInfoReport::Send(HID_REPORT report)
{
    int i;
    for(i = 0; i<10; i++)
    {
        rf->printf("%c",report.data[i]); 
        wait_us(1);
    }  
    rf->printf("%c%c",char(0xff),char(0xff)); 
}
#else
void RFInfoReport::Send(char* data)
{
    int i;
    for(i = 0; i<10; i++)
    {
        rf->printf("%c",data[i]); 
        wait_us(1);
    }  
    rf->printf("%c%c",char(0xff),char(0xff)); 
}
#endif

void RFInfoReport::ClearBuffer()
{
	int i;
	for (i = 0; i<MAXBUFFER; i++)
		buffer[i] = 0x00;
	bufPointer = 0;
}

void RFInfoReport::GetReport()
{
	int i;

	if (rfRx->readable()) {
		char c = rfRx->getc();
		pc.putc(c);
		buffer[bufPointer] = c;
		bufPointer++;

		if (lastChar == 0xFF && c == 0xFF) {
			if (bufPointer>11) {
				for (i = 0; i< REPORTLENGTH; i++)
					report->data[i] = buffer[i];

				HeartBeat++;
				report->data[13] = HeartBeat;
				led2 = !led2;
			}
			bufPointer = 0;
		}
		lastChar = c;
	}
}