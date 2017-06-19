#ifndef Derived1Derived_H
#define Derived1Derived_H

#include "Derived1.h"

class Derived1Derived : public Derived1
{
private:
	
public:
	Derived1Derived();
	
	virtual void Method1();
	void Method2();
	void Method3();
	void Method4();

	~Derived1Derived();
};

#endif