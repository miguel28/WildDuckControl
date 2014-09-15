#include "UltrasonicBase.h"

IUltrasonicSensor::IUltrasonicSensor()
{
    stackPointer = 0;
	STACKAVERAGE = 10;
    stackBuffer = new float[STACKAVERAGE];  
    IgnoreLectures = false;
}

IUltrasonicSensor::IUltrasonicSensor(int stack)
{
	stackPointer = 0;
	STACKAVERAGE = stack;
	stackBuffer = new float[STACKAVERAGE];
	IgnoreLectures = false;
}

IUltrasonicSensor::~IUltrasonicSensor()
{
    delete stackBuffer;
}

///uS/58=cm or uS/148=inches.
float IUltrasonicSensor::GetCentimeter()
{
	return GetAverrage() / CONVERSIONRANGE;
}

float IUltrasonicSensor::GetInches()
{
	return GetAverrage() / CONVERSIONRANGE_IN;
}

float IUltrasonicSensor::GetAverrage()
{
    int i;
    float avr = 0;
    for(i=0; i< stackPointer; i++)
    {
        avr += stackBuffer[i];
    }
    return avr/(float)stackPointer;
}

void IUltrasonicSensor::AddToStack(float range)
{
    if(stackPointer >= STACKAVERAGE)
    {
        float *newstack = new float[STACKAVERAGE];
        int i;
        for(i = 0; i< STACKAVERAGE -1; i++)
            newstack[i] = stackBuffer[i+1]; 
		delete stackBuffer;
		stackBuffer = newstack;
		stackBuffer[STACKAVERAGE - 1] = range;
    }
    else
    {
        stackBuffer[stackPointer] = range;
        stackPointer++;
    }       
}