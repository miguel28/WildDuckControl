#include "mbed.h"
#define NUM_SEGMENTS 9
#define MAX_THROTTLE 1022.0f

class LedBar
{
private:
	PwmOut *Segment[NUM_SEGMENTS];
	void CalcPWM();

public:

	int value;
	int Throttle;
	int defined;

	LedBar();
	~LedBar();
	void SetPin(int numpin, PinName pin);
	void operator= (const int t);
};