#include "Derived2.h"
#include "DefinesAndIncludes.h"

Derived2::Derived2()
{
	writeStr("\n Derived2 class constructor called...");
}

void Derived2::Method1()
{
	writeStr("\n Derived2::Method1 called...");
}

void Derived2::Method2()
{
	writeStr("\n Derived2::Method2 called...");
}

void Derived2::Method3()
{
	writeStr("\n Derived2::Method3 called...");
}

void Derived2::Method4()
{
	writeStr("\n Derived2::Method4 called...");
}

Derived2::~Derived2()
{
	writeStr("\n Derived2 class distructor called...");
}
