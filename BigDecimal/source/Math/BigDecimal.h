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

	bool _delVector;

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

	void SetDeleteVector(bool del);

	bool IsEvenNumber();
	bool IsOddNumber();
	bool IsZero();

	BigDecimal* Multiply(BigDecimal* bigDecimal);
	void MultiplyBy2Power(int power);

	void DivideBy2Power(int power);

	void Add(BigDecimal* bigDecimal);

	char GetBitValue(unsigned int index);

	BigDecimal* Clone();

	string ToString();
};

#endif
