#ifndef BigDecimal_H
#define BigDecimal_H

#include "Util/VecUInt.h"
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

	static int addCount;
	static int mulCount;
	static int divCount;

public:
	VecUInt vec;

	string str;

	BigDecimal();
	BigDecimal(BigDecimal* cloneFrom);
	BigDecimal(unsigned int val);
	BigDecimal(uint64_t val);

	bool IsEvenNumber();
	bool IsOddNumber();
	bool IsZero();

	BigDecimal* Multiply(BigDecimal* bigDecimal);
	void MultiplyBy2Power(int power);

	void DivideBy2Power(int power);

	void Add(BigDecimal* bigDecimal);

	char GetBitValue(unsigned int index);


	string ToString();
};

#endif
