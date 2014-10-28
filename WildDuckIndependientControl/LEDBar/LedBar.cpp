/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File LedBar.cpp

This program has been created by using mbed runtime libraries
for the platform FRDM-KL25Z in a offline project managed by
arm-gcc compiler.

For more details see (http://www.mbed.org) for a gerneal
overview. And for the development se (http://developer.mbed.org/)

*This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>
******************************************************************/

#include "LedBar.h"

LedBar::LedBar()
{
	//// Reset private var to default value.
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

//// end of LedBar.cpp
