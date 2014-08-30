#ifndef _SRF10_H_
#define _SRF10_H_

#include "mbed.h"
#include "UltrasonicBase.h"

#define ADDRESS 0xE0
#define COMMAND 0x00
#define READUS 0x52
#define RANGEBYTE 0x02

class SRF10 : public IUltrasonicSensor
{
public:
    SRF10(PinName sda, PinName scl);
    ~SRF10();
    bool Error;
private:
    I2C *_srf10;
    void ReadRegister();
    
};

#endif