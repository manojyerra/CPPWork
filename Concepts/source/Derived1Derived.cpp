#include "Derived1Derived.h"
#include "DefinesAndIncludes.h"

Derived1Derived::Derived1Derived()
{
	print("\n Derived1Derived class constructor called...");
}

void Derived1Derived::Method1()
{
	print("\n Derived1Derived::Method1 called...");
}

void Derived1Derived::Method2()
{
	print("\n Derived1Derived::Method2 called...");
}

void Derived1Derived::Method3()
{
	print("\n Derived1Derived::Method3 called...");
}

void Derived1Derived::Method4()
{
	print("\n Derived1Derived::Method4 called...");
}

Derived1Derived::~Derived1Derived()
{
	print("\n Derived1Derived class distructor called...");
}