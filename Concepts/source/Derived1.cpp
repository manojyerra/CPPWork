#include "Derived1.h"
#include "DefinesAndIncludes.h"

Derived1::Derived1()
{
	print("\n Derived1 class constructor called...");
}

void Derived1::Method1()
{
	print("\n Derived1::Method1 called...");
}

void Derived1::Method2()
{
	print("\n Derived1::Method2 called...");
}

void Derived1::Method3()
{
	print("\n Derived1::Method3 called...");
}

Derived1::~Derived1()
{
	print("\n Derived1 class distructor called...");
}