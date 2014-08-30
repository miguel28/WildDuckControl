#include "mbed.h"
#include "USBHID.h"
#include "RFTransfer.h"

//Serial pc(USBTX, USBRX); // tx, rx
USBHID hid(16, 16, 0x3995,0x0020);
HID_REPORT send_report;
HID_REPORT recv_report;

RFInfoReport reporter;
DigitalOut led(LED2);

int main() {
    send_report.length = 16;
   
    while(1) 
    {
        led = 1;
        if(hid.read(&recv_report)) 
        {
            reporter.Send(recv_report);
            wait(0.01f);
            led=0;
        }
    }
}
