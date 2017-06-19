#include "Temp.h"
#include "DefinesAndIncludes.h"

Temp::Temp()
{
	print("\n Temp class constructor called...");
}

Temp::Temp(int param1, int param2)
{
	print("\n Temp class constructor called...");
}

Temp::~Temp()
{
	print("\n Temp class distructor called...");
}
	
void Temp::tempFunc()
{
	print("\n Temp class tempFunc method called...");
}
