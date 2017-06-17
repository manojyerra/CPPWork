#include "Base.h"
#include "DefinesAndIncludes.h"

Base::Base()
{
	print("\n Base class constructor called...");
}

void Base::Method1()
{
	print("\n Base::Method1 called...");
}

void Base::Method2()
{
	print("\n Base::Method2 called...");
}

void Base::Method3()
{
	print("\n Base::Method3 called...");
}

Base::~Base()
{
	print("\n Base class distructor called...");
}