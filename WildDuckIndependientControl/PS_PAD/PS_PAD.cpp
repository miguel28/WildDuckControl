/*
 * PlayStation Controller library
 * Copyright (c) 2013 Hiroshi Suga
 */

#include "PS_PAD.h"
#ifdef __DEBUG__
Serial pc(USBTX, USBRX);
#endif

PS_PAD::PS_PAD(PinName mosi, PinName miso, PinName sck, PinName cs) : _clk(sck), _mosi(mosi), _miso(miso), _cs(cs) {
	_clk = 1;
	_mosi = 0;
	_cs = 1;
	_vib1 = 0;
	_vib2 = 0;
	_connected = false;
}

uint8_t PS_PAD::SendSPI(uint8_t data)
{
	char i;
	uint8_t retData = 0x00;
	for (i = 0; i < 8; i++)
	{
		uint8_t sbit = (data >> i) & 0x01;
		_mosi = sbit;
		_clk = 0;
		wait_us(6);

		retData |= (_miso << i);
		_clk = 1;
		wait_us(6);
	}
	return retData;
}

int PS_PAD::init() {
	const char enter_config_mode[5] = { 0x01, 0x43, 0x00, 0x01, 0x00 };
	const char enable_analog_mode[9] = { 0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
	const char enable_vibration[9] = { 0x01, 0x4d, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff };
	const char exit_config_mode[9] = { 0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
	char buf[10];

	send(enter_config_mode, 5, buf);
	if (buf[2] == 0xff) {
		return -1;
	}
	wait_ms(16);
	send(enable_analog_mode, 9, buf);
	wait_ms(16);
	send(enable_vibration, 9, buf);
	wait_ms(16);
	send(exit_config_mode, 9, buf);
	wait_ms(16);
	return 0;
}

int PS_PAD::poll() {
	const char poll_command[9] = { 0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	int i;
	char cmd[10], buf[10];

	memcpy(cmd, poll_command, 9);
	cmd[3] = _vib1;
	cmd[4] = _vib2;
	send(cmd, 9, buf);
	if (buf[2] != 0x5a) {
		return -1;
	}

	for (i = 0; i < 6; i++) {
		_pad[i] = buf[3 + i];
	}
	_connected = true;
	return 0;
}

int PS_PAD::read(TYPE t) {
	if (!_connected) {
		if (t <= BUTTONS) {
			return 0;
		}
		else {
			return 0x80;
		}
	}

	switch (t) {
	case PAD_LEFT:
		return _pad[0] & 0x80 ? 0 : 1;
	case PAD_BOTTOM:
		return _pad[0] & 0x40 ? 0 : 1;
	case PAD_RIGHT:
		return _pad[0] & 0x20 ? 0 : 1;
	case PAD_TOP:
		return _pad[0] & 0x10 ? 0 : 1;
	case PAD_START:
		return _pad[0] & 0x08 ? 0 : 1;
	case ANALOG_LEFT:
		return _pad[0] & 0x04 ? 0 : 1;
	case ANALOG_RIGHT:
		return _pad[0] & 0x02 ? 0 : 1;
	case PAD_SELECT:
		return _pad[0] & 0x01 ? 0 : 1;
	case PAD_SQUARE:
		return _pad[1] & 0x80 ? 0 : 1;
	case PAD_X:
		return _pad[1] & 0x40 ? 0 : 1;
	case PAD_CIRCLE:
		return _pad[1] & 0x20 ? 0 : 1;
	case PAD_TRIANGLE:
		return _pad[1] & 0x10 ? 0 : 1;
	case PAD_R1:
		return _pad[1] & 0x08 ? 0 : 1;
	case PAD_L1:
		return _pad[1] & 0x04 ? 0 : 1;
	case PAD_R2:
		return _pad[1] & 0x02 ? 0 : 1;
	case PAD_L2:
		return _pad[1] & 0x01 ? 0 : 1;
	case BUTTONS:
		return ~((_pad[1] << 8) | _pad[0]) & 0xffff;
	case ANALOG_RX:
		return _pad[2] - 0x80;
	case ANALOG_RY:
		return _pad[3] - 0x80;
	case ANALOG_LX:
		return _pad[4] - 0x80;
	case ANALOG_LY:
		return _pad[5] - 0x80;
	}
	return 0;
}

int PS_PAD::vibration(int v1, int v2) {
	_vib1 = v1 ? 1 : 0;
	if (v2 < 0) v2 = 0;
	if (v2 > 0xff) v2 = 0;
	_vib2 = v2;
	poll();
	return 0;
}

int PS_PAD::send(const char *cmd, int len, char *dat) {
	int i;

	_cs = 0;
	wait_us(10);
	for (i = 0; i < len; i++) 
	{
		dat[i] = __rbit(_spi.write(__rbit(cmd[i] << 24)) << 24);
		wait_us(20);
	}
#ifdef __DEBUG__
	pc.printf("Sended:   ");
	for (i = 0; i < len; i++)
		pc.printf("%p, ", cmd[i]);
	pc.printf("\r\n");
	pc.printf("Received: ");
	for (i = 0; i < len; i++)
		pc.printf("%p, ", dat[i]);
	pc.printf("\r\n");
#endif
	_cs = 1;
	return i;
}




///////////////////////////////////////////
Joystick::Joystick() : PS_PAD(D11, D12, D13, D10)
{
	Opened = false;
	NumButtons = 12;
}
Joystick::~Joystick()
{

}

int Joystick::Init()
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

	axis[XAxis] = read(ANALOG_LX);
	axis[YAxis] = read(ANALOG_LY);
	axis[ZAxis] = read(ANALOG_RX);
	axis[WAxis] = read(ANALOG_RY);

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
	/*
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
	hatPrevState[1] = TempHat;*/
}
unsigned short Joystick::ButtonHeld(unsigned short button)
{
	if(button > NumButtons || button == 0)return 0;
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
/*
char Joystick::GetHatHeld(int NumHat)
{

}
char Joystick::GetHatNewPress(int NumHat)
{

}*/