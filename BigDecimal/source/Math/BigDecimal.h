#ifndef BigDecimal_H
#define BigDecimal_H

#include "Util/VecUInt.h"

#include <iostream>
#include <fstream>

#include "stdint.h"
#include <vector>
#include <string>
using namespace std;

class BigDecimal
{
private:
	void LeftShift_LessThan32(int shiftBits);
	void LeftShift32Bits();
	void LeftShift32BitsMultiple(int multiple);

	void RightShift_LessThan32(int shiftBits);
	void RightShift32Bits();

	void MultiplyBy2();
	void DivideBy2();

	static BigDecimal* Multiply_Method1(BigDecimal* a, BigDecimal* b);
	static BigDecimal* Multiply_Method2(BigDecimal* a, BigDecimal* b);

	static int addCount;
	static int mulCount;
	static int divCount;

public:
	VecUInt* vec;

	string str;

	BigDecimal();
	BigDecimal(VecUInt* vecUInt);
	BigDecimal(unsigned int val, unsigned int vecCapacity);
	BigDecimal(unsigned int val);
	BigDecimal(uint64_t val);
	~BigDecimal();

	bool IsEvenNumber();
	bool IsOddNumber();
	bool IsZero();

	BigDecimal* Multiply(BigDecimal* bigDecimal);

	void MultiplyBy2Power(int power);

	void MultiplyWithUInt(unsigned int val);
	void MultiplyWithUInt(BigDecimal* a, unsigned int val, BigDecimal* result, int addFromIndex);

	void DivideBy2Power(int power);

	void Add(BigDecimal* bigDecimal);

	char GetBitValue(unsigned int index);

	BigDecimal* Clone();

	string ToString();
};

#endif
