/*
 * PlayStation Controller library
 * Copyright (c) 2013 Hiroshi Suga
 */

#include "PS_PAD.h"
#include "BufferedSerial.h"
BufferedSerial pc(USBTX, USBRX);

uint32_t __rbit(uint32_t value)
{
	uint32_t newvalue = 0;
	uint16_t i;
	uint32_t tempValue = 0;
	for (i = 0; i < 32; i++)
	{
		tempValue = value & (1 << i);
		bool bit = tempValue > 0;
		newvalue |= (bit << (31 - i));
	}
	return newvalue;
}

uint8_t __rbit8(uint8_t value)
{
	uint8_t newvalue = 0;
	uint16_t i;
	uint8_t tempValue = 0;
	for (i = 0; i < 8; i++)
	{
		tempValue = value & (1 << i);
		bool bit = tempValue > 0;
		newvalue |= (bit << (7 - i));
	}
	return newvalue;
}

PS_PAD::PS_PAD (PinName mosi, PinName miso, PinName sck, PinName cs) : _spi(mosi, miso, sck), _cs(cs) {
    _spi.format(8, 3);
    _spi.frequency(250000);
    _cs = 1;
    _vib1 = 0;
    _vib2 = 0;
    _connected = false;
}

PS_PAD::PS_PAD (SPI &spi, PinName cs) : _spi(spi), _cs(cs) {
    _spi.format(8, 3);
    _spi.frequency(250000);
    _cs = 1;
    _vib1 = 0;
    _vib2 = 0;
    _connected = false;
}

int PS_PAD::init () {
    const char enter_config_mode[5]  = {0x01, 0x43, 0x00, 0x01, 0x00};
    const char enable_analog_mode[9] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
    const char enable_vibration[9]   = {0x01, 0x4d, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff};
    const char exit_config_mode[9]   = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
    char buf[10];

	pc.printf("EnterConfig: \r\n");
    send(enter_config_mode, 5, buf);

    if (buf[2] == 0xff) {
        //return -1;
		return buf[2];
    }
	
    wait_ms(16);
	pc.printf("Analog: \r\n");
    send(enable_analog_mode, 9, buf);
    wait_ms(16);
	pc.printf("Vibration: \r\n");
    send(enable_vibration, 9, buf);
    wait_ms(16);
	pc.printf("Exit: \r\n");
    send(exit_config_mode, 9, buf);
    wait_ms(16);
    return 0;
}

int PS_PAD::poll () {
    const char poll_command[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int i;
    char cmd[10], buf[10];

    memcpy(cmd, poll_command, 9);
    cmd[3] = _vib1;
    cmd[4] = _vib2;
    send(cmd, 9, buf);
    if (buf[2] != 0x5a) {
        return -1;
    }

    for (i = 0; i < 6; i ++) {
        _pad[i] = buf[3 + i];
    }
    _connected = true;

	pc.printf("Axis: %4.4f\r\n", _pad[4]);

    return 0;
}

int PS_PAD::read (TYPE t) {
    if (!_connected) {
        if (t <= BUTTONS) {
            return 0xff;
        } else {
            return 0xff;
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

int PS_PAD::vibration (int v1, int v2) {
    _vib1 = v1 ? 1 : 0;
    if (v2 < 0) v2 = 0;
    if (v2 > 0xff) v2 = 0;
    _vib2 = v2;
    poll();
    return 0;
}

int PS_PAD::send (const char *cmd, int len, char *dat) {
    int i;

    _cs = 0;
    wait_us(10);
    for (i = 0; i < len; i ++) {
#ifdef USE_ORIGINAL
        dat[i] = __rbit(_spi.write(__rbit(cmd[i] << 24)) << 24);
#else
		dat[i] = __rbit8(_spi.write( __rbit8(cmd[i]) ) );
#endif
        wait_us(10);
    }
    _cs = 1;

	//int i = 0;
	for (i = 0; i < 10; i++)
		pc.printf("%p, ", dat[i]);
	pc.printf("\r\n");
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