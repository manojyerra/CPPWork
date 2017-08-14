#ifndef BigInteger_H
#define BigInteger_H

#include "VecUInt.h"

#include <iostream>
#include <fstream>

#include "stdint.h"
#include <vector>
#include <string>
using namespace std;


class BigInteger
{
private:
	void LeftShift_LessThan32(unsigned int numBits);
	void LeftShift32BitMultiple(unsigned int multiple);
	void LeftShift(unsigned int numBits);

	void RightShift_LessThan32(unsigned int numBits);
	void RightShift32BitMultiple(unsigned int multiple);
	void RightShift(unsigned int numBits);

	static int addCount;
	static int mulCount;

public:
	VecUInt* vec;

	BigInteger();
	BigInteger(VecUInt* vecUInt);
	BigInteger(unsigned int val, unsigned int vecCapacity);
	BigInteger(unsigned int val);
	BigInteger(uint64_t val);
	~BigInteger();

    BigInteger* Clone();
    BigInteger* CloneAndLeftShiftBytes(int numBytes);
    
    string GetHexString();
    
	bool IsEvenNumber();
	bool IsOddNumber();
	bool IsZero();
    
    static BigInteger* Add		(BigInteger* a, BigInteger* b);
    static BigInteger* Subtract	(BigInteger* a, BigInteger* b);
    static BigInteger* Mul		(BigInteger* a, BigInteger* b);
    static BigInteger* Mul		(BigInteger* a, unsigned int uIntVal);

    void Add		(BigInteger* b);
    void Subtract	(BigInteger* b);
    void Mul		(BigInteger* bigInteger);
    void Mul		(unsigned int uIntVal);

	void MulBy2Power(int power);
	void DivideBy2Power	 (int power);
    
    void MultiplyBy2();
    void DivideBy2();
};

#endif


//static BigInteger* Multiply_Method1(BigInteger* a, BigInteger* b);
//static void Add_Exper(BigInteger* aBigInteger, BigInteger* rBigInteger, int startIndex);
//static void AddBytes(unsigned char* a, unsigned char* r, unsigned int size);
//static BigInteger* Mul_Exper(BigInteger* a, BigInteger* b);

//char GetBitValue(unsigned int index);
//void RightShift32Bits();

//void LeftShift32Bits();
//void LeftShift32BitMultiple(int multiple);

//void DivideBy2Power(int power);
//void MulBy2Power(int power);