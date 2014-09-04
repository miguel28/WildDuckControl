#ifndef MBED_SRF05_H
#define MBED_SRF05_H

#include "mbed.h"
#include "UltrasonicBase.h"

class SRF05 : public IUltrasonicSensor
{
public:

    SRF05(PinName trigger, PinName echo);
	float Greater(SRF05 s);

private :
    DigitalOut _trigger;
    InterruptIn _echo;
    Timer _timer;
    Ticker _ticker;
    void _rising (void);
    void _falling (void);
    void _startRange (void);
    float _dist;
};

#endif
