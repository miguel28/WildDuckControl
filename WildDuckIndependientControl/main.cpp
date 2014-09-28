#include "mbed.h"
#include "BufferedSerial.h"
#include "PS_PAD.h"

DigitalOut myled(LED2);
Joystick joy;
//BufferedSerial pc(USBTX, USBRX);

int main() {
	int res = joy.init();
	/*if (res ==0)
		pc.printf("Joystick Connected!%d\r\n", res);
	else
		pc.printf("Joystick NO Connected!%d\r\n", res);
		*/
    while(1) {
		joy.Update();
		//pc.printf("POLL: %d\r\n", joy.poll());
		//pc.printf("Axis 0: %4.4f\r\n", joy.GetAxis(0));
		//pc.printf("Axis 0: %d\r\n", joy.read(ANALOG_LX));

        myled = 1;
        wait(0.05);
        myled = 0;
        wait(0.05);
    }
}
