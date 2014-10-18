#include "mbed.h"
#include "esc.h"

ESC::ESC(const PinName pwmPinOut, const int period)
        : esc(pwmPinOut), period(period), throttle(0)
{
    esc.period_ms(period);
    esc.pulsewidth_us(throttle);
}

bool ESC::setDuty (const float t)
{
    if (t >= 0.0 && t <= 1.0) {       // qualify range, 0-1
        throttle = 1000.0*t + 1000;     // map to range, 1-2 ms (1000-2000us)
        return true;
    }
    return false;
}
bool ESC::operator= (const float t){
    return this->setDuty(t);
}

float ESC::getDuty () const{
    return throttle;
}
ESC::operator float () const{
    return this->getDuty();
}

void ESC::pulse ()
{
    esc.pulsewidth_us(throttle);
}
void ESC::operator() ()
{
    this->pulse();
}

void ESC::powerOff()
{
	throttle = 0;
}