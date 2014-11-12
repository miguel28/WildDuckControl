/******************************************************************
Wild Duck Independient Control
Project Created 8/3/2014
File Joystick.h

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

#include "Joystick.h" //// Include the Joystick.h definitions
/* the Default constructor calls the parent Constructor by
   using the pins D12, D11, D13 and D10 */
Joystick::Joystick() : PS_PAD(D12, D11, D13, D10)
{
	Opened = false; //// Set Opened to false at the begining
	NumButtons = 16; //// Set 16 PS2 Buttons.
}
/*  Default destructor*/
Joystick::~Joystick()
{
	//// Nothing
}

/* Init the configuration of the controller
   calls the parent method int init() */
bool Joystick::Init()
{
	Opened = (init() == 0);
	return Opened; //// return if the controller has been opened successfully
}

/* This Method only calls a parent method of PS_PAD to read
   the new values of the controller, and also calculates the new
   press states of the button.   
*/
void Joystick::Update()
{
	poll();
	Event();
}

/* This fucntion Read from the parent class and stores in my own array
   (this is for reuse my old code that I've been written before)
   
   Example Button [] square Held
   1     ______________________       _______________
   0_____|                     |______|              |___
   
   Example Button [] square Newpress
   1     ______                       ______
   0_____|     |______________________|     |____________
          poll cycle

   The new press waits until the held state be 0.
   */
void Joystick::Event()
{
	
	/* This Block copies the new button structure */
	mButtonHeld[Triangle] = read(PAD_TRIANGLE);
	mButtonHeld[Circle] = read(PAD_CIRCLE);
	mButtonHeld[Cross] = read(PAD_X);
	mButtonHeld[Square] = read(PAD_SQUARE);
	mButtonHeld[L1] = read(PAD_L1);
	mButtonHeld[R1] = read(PAD_R1);
	mButtonHeld[L2] = read(PAD_L2);
	mButtonHeld[R2] = read(PAD_L1);
	mButtonHeld[Select] = read(PAD_SELECT);
	mButtonHeld[Start] = read(PAD_START);
	mButtonHeld[L3] = read(ANALOG_LEFT);
	mButtonHeld[R3] = read(ANALOG_RIGHT);

	/* This Block copies the new digital pad structure */
	mButtonHeld[UP] = read(PAD_TOP);
	mButtonHeld[DOWN] = read(PAD_BOTTOM);
	mButtonHeld[LEFT] = read(PAD_LEFT);
	mButtonHeld[RIGHT] = read(PAD_RIGHT);

	/* This Block copies the new axis structure */
	axis[XAxis] = read(ANALOG_LX);
	axis[YAxis] = read(ANALOG_LY);
	axis[WAxis] = read(ANALOG_RX);
	axis[ZAxis] = read(ANALOG_RY);

	int i; //// for iteration loop control
	
	/* This is for determine any button has been newpressed.
	   To do this I stores the old state in alternative array.
	*/
	for (i = 0; i<NumButtons; i++) //// create a for loop for 16 buttons
	{
		if (mButtonHeld[i]) //// check if the button are pressed
		{
			/* if the button has been pressed in the last
			   state saved the button isn't new pressed	 
			*/
			if (bButtonNewpress[i] == 1){ 
				mButtonNewpress[i] = 0;
				bButtonNewpress[i] = 1;
			}
			/* IF in the last state the button hasn't been pressed (released )
			   then the button is new pressed*/
			else
			{
				mButtonNewpress[i] = 1;
				bButtonNewpress[i] = 1;
			}
		}
		else //// If the button has been released restore all states as released
		{
			bButtonNewpress[i] = 0;
			mButtonNewpress[i] = 0;
		}
	}
}

/* This function only returns the result of the button state 
   calculated in void Update(). 
   This fucntion returns only if a button is pressed or not.
*/
unsigned short Joystick::ButtonHeld(unsigned short button)
{
	if (button > NumButtons || button < 0)return 0;
	else return mButtonHeld[button];
}

/* This function only returns the result of the button state
calculated in void Update().
This fucntion returns if a button is new pressed or not.
*/
unsigned short Joystick::ButtonNewpress(unsigned short button)
{
	if (button > NumButtons || button < 0)return 0;
	else return mButtonNewpress[button];
}

/* This method returns the value of the selected axis in the parameter
   unsigned char _axis. Also it calculated a defined deathzone ( by default 0.0f)

*/
float Joystick::GetAxis(unsigned char _axis, float DeathZone)
{
	/* the raw data retrieved of the controller is for a 
	   8 bits  digital value of any axis. 
	   The values are int between -128 minor value of axis, 
	   0 is the center of the stick.
	   128 the maximun value of the stick.

	   -128     0       128
	   __________________
	   |                | -128
	   |                |
	   |       00       |
	   |      0000      | 0
	   |       00       |
	   |                |
	   |________________| 128

	   So that why I Create a convertion by using a division by
	   128.0f, to get float values between -1.0f and 1.0f.

	   -1.0f   0.0f      1.0f
	   __________________
	   |                | -1.0f
	   |                |
	   |       00       |
	   |      0000      | 0.0f
	   |       00       |
	   |                |
	   |________________| 1.0f
	*/
	float value = (float)axis[_axis] / 128.0f;

	/* The rest of the instruction is for manage the death zone correction
	   this correction is usefull if the controller has variation in the center
	   of the stick.

	   The death zone means that the real value retrieved for the controller
	   is less or equal thet the deathzone value, the return value is 0.0f
	   tI do this in order to avoid falses value of the stick then the stick is
	   in the center.

	   When the real stick values gets greater of the death zone value
	   a new axis scale is calculated from this value.

	   For example. Supose that we have a real axis value of 0.5f and the death
	   zone value is 0.25f, the return value is 0.3333f

	   Finalvalue = (RV - DZV)/(1 - DZV)

	   Where RV = Real Value
	         DZV = Death Zone value.

	*/
	float FinalAxis = 0.0f;
	bool negative = value < 0.0f;
	if (negative)
		value *= -1;

	if (value < DeathZone)
		FinalAxis = 0.0f;
	else
	{
		FinalAxis = value - DeathZone;
		FinalAxis /= (1.0f - DeathZone);

		if (negative)
			FinalAxis *= -1;
	}

	return FinalAxis;
}
//// End of file Joystick.cpp
