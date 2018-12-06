#include "Derived1.h"
#include "DefinesAndIncludes.h"

Derived1::Derived1()
{
	val = 1234;

	writeStr("\n Derived1 class constructor called...");
}

void Derived1::PrintValue()
{
	writeStr("\n Derived1::PrintValue, value = %d", val);
}

void Derived1::Method1()
{
	writeStr("\n Derived1::Method1 called...");
}

void Derived1::Method2()
{
	writeStr("\n Derived1::Method2 called...");
}

void Derived1::Method3()
{
	writeStr("\n Derived1::Method3 called...");
}

void Derived1::Method4()
{
	writeStr("\n Derived1::Method4 called...");
}

Derived1::~Derived1()
{
	writeStr("\n Derived1 class distructor called...");
}