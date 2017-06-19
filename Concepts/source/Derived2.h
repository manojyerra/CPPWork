#ifndef Derived2_H
#define Derived2_H

#include "Base.h"

class Derived2 : public Base
{
private:
	
public:
	Derived2();
	
	void Method1();
	void Method2();
	void Method3();
	virtual void Method4();

	~Derived2();
};

#endif