#include "Temp.h"
#include "DefinesAndIncludes.h"

Temp::Temp()
{
	writeStr("\n Temp class constructor called...");
}

Temp::Temp(int param1, int param2)
{
	writeStr("\n Temp class constructor called...");
}

//Temp::Temp(const Temp& temp)
//{
//	int a = 10;
//	int b = 10;
//	int c = a;
//
//}

Temp::~Temp()
{
	writeStr("\n Temp class distructor called...");
}
	
void Temp::tempFunc()
{
	writeStr("\n Temp class tempFunc method called...");
}
