#ifndef Derived1_H
#define Derived1_H

#include "Base.h"

class Derived1 : public Base
{
private:
	int val;
	
public:
	Derived1();
	
	void PrintValue();

	void Method1();
	void Method2();
	void Method3();
	virtual void Method4();

	~Derived1();
};

#endif