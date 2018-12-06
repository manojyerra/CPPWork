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

Temp::~Temp()
{
	writeStr("\n Temp class distructor called...");
}
	
void Temp::tempFunc()
{
	writeStr("\n Temp class tempFunc method called...");
}
