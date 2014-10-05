#include "LedBar.h"


LedBar::LedBar()
{
	Throttle = 0;
	defined = 0;
}
LedBar::~LedBar()
{
	for (int i = 0; i < NUM_SEGMENTS; i++)
		delete Segment[i];
}
void LedBar::SetPin(int numpin, PinName pin)
{
	if (numpin >= NUM_SEGMENTS)
		return;

	Segment[numpin] = new PwmOut(pin);
	*Segment[numpin] = 0.0f;
	defined++;
}
void LedBar::operator = (const int t)
{
	if (defined < NUM_SEGMENTS)
		return;

	Throttle = t;
	CalcPWM();
}

void LedBar::CalcPWM()
{
	value = (int)(((float)Throttle / MAX_THROTTLE) * 100.0f);
	//*Segment[9] = 0.5f;
	for (int i = 0; i < NUM_SEGMENTS; i++)
	{
		int diff = (int)(value - (i * 11));
		if (diff > 10)
			*Segment[i] = 1.0f;
		else
			*Segment[i] = (float)diff/10.0f;
	}
}

