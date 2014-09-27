#include "PS_PAD.h"
///
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
	R3
};

enum JAxis
{
	XAxis,
	yAxis,
	ZAxis,
	wAxis
};


class Joystick : private PS_PAD
{
public:
	Joystick();
	~Joystick();

	float GetAxis(unsigned char axis, float DeathZone= 0.0f);
	float 
};

