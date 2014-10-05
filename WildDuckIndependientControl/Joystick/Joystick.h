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