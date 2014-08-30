#include "RFTransfer.h"
Serial rf(D14, D15); // tx, rx

RFInfoReport::RFInfoReport()
{
}

void RFInfoReport::GetReport()
{
    
}
#ifdef USBHOST
void RFInfoReport::Send(HID_REPORT report)
{
    int i;
    for(i = 0; i<10; i++)
    {
        rf.printf("%c",report.data[i]); 
        wait_us(1);
    }  
    rf.printf("%c%c",char(0xff),char(0xff)); 
}
#else
void RFInfoReport::Send(char* data)
{
    int i;
    for(i = 0; i<10; i++)
    {
        rf.printf("%c",data[i]); 
        wait_us(1);
    }  
    rf.printf("%c%c",char(0xff),char(0xff)); 
}
#endif
