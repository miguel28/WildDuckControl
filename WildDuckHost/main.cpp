#include "mbed.h"
#include "USBHID.h"
#include "RFTransfer.h"

USBHID hid(16, 16, 0x3995,0x0020);
HID_REPORT send_report;
HID_REPORT recv_report;

RFInfoReport reporter(&send_report);
DigitalOut led(LED3);

int main() {
    send_report.length = 16;
   
    while(1) 
    {
        led = 1;
        if(hid.readNB(&recv_report)) 
            reporter.Send(recv_report);

		hid.sendNB(&send_report);
		wait(0.01f);
    }
}
