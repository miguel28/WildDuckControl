#include "mbed.h"
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
private:
	unsigned short NumButtons;
	unsigned short mButtonHeld[12];
	unsigned short mButtonNewpress[12];
	unsigned short bButtonNewpress[12];
	char hatPrevState[5];
	char hatNewpressState[5];
	char hatHeldState[5];
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
	float GetAxis(unsigned char axis, float DeathZone= 0.0f);
	//char GetHatHeld(int NumHat);
	//char GetHatNewPress(int NumHat);
};

