#ifndef Base_H
#define Base_H

class Base
{
private:
	virtual void Method3();

public:
	Base();
	
	virtual void Method1();
	void Method2();

	virtual void Method4() = 0;

	virtual ~Base();
};

#endif