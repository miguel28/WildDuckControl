/*
 * PlayStation Controller library
 * Copyright (c) 2013 Hiroshi Suga
 */

#include "mbed.h"
#define USE_ORIGINAL

enum TYPE {
	PAD_LEFT,
	PAD_BOTTOM,
	PAD_RIGHT,
	PAD_TOP,
	PAD_START,
	ANALOG_LEFT,
	ANALOG_RIGHT,
	PAD_SELECT,
	PAD_SQUARE,
	PAD_X,
	PAD_CIRCLE,
	PAD_TRIANGLE,
	PAD_R1,
	PAD_L1,
	PAD_R2,
	PAD_L2,
	BUTTONS,
	ANALOG_RX,
	ANALOG_RY,
	ANALOG_LX,
	ANALOG_LY,
};

class PS_PAD {
public:
    PS_PAD (PinName mosi, PinName miso, PinName sck, PinName cs);
    PS_PAD (SPI &spi, PinName cs);

    int init ();
    int poll ();
    int read (TYPE t);
    int vibration (int v1, int v2);

private:
    SPI _spi;
    DigitalOut _cs;
    uint8_t _pad[6];
    int _vib1, _vib2;
    bool _connected;

    int send (const char *cmd, int len, char *dat);
};

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
	YAxis,
	ZAxis,
	WAxis
};




class Joystick : public PS_PAD
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

	int Init();
	void Update();
	unsigned short ButtonHeld(unsigned short button);
	unsigned short ButtonNewpress(unsigned short button);
	float GetAxis(unsigned char axis, float DeathZone = 0.0f);
	//char GetHatHeld(int NumHat);
	//char GetHatNewPress(int NumHat);
};


