#include "mbed.h"
#include "PS_PAD.h"

DigitalOut myled(LED2);

PS_PAD pad(D12, D11, D13, D10);
#ifndef __DEBUG__
Serial pc(USBTX, USBRX);
#endif

int main() {
	int res = pad.init();
	if (res == 0)
	{
#ifndef __DEBUG__
		pc.printf("Joystick Opened\r\n");
#endif
	}
    while(1) {
		pad.poll();
		if (pad.read(PAD_X))
		{
#ifndef __DEBUG__
			pc.printf("X Pressed\r\n");
#endif
		}

		if (pad.read(PAD_CIRCLE))
		{
#ifndef __DEBUG__
			pc.printf("O Pressed\r\n");
#endif
		}

		if (pad.read(PAD_L1))
		{
#ifndef __DEBUG__
			pc.printf("AXIS: %d\r\n", pad.read(ANALOG_LX));
#endif
		}

		myled = !myled;
        wait(0.05);

    }
}
