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
	void LeftShift_LessThan32(int shiftBits);
	void LeftShift32Bits();
	void LeftShift32BitMultiple(int multiple);

	void RightShift_LessThan32(int shiftBits);
	void RightShift32Bits();
    
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
    char GetBitValue(unsigned int index);
    
    void Add(BigInteger* b);
    static BigInteger* Add(BigInteger* a, BigInteger* b);

    void Subtract(BigInteger* b);
    static BigInteger* Subtract(BigInteger* a, BigInteger* b);
    
    static BigInteger* Mul(BigInteger* a, BigInteger* b);
    static BigInteger* Mul(BigInteger* a, unsigned int uIntVal);
    
    void Mul(BigInteger* bigInteger);
    void Mul(unsigned int uIntVal);
    
    void MultiplyBy2();
    void MulBy2Power(int power);
    
    void DivideBy2();
    void DivideBy2Power(int power);
};

#endif


//static BigInteger* Multiply_Method1(BigInteger* a, BigInteger* b);
//static void Add_Exper(BigInteger* aBigInteger, BigInteger* rBigInteger, int startIndex);
//static void AddBytes(unsigned char* a, unsigned char* r, unsigned int size);
//static BigInteger* Mul_Exper(BigInteger* a, BigInteger* b);
