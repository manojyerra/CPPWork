#include "Base.h"
#include "DefinesAndIncludes.h"

Base::Base()
{
	writeStr("\n Base class constructor called...");
}

void Base::Method1()
{
	writeStr("\n Base::Method1 called...");
}

void Base::Method2()
{
	writeStr("\n Base::Method2 called...");
}

void Base::Method3()
{
	writeStr("\n Base::Method3 called...");
}

Base::~Base()
{
	writeStr("\n Base class distructor called...");
}