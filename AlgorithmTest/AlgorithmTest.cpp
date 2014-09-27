// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
using namespace std;

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

int _tmain(int argc, _TCHAR* argv[])
{
	char test1 = 0xf0;
	int test2 = 0x23459f;

	char btest1 = __rbit8(test1);
	int btest2 = __rbit(test2);

	cout << hex << (int)btest1 << " , " << btest2 << endl;

	system("pause");
	return 0;
}

