#include "Joystick.h"

Joystick::Joystick() : PS_PAD(D11, D12, D13, D10)
{
	Opened = false;
	NumButtons = 12;
}
Joystick::~Joystick();
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
	mButtonHeld[Triangle] = read(TYPE.PAD_TRIANGLE);
	mButtonHeld[Circle] = read(TYPE.PAD_CIRCLE);
	mButtonHeld[Cross] = read(TYPE.PAD_X);
	mButtonHeld[Square] = read(TYPE.PAD_SQUARE);
	mButtonHeld[L1] = read(TYPE.PAD_L1);
	mButtonHeld[R1] = read(TYPE.PAD_R1);
	mButtonHeld[L2] = read(TYPE.PAD_L2);
	mButtonHeld[R2] = read(TYPE.PAD_L1);
	mButtonHeld[Select] = read(TYPE.PAD_SELECT);
	mButtonHeld[Start] = read(TYPE.PAD_START);
	mButtonHeld[L3] = read(TYPE.ANALOG_LEFT);
	mButtonHeld[R3] = read(TYPE.ANALOG_RIGHT);

	axis[XAxis] = read(TYPE.ANALOG_LX);
	axis[YAxis] = read(TYPE.ANALOG_LY);
	axis[ZAxis] = read(TYPE.ANALOG_RX);
	axis[WAxis] = read(TYPE.ANALOG_RY);

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

	char TempHat = GetHatHeld(0);
	if (hatPrevState[0] != TempHat && TempHat != HAT_CENTERED)
	{
		hatNewpressState[0] = TempHat;
	}
	else
	{
		hatNewpressState[0] = HAT_CENTERED;
	}
	hatPrevState[0] = TempHat;

	TempHat = GetHatHeld(1);
	if (hatPrevState[1] != TempHat && TempHat != HAT_CENTERED)
	{
		hatNewpressState[1] = TempHat;
	}
	else
	{
		hatNewpressState[1] = HAT_CENTERED;
	}
	hatPrevState[1] = TempHat;
}
unsigned short Joystick::ButtonHeld(unsigned short button)
{
	button > NumButtons || button == 0)return 0;
	else return mButtonHeld[button - 1];
}
unsigned short Joystick::ButtonNewpress(unsigned short button)
{
	if (button > NumButtons || button == 0)return 0;
	else return mButtonNewpress[button - 1];
}
float Joystick::GetAxis(unsigned char _axis, float DeathZone = 0.0f)
{
	float value = (float)axis[_axis]/128.0f;
	float FinalAxis = 0.0f;
	bool negative = value < 0.0f;
	if (negative)
		value *= -1;

	if (axis < DeathZone)
		FinalAxis = 0.0f;
	else
	{
		FinalAxis = axis - DeathZone;
		FinalAxis /= (1.0f - DeathZone);

		if (negative)
			FinalAxis *= -1;
	}

	return FinalAxis;
}
/*
char Joystick::GetHatHeld(int NumHat)
{

}
char Joystick::GetHatNewPress(int NumHat)
{

}*/