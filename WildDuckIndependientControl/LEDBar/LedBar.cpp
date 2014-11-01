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

/* Default constructor */
LedBar::LedBar()
{
	//// Reset private var to default value.
	Throttle = 0; 
	defined = 0;
}
/* Default desconstructor 
   deletes all pwmout constructed before*/
LedBar::~LedBar()
{
	for (int i = 0; i < NUM_SEGMENTS; i++) //// for each segment array meber
		delete Segment[i];				   //// delete the pwmout instance
}
void LedBar::SetPin(int numpin, PinName pin)
{
	if (numpin >= NUM_SEGMENTS) //// if the 9 pwmout are defined
		return;					//// then exit of this function

	Segment[numpin] = new PwmOut(pin);  //// Construct a new instace of pwmout defined in mbed.h
	*Segment[numpin] = 0.0f;			//// use overloaded operator to initialize on 0% duty
	defined++;							//// if new pin is defined adds 1 the defined variable.
}
//// = operator overload 
void LedBar::operator = (const int t)
{
	if (defined < NUM_SEGMENTS) //// if the 9 pwmout aren't defined
		return;					//// then exit of this function

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
