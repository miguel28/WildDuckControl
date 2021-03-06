#include "SRF05.h"
#include "mbed.h"

SRF05::SRF05(PinName trigger, PinName echo) 
	: IUltrasonicSensor(6), _trigger(trigger), _echo(echo) {
        
    // Attach interrupts
    _echo.rise(this, &SRF05::_rising);
    _echo.fall(this, &SRF05::_falling);
    _ticker.attach(this, &SRF05::_startRange, 0.1f);     
}
 
void SRF05::_startRange() {
    // send a trigger pulse, 20uS long
    _trigger = 1;
    wait_us(10);
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
