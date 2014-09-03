// TargetControlSimulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#define IDLE_CONSTANT 511
#define HS_High_Limit 60
#define HS_Medium_Limit 30
#define HS_Low_Limit 10

#define HS_UltraHigh_Correction 320
#define HS_High_Correction 120
#define HS_Medium_Correction 35
#define HS_Low_Correction 12

int ThrottleCorrection(int ErrorDif)
{
	float CalThrottleDif = 0;
	float MaxLimit, MinLimit, MinCorrection, MaxCorrection;

	if (ErrorDif > 2)/// Quad por debajo del target
	{
		if (ErrorDif > HS_High_Limit) /// Diferencia es Grande 60
		{
			MinLimit = HS_High_Limit;
			MinCorrection = HS_High_Correction;
			MaxLimit = 100;
			MaxCorrection = HS_UltraHigh_Correction;
		}
		else if (ErrorDif > HS_Medium_Limit) /// Diferencia es Media 30
		{
			MinLimit = HS_Medium_Limit;
			MinCorrection = HS_Medium_Correction;
			MaxLimit = HS_High_Limit;
			MaxCorrection = HS_High_Correction;
		}
		else if (ErrorDif > HS_Low_Limit) /// Diferencia es Minima 10
		{
			MinLimit = HS_Low_Limit;
			MinCorrection = HS_Low_Correction;
			MaxLimit = HS_Medium_Limit;
			MaxCorrection = HS_Medium_Correction;
		}
		else if (ErrorDif > 2) /// Diferencia es Muy Minima
		{
			MinLimit = 2;
			MinCorrection = 0;
			MaxLimit = HS_Low_Limit;
			MaxCorrection = HS_Low_Correction;
		}
		float NetError = (ErrorDif - MinLimit);
		float NetScale = (MaxLimit - MinLimit);
		float NetGain = (MaxCorrection - MinCorrection);

		CalThrottleDif = ((NetError / NetScale) * NetGain) + MinCorrection;
	
		//CalThrottleDif = (((ErrorDif - MinLimit) / (MaxLimit - MinLimit)) * (MaxCorrection - MinCorrection)) + MinCorrection;
	}
	else if (ErrorDif < -2) /// Quad por encima del target
	{
		ErrorDif *= -1;
		if (ErrorDif > HS_High_Limit) /// Diferencia es Grande 60
		{
			MinLimit = HS_High_Limit;
			MinCorrection = HS_High_Correction;
			MaxLimit = 100;
			MaxCorrection = HS_UltraHigh_Correction;
		}
		else if (ErrorDif > HS_Medium_Limit) /// Diferencia es Media 30
		{
			MinLimit = HS_Medium_Limit;
			MinCorrection = HS_Medium_Correction;
			MaxLimit = HS_High_Limit;
			MaxCorrection = HS_High_Correction;
		}
		else if (ErrorDif > HS_Low_Limit) /// Diferencia es Minima 10
		{
			MinLimit = HS_Low_Limit;
			MinCorrection = HS_Low_Correction;
			MaxLimit = HS_Medium_Limit;
			MaxCorrection = HS_Medium_Correction;
		}
		else if (ErrorDif > 2) /// Diferencia es Muy Minima
		{
			MinLimit = 2;
			MinCorrection = 0;
			MaxLimit = HS_Low_Limit;
			MaxCorrection = HS_Low_Correction;
		}
		
		float NetError = (ErrorDif - MinLimit);
		float NetScale = (MaxLimit - MinLimit);
		float NetGain = (MaxCorrection - MinCorrection);

		CalThrottleDif = ((NetError / NetScale) * NetGain) + MinCorrection;
		CalThrottleDif *= -1;
		//CalThrottleDif = -(((ErrorDif - MinLimit) / (MaxLimit - MinLimit)) * (MaxCorrection - MinCorrection)) + MinCorrection;
	}

	return (int)CalThrottleDif;
}
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int i= 0;
	ofstream file("ouput.csv");

	for (i = -100; i <= 100; i++)
	{
		int output = ThrottleCorrection(i);
		cout << i << "," << output << endl;
		file << i << "," << output << endl;
	}
	file.close();
	char a;
	cin >> a;

	return 0;
}

