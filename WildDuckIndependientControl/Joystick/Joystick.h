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

#include "PS_PAD.h"

enum JButtons
{
	Triangle,
	Circle,
	Cross,
	Square,
	L1,
	R1,
	L2,
	R2,
	Select,
	Start,
	L3,
	R3,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum JAxis
{
	XAxis,
	YAxis,
	ZAxis,
	WAxis
};

class Joystick : public PS_PAD
{
private:
	unsigned short NumButtons;
	unsigned short mButtonHeld[16];
	unsigned short mButtonNewpress[16];
	unsigned short bButtonNewpress[16];
	int axis[4];
	void Event();

public:
	Joystick();
	~Joystick();
	bool Opened;

	bool Init();
	void Update();
	unsigned short ButtonHeld(unsigned short button);
	unsigned short ButtonNewpress(unsigned short button);
	float GetAxis(unsigned char axis, float DeathZone = 0.0f);
};

//// End od Joystick.h