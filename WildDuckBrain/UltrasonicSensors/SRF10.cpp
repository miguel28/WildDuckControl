#include "SRF10.h"
Ticker tckReadLength;

SRF10::SRF10(PinName sda, PinName scl) : IUltrasonicSensor()
{
    _srf10 = new I2C(sda, scl);
    Error = false;
    
    char cmd[2];
    
    // Set up SRF10 max range and receiver sensitivity over I2C bus
    cmd[0] = 0x02;                          // Range register
    cmd[1] = 0x1C;                          // Set max range about 100cm
    _srf10->write(ADDRESS, cmd, 2);
    cmd[0] = 0x01;                          // Receiver gain register
    cmd[1] = 0x1B;                          // Set max receiver gain
    _srf10->write(ADDRESS, cmd, 2);
    
    wait(0.1f);
    tckReadLength.attach(this, &SRF10::ReadRegister, 0.12f);  
}

SRF10::~SRF10()
{
    //delete stackBuffer;
}

void SRF10::ReadRegister()
{   
    char data[2] = {COMMAND,READUS};
    char readData[2];
    
    Error = _srf10->write(ADDRESS,data, 2) !=0;

    wait(0.07f);
    
    data[0] = RANGEBYTE;
    Error = _srf10->write(ADDRESS, data,1) !=0;

    if(_srf10->read(ADDRESS, readData,2) == 0)
    {
        CurrentRange = (readData[0] << 8) && readData[1];
        Error = false;
    }
    else Error = true;
    
    AddToStack(CurrentRange);//*/
}

