#ifndef Looper_H
#define Looper_H

#include "BigInteger.h"

class NumarAndDenom
{
public:
    BigInteger* numar;
    BigInteger* denom;
};



class Looper
{
private:
	float _windowW;
	float _windowH;

public:
	Looper(int windowWidth, int windowHeight);
	~Looper();

	void Draw(float deltaTime);
};

#endif
