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

#include "PS_PAD.h" //// Includes PS_PAD.h headers.

/*
	In this file include the definition of Joystick class
	that inherits the members of a PS_PAD class and manage also
	a newpress state of the buttons and create a final user
	API like Joystick on a CSharp write that a been writed before, 
	and also the MK_Input.cpp  used in the watchdog interface. 
*/


/* Enum definition of the name of the buttons*/
enum JButtons
{
	Triangle, //// 0x00
	Circle,   //// 0x01
	Cross,    //// 0x02
	Square,   //// 0x03
	L1,       //// 0x04
	R1,       //// 0x05
	L2,       //// 0x06
	R2,       //// 0x07
	Select,   //// 0x08
	Start,    //// 0x08
	L3,       //// 0x09
	R3,       //// 0x0A
	UP,       //// 0x0B
	DOWN,     //// 0x0C
	LEFT,     //// 0x0D
	RIGHT     //// 0x0E
};

/* Enum definition of the Axis*/
enum JAxis
{
	XAxis, //// 0x00
	YAxis, //// 0x01
	ZAxis, //// 0x02
	WAxis  //// 0x03
};

/* Definition of a class Joystick */
class Joystick : public PS_PAD //// Inherits from PS_PAD as public
{
	/* Private members */
private:
	/* Stores on a buffer the polled button states from
	PS_PAD */
	unsigned short NumButtons; //// = 16 num buttons
	unsigned short mButtonHeld[16];
	unsigned short mButtonNewpress[16];
	unsigned short bButtonNewpress[16];
	int axis[4]; //// 4 axis defined

	/* Function that takes the buttons states from PS_PAD class
	   and convets it to a new buffer format ( this is for reuse a code
	   that a I've generated before) */
	void Event(); 

	/* Public members*/
public:
	Joystick(); //// Default contructor
	~Joystick(); //// Default Destructor
	bool Opened; //// Indicates if the Joystick is connected.

	bool Init(); //// Function that initialized the joystick
	void Update(); ////  Method that Update the state of the buttons
	
	/*Public method that returns the state of a button if is pressed or not*/
	unsigned short ButtonHeld(unsigned short button);

	/* Public methods that return the state of the button if 
	   the button has been when the before state was not,
	   in order to catch the new press event
	*/
	unsigned short ButtonNewpress(unsigned short button);

	/* Get the value of the selected axis in a float range of -1.0f and 1.0f 
	   Also calculates the result of the axis by using a death zone, by default
	   this DeathZone is 0.0f (no death zone).
	*/
	float GetAxis(unsigned char axis, float DeathZone = 0.0f);
};/* Definition of a class Joystick */

//// End of Joystick.h