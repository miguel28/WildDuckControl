#include "mbed.h"

#define USBHOST 
#define MAXBUFFER 32
#define REPORTLENGTH 10 

#ifdef USBHOST
#include "USBHID.h"
#endif

class RFInfoReport
{
public:
	RFInfoReport(HID_REPORT* rep);
	
    #ifdef USBHOST
    void Send(HID_REPORT report);
    #else
    void Send(char* data);
    #endif

	void Attach();
	void GetReport();
	char bufPointer;
	char *buffer;
	unsigned char HeartBeat;
private:
	
	bool bufferBusy;
	char lastChar;

	HID_REPORT* report;
	Serial* rf;
	Serial* rfRx;

	void ClearBuffer();
	
};
