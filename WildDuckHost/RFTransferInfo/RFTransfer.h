#include "mbed.h"

#define USBHOST 

#ifdef USBHOST
#include "USBHID.h"
#endif

class RFInfoReport
{
public:
    char Command;
    char Status;
    char Thortle;
    char Rudder;
    char Aileron;
    char Elevator;
    char Elevation;
    RFInfoReport();
    void GetReport();
    #ifdef USBHOST
    void Send(HID_REPORT report);
    #else
    void Send(char* data);
    #endif
};
