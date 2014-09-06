// SensorsSimulation.cpp : main project file.

#include "stdafx.h"
#include "frmSim.h"
using namespace System;
using namespace SensorsSimulation;
int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	Application::EnableVisualStyles();
	frmSim^ window = gcnew frmSim();
	window->ShowDialog();
	
    return 0;
}
