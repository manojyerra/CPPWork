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
	void MultiplyBy2();

public:
	//vector<unsigned int> vec;
	VecUInt vec;

	string str;

	BigDecimal();
	BigDecimal(BigDecimal* cloneFrom);
	BigDecimal(unsigned int val);
	BigDecimal(uint64_t val);

	bool IsEvenNumber();
	bool IsOddNumber();
	bool IsZero();

	void MultiplyBy2Power(int power);
	BigDecimal* Multiply(BigDecimal* bigDecimal);
	void DivideBy2();
	void Add(BigDecimal* bigDecimal);

	string ToString();
};

#endif
