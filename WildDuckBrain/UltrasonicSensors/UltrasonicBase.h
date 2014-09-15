#ifndef _ULTRASONIC_BASE_H_
#define _ULTRASONIC_BASE_H_

//#define STACKAVERAGE 10
#define CONVERSIONRANGE 58.0f 
#define CONVERSIONRANGE_IN 148.0f
class IUltrasonicSensor
{
public:
    IUltrasonicSensor();
	IUltrasonicSensor(int stack);
    ~IUltrasonicSensor();

    float GetCentimeter();
    float GetInches();
    
    bool IgnoreLectures;
    float CurrentRange;
    float CurrentInches;
    float CurrentCentimeters;
protected:   
    int stackPointer;
    float *stackBuffer;
	int STACKAVERAGE;

    void AddToStack(float range);
    float GetAverrage();
};

#endif