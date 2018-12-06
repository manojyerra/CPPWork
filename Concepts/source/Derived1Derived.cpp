#include "Derived1Derived.h"
#include "DefinesAndIncludes.h"

Derived1Derived::Derived1Derived()
{
	writeStr("\n Derived1Derived class constructor called...");
}

void Derived1Derived::Method1()
{
	writeStr("\n Derived1Derived::Method1 called...");
}

void Derived1Derived::Method2()
{
	writeStr("\n Derived1Derived::Method2 called...");
}

void Derived1Derived::Method3()
{
	writeStr("\n Derived1Derived::Method3 called...");
}

void Derived1Derived::Method4()
{
	writeStr("\n Derived1Derived::Method4 called...");
}

Derived1Derived::~Derived1Derived()
{
	writeStr("\n Derived1Derived class distructor called...");
}