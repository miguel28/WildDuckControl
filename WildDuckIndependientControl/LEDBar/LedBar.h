/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File LedBar.h

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

/******************************************************************
This file define Ledbar Class. 
This public class handles the power gloove, that it has 9 led in 
common catode that show the total of throttle has been sended to 
the wild duck brain.

This class uses the concept of pwmout led illumitaion.
this example shows how the led bar looks to show certain throttle.

The 100% of throttle is showed in 9 leds, it means 11.11% correspond
to each led, so any scale of this 11.11% is showed in a duty cycle
of the pwmout for the imcomplete part of this 11.11%.

For example if we have 5% of throttle, is less than 11.11%, this can't 
show a comple led illumination but show arrounf 50% of duty on the first
pwmout. 

If we have 16% of throttle, we can illuminate the first led to 100%
of the pwmout, but the second one must be illuminated with arround of
50 % of the pwmout for the second led.

Here more grafics examples:

100% throttle

█████████

90% throttle

███████▓░

50% throttle

████▓░░░░

0% throttle

░░░░░░░░░

NOTE: the FDRM-KL25Z only has 9 pwmouts so thats why I only used
9 segments to show 100% of throttle.

******************************************************************/

#include "mbed.h" //// Include mbed main runtime library check www.mbed.org
#define NUM_SEGMENTS 9 //// Define to 9 a constant for the num of led used
#define MAX_THROTTLE 1022.0f //// Define max throttle for math calculus support

/* Definition of LedBar class*/
class LedBar
{
private: //// Private members branch
	PwmOut *Segment[NUM_SEGMENTS]; //// Define a pointer array  of Pwmout
								   //// with 9 of array lenght
	/* 
	private void CalcPWM(); 
	it takes 0 arguments, and return a void argument
	Method that caculates pwmouts in base of throtle selected
	is for internal use of the class
	*/
	void CalcPWM(); 
	int value;		//// internal calc var				
	int Throttle;	//// throttle seted
	int defined;	//// num of pins defined must be 9

public: //// Public members branch
	LedBar(); //// Public default contructor
	~LedBar();//// public default destructor

	/*  
	public void SetPin(int numpin, PinName pin);
	it takes 2 arguments.
	
	this pin construct every pwmout depending of the index of segment

	@argument - int numpin, argument thar indicate the segment index
	@argument - PinName pin, Enumeration of a pin name define in mbed.h
	*/
	void SetPin(int numpin, PinName pin);

	/*
	public void operator= (const int t);
	overloads = operator
	it takes 1 argument that is a const int when you asing 
	a int value to this object
	*/
	void operator= (const int t);
}; //// end definition of class LedBar

//// end of LedBar.h
