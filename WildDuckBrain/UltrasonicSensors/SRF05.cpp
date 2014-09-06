#include "SRF05.h"
#include "mbed.h"

SRF05::SRF05(PinName trigger, PinName echo) 
    : _trigger(trigger), _echo(echo) {    
        
    // Attach interrupts
    _echo.rise(this, &SRF05::_rising);
    _echo.fall(this, &SRF05::_falling);
    _ticker.attach(this, &SRF05::_startRange, 0.1f);     
}
 
float SRF05::Minor(SRF05 s)
{
	float a = GetInches();
	float b = s.GetInches();
	if (a <= b)
		return a;
	else
		return b;
}

void SRF05::_startRange() {
    // send a trigger pulse, 20uS long
    _trigger = 1;
    wait (0.000002);
    _trigger = 0;
}

// Clear and start the timer at the begining of the echo pulse
void SRF05::_rising(void) {
    _timer.reset();
    _timer.start();
}

// Stop and read the timer at the end of the pulse
void SRF05::_falling(void) {
    _timer.stop();
    
    CurrentRange = _timer.read_us();
    CurrentInches = CurrentRange/148.0f;
    CurrentCentimeters = CurrentRange/58.0f;
    AddToStack(CurrentRange);
}
