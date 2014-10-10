#include "Joystick.h"

Joystick::Joystick() : PS_PAD(D12, D11, D13, D10)
{
	Opened = false;
	NumButtons = 14;
}
Joystick::~Joystick()
{

}

bool Joystick::Init()
{
	Opened = init() == 0;
	return Opened;
}
void Joystick::Update()
{
	poll();
	Event();
}

void Joystick::Event()
{
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

	mButtonHeld[UP] = read(PAD_TOP);
	mButtonHeld[DOWN] = read(PAD_BOTTOM);
	mButtonHeld[LEFT] = read(PAD_LEFT);
	mButtonHeld[RIGHT] = read(PAD_RIGHT);

	axis[XAxis] = read(ANALOG_LX);
	axis[YAxis] = read(ANALOG_LY);
	axis[WAxis] = read(ANALOG_RX);
	axis[ZAxis] = read(ANALOG_RY);

	int i;
	for (i = 0; i<NumButtons; i++)
	{
		if (mButtonHeld[i])
		{
			if (bButtonNewpress[i] == 1){
				mButtonNewpress[i] = 0;
				bButtonNewpress[i] = 1;
			}
			else
			{
				mButtonNewpress[i] = 1;
				bButtonNewpress[i] = 1;
			}
		}
		else
		{
			bButtonNewpress[i] = 0;
			mButtonNewpress[i] = 0;
		}
	}
}
unsigned short Joystick::ButtonHeld(unsigned short button)
{
	if (button > NumButtons || button == 0)return 0;
	else return mButtonHeld[button - 1];
}
unsigned short Joystick::ButtonNewpress(unsigned short button)
{
	if (button > NumButtons || button == 0)return 0;
	else return mButtonNewpress[button - 1];
}
float Joystick::GetAxis(unsigned char _axis, float DeathZone)
{
	float value = (float)axis[_axis] / 128.0f;
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
