#include "BigInteger.h"
#include "BaseConverter.h"
#include "DefinesAndIncludes.h"

int BigInteger::addCount = 0;
int BigInteger::mulCount = 0;


BigInteger::BigInteger()
{
	vec = new VecUInt();
	vec->push_back(0);
}


BigInteger::BigInteger(VecUInt* vecUInt)
{
	vec = vecUInt;
}


BigInteger::BigInteger(unsigned int val, unsigned int vecCapacity)
{
	vec = new VecUInt(vecCapacity);
	vec->push_back(val);
}


BigInteger::BigInteger(unsigned int val)
{
	vec = new VecUInt();
	vec->push_back(val);
}


BigInteger::BigInteger(uint64_t val)
{
	vec = new VecUInt();

	unsigned int intVal0 = (unsigned int)((val << 32 ) >> 32);
	unsigned int intVal1 = (unsigned int)(val >> 32);

	vec->push_back(intVal0);

	if(intVal1 > 0)
		vec->push_back(intVal1);
}


BigInteger* BigInteger::Clone()
{
    VecUInt* newVec = vec->Clone();
    
    return new BigInteger(newVec);
}


BigInteger* BigInteger::CloneAndLeftShiftBytes(int numBytes)
{
    VecUInt* newVec = vec->CloneAndLeftShiftBytes(numBytes);
    
    return new BigInteger(newVec);
}


bool BigInteger::IsEvenNumber()
{
	bool isEven = true;

	if(vec->size() > 0)
		isEven = (vec->at(0) % 2 == 0);

	return isEven;
}


bool BigInteger::IsOddNumber()
{
	bool isOdd = false;

	if(vec->size() > 0)
		isOdd = (vec->at(0) % 2 == 1);

	return isOdd;
}


bool BigInteger::IsZero()
{
	bool isZero = false;

	if(vec->size() == 0)
		isZero = true;
	else if(vec->size() == 1)
		isZero = (vec->at(0) == 0);

	return isZero;
}


void BigInteger::LeftShift_LessThan32(unsigned int leftShiftBits)
{
	unsigned int rightShiftBits = sizeof(int)*8 - leftShiftBits;
	unsigned int carry = 0;

	unsigned int size = vec->size();
	unsigned int* arr = vec->GetArray();

	for(unsigned int i=0; i<size; i++)
	{
		unsigned int val = arr[i];

		arr[i] = (val << leftShiftBits) | carry;

		carry = val >> rightShiftBits;
	}

	if(carry != 0)
		vec->push_back(carry);
}


void BigInteger::LeftShift32BitMultiple(unsigned int multiple)
{
	unsigned int size = vec->size();

	for(int i=0; i<multiple; i++)
		vec->push_back(0);

	unsigned int* arr = vec->GetArray();

	for(int i=size-1; i>=0; i--)
		arr[i+multiple] = arr[i];

	for(int i=0; i<multiple; i++)
		arr[i] = 0;
}


void BigInteger::LeftShift(unsigned int numBits)
{
	if(numBits == 0)
		return;

	int sizeOfUInt = sizeof(unsigned int) * 8;

	int num32BitsShift = numBits / sizeOfUInt;
	int remainderBits = numBits % sizeOfUInt;

	if(num32BitsShift)
		LeftShift32BitMultiple( num32BitsShift );

	if(remainderBits > 0)
		LeftShift_LessThan32( remainderBits );
}


void BigInteger::RightShift_LessThan32(unsigned int rightShiftBits)
{
	unsigned int size = vec->size();

	if(size <= 0)
		return;

	unsigned int leftShiftBits = sizeof(int)*8 - rightShiftBits;
	unsigned int carry = 0;

	unsigned int* arr = vec->GetArray();

	for(unsigned int i=size-1; ; i--)
	{
		unsigned int val = arr[i];

		arr[i] = (val >> rightShiftBits) | carry;

		carry = val << leftShiftBits;

		if(i == 0)
			break;
	}

	if(arr[size-1] == 0)
		vec->pop_back();
}


void BigInteger::RightShift32BitMultiple(unsigned int multiple)
{
	unsigned int size = vec->size();

	unsigned int* arr = vec->GetArray();

	for(int i=0; i<size-multiple; i++)
		arr[i] = arr[i+multiple];

	for(int i=size-multiple; i<size; i++)
	{
		arr[i] = 0;
		vec->pop_back();
	}
}


void BigInteger::RightShift(unsigned int numBits)
{
	if(numBits == 0)
		return;

	int sizeOfUInt = sizeof(unsigned int) * 8;

	int num32BitsShift = numBits / sizeOfUInt;
	int remainderBits = numBits % sizeOfUInt;

	if(num32BitsShift)
		RightShift32BitMultiple( num32BitsShift );

	if(remainderBits > 0)
		RightShift_LessThan32( remainderBits );
}


void BigInteger::MulBy2Power(int power)
{
	if(power < 32)
		LeftShift_LessThan32(1);
	else
		LeftShift(power);
}


void BigInteger::DivideBy2Power(int power)
{
	if(power < 32)
		RightShift_LessThan32(1);
	else
		RightShift(power);
}


void BigInteger::MultiplyBy2()
{
	LeftShift_LessThan32(1);
}


void BigInteger::DivideBy2()
{
	RightShift_LessThan32(1);
}


void BigInteger::Mul(unsigned int uIntVal)
{
	unsigned int* vecArr = vec->GetArray();
	unsigned int vecSize = vec->size();

    uint64_t val = uIntVal;
	uint64_t sum = 0;

	for(int i=0; i<vecSize; i++)
	{
		sum = (uint64_t)vecArr[i] * val + (sum >> 32);

		vecArr[i] = (unsigned int) ((sum << 32) >> 32);
	}

	if((sum >> 32) != 0)
		vec->push_back((sum >> 32));
}


BigInteger* BigInteger::Mul(BigInteger* a, unsigned int uIntVal)
{
    BigInteger* result = a->Clone();
    
    unsigned int* vecArr = result->vec->GetArray();
    unsigned int vecSize = result->vec->size();
    
    uint64_t val = uIntVal;
    uint64_t sum = 0;
    
    for(int i=0; i<vecSize; i++)
    {
        sum = (uint64_t)vecArr[i] * val + (sum >> 32);
        
        vecArr[i] = (unsigned int) ((sum << 32) >> 32);
    }
    
    if((sum >> 32) != 0)
        result->vec->push_back((sum >> 32));
    
    return result;
}


void BigInteger::Mul(BigInteger* b)
{
    BigInteger* result = Mul(this, b);
    
    delete vec;
    
    vec = result->vec;
    
    result->vec = NULL;
    
    delete result;
}


BigInteger* BigInteger::Mul(BigInteger* a, BigInteger* b)
{
	//uint64_t startTime = GetTickCount();

    if(a->vec->size() < b->vec->size())
    {
        BigInteger* temp = a;
        a = b;
        b = temp;
    }
    
    unsigned int bVecSize = b->vec->size();
    unsigned int* bVecIter = b->vec->GetArray();
    
    unsigned int aVecSize = a->vec->size();
    unsigned int* aVecIter = a->vec->GetArray();
    
    unsigned int resultSize = bVecSize + a->vec->size() + 1;
    
    BigInteger* result = new BigInteger(0, resultSize+1024);
    result->vec->setSize(resultSize);
    
    memset(result->vec->GetArray(), 0, result->vec->capacity()*sizeof(unsigned int));
    
    unsigned int* r = result->vec->GetArray();
    
    for(int j=0; j<bVecSize; j++)
    {
        unsigned int val = bVecIter[j];
        
        uint64_t mulSum = 0;
        
        int i=0;
        
        if( aVecSize > 10)
        {
            for(; i<aVecSize-10; i++)
            {
                //mulSum = (uint64_t)aVecIter[i] * (uint64_t)val + r[i+j] + (mulSum >> 32);
                //r[j+i] = (unsigned int) mulSum; i++;
                
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));    i++;
                r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));
            }
        }

        for(; i<aVecSize; i++)
        {
            //mulSum = (uint64_t)aVecIter[i] * (uint64_t)val + r[i+j] + (mulSum >> 32);
            //r[j+i] = (unsigned int) ((mulSum << 32) >> 32);
            
            r[i+j] = (unsigned int)  (mulSum = ((uint64_t)aVecIter[i] * val + r[i+j] + (mulSum >> 32)));
        }
        
        r[j+aVecSize] = (mulSum >> 32);
    }
    
    for(int i=result->vec->size()-1; i>=0; i--)
    {
        if(r[i] == 0)
            result->vec->pop_back();
        else
            break;
    }

	//mulCount+= GetTickCount() - startTime;
    
    return result;
}

void BigInteger::Add(BigInteger* b)
{
    BigInteger* result = Add(this, b);
    
    delete vec;
    
    vec = result->vec;
    
    result->vec = NULL;
    
    delete result;
}

BigInteger* BigInteger::Add(BigInteger* a, BigInteger* b)
{
    //uint64_t startTime = GetTickCount();
    
    if(a->vec->size() < b->vec->size())
    {
        BigInteger* temp = a;
        a = b;
        b = temp;
    }
    
    BigInteger* result = a->Clone();
     
    unsigned int aVecSize = a->vec->size();
    unsigned int bVecSize = b->vec->size();
    
    unsigned int* aVecArr = a->vec->GetArray();
    unsigned int* bVecArr = b->vec->GetArray();
    unsigned int* r = result->vec->GetArray();

    uint64_t sum = 0;

    for(int i=0; i<bVecSize; i++)
    {
        r[i] = (unsigned int) (sum = (uint64_t)aVecArr[i] + (uint64_t)bVecArr[i] + (sum >> 32));
    }
    
    for(int i=bVecSize; i<aVecSize; i++)
    {
        r[i] = (unsigned int) ( sum = (uint64_t)aVecArr[i] + (sum >> 32)) ;
        
        if((sum >> 32) == 0)
            break;
    }
    
    if((sum >> 32) != 0)
    {
        result->vec->push_back((sum >> 32));
    }
    
    //addCount += GetTickCount() - startTime;
    
    return result;
}


void BigInteger::Subtract(BigInteger* b)
{
    BigInteger* result = Add(this, b);
    
    delete vec;
    
    vec = result->vec;
    
    result->vec = NULL;
    
    delete result;
}


BigInteger* BigInteger::Subtract(BigInteger* a, BigInteger* b)
{
    if(a->vec->size() < b->vec->size())
    {
        BigInteger* temp = a;
        a = b;
        b = temp;
    }
    else if(a->vec->size() == b->vec->size())
    {
        unsigned int* aArr = a->vec->GetArray();
        unsigned int* bArr = b->vec->GetArray();
        
        unsigned int size = a->vec->size();
        
        for(int i=0; i<size; i++)
        {
            if(aArr[i] == bArr[i])
                continue;
            
            if(aArr[i] < bArr[i])
            {
                BigInteger* temp = a;
                a = b;
                b = temp;
            }
            
            break;
        }
    }
    
    VecUInt* resultVec = a->vec->Clone();
    
    BigInteger* result = new BigInteger(resultVec);
    
    unsigned int* aVecArr = a->vec->GetArray();
    unsigned int* bVecArr = b->vec->GetArray();
    unsigned int* resultVecArr = resultVec->GetArray();
    
    unsigned int aVecSize = a->vec->size();
    unsigned int bVecSize = b->vec->size();
    
    uint64_t sum = 0;
    
    for(int i=0; i<aVecSize; i++)
    {
        if(i < bVecSize)
        {
            sum = (uint64_t)aVecArr[i] - (uint64_t)bVecArr[i] - (sum >> 32);
            
            resultVecArr[i] = (unsigned int) ((sum << 32) >> 32);
        }
        else
        {
            sum = (uint64_t)aVecArr[i] + (sum >> 32);
            
            resultVecArr[i] = (unsigned int) ((sum << 32) >> 32);
            
            if((sum >> 32) == 0)
                break;
        }
    }
    
    return result;
}


string BigInteger::GetHexString()
{
	writeConsole("\n mulCount : %d", (int)mulCount);

    addCount = 0;
    mulCount = 0;

	const BaseConverter& dec2hex = BaseConverter::DecimalToHexConverter();

	string hexString;

	for(int i=vec->size()-1; i>=0; i--)
	{
		string temp = dec2hex.FromDecimal(vec->at(i));

		unsigned int len = temp.length();

		if(len < 8)
			temp = std::string( 8-len, '0').append( temp);

		hexString.append( temp );
	}

	/////////////////////////////////// Begin : Debug code  ///////

	int zeroCount = 0;
	int hexLen = hexString.length();

	for(int i=0; i<hexLen; i++)
	{
		if(hexString[i] == '0')
			zeroCount++;
		else
			break;
	}

	if(zeroCount >= 8 && hexString.length() > 8)
	{
		int a = 1;
		int b = 0;
		int c = a / b;

		printf("throw exception");
	}

	/////////////////////////////////////// End : Debug code ////////

//	std::ofstream hexFile("outputHex.txt");
//	hexFile << hexString;
//	hexFile.close();
//
//	const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();
//	str = hex2dec.Convert(hexString);
//
//	std::ofstream decimalFile("outputDecimal.txt");
//	decimalFile << str;
//	decimalFile.close();
//
//	return str;
    
    return hexString;
}


BigInteger::~BigInteger()
{
	if(vec)
	{
		delete vec;
		vec = NULL;
	}
}


//BigInteger* BigInteger::Multiply(BigInteger* b)
//{
//	BigInteger* result = new BigInteger();
//
//	int twoPower = 0;
//
//	int bitIndex = 0;
//	int loopCount = 0;
//
//	char bitVal = b->GetBitValue(bitIndex);
//
//	while(bitVal >= 0)
//	{
//		loopCount++;
//
//		if(bitVal == 1)
//		{
//			if(twoPower > 0)
//			{
//				MultiplyBy2Power( twoPower );
//
//				twoPower = 0;
//			}
//
//			result->Add(this);
//		}
//
//		twoPower++;
//		bitIndex++;
//
//		bitVal = b->GetBitValue(bitIndex);
//	}
//
//	return result;
//}


//BigInteger* BigInteger::Multiply(BigInteger* a, BigInteger* b)
//{
//	int twoPower = 0;
//
//	unsigned int bVecSize = b->vec->size();
//	unsigned int* bVecIter = b->vec->GetArray();
//
//	BigInteger* result = new BigInteger(0, bVecSize + a->vec->size() + 2);
//
//	for(int i=0; i<bVecSize; i++)
//	{
//		unsigned int val = (*bVecIter);
//
//		for(int bitIndex=0; bitIndex<32; bitIndex++)
//		{
//			unsigned int bitVal = ((val << (31 - bitIndex)) >> 31);
//
//			if(bitVal == 1)
//			{
//				if(twoPower > 0)
//				{
//					a->MultiplyBy2Power( twoPower );
//					twoPower = 0;
//				}
//
//				result->Add(a);
//			}
//
//			twoPower++;
//		}
//
//		bVecIter++;
//	}
//
//	return result;
//}



//BigInteger* BigInteger::Multiply_Method1(BigInteger* a, BigInteger* b)
//{
//    int twoPower = 0;
//    
//    unsigned int bVecSize = b->vec->size();
//    unsigned int* bVecIter = b->vec->GetArray();
//    
//    BigInteger* result = new BigInteger(0, bVecSize + a->vec->size() + 2);
//    
//    for(int i=0; i<bVecSize; i++)
//    {
//        unsigned int val = (*bVecIter);
//        
//        for(int bitIndex=0; bitIndex<32; bitIndex++)
//        {
//            unsigned int bitVal = ((val << (31 - bitIndex)) >> 31);
//            
//            if(bitVal == 1)
//            {
//                if(twoPower > 0)
//                {
//                    a->MultiplyBy2Power( twoPower );
//                    twoPower = 0;
//                }
//                
//                result->Add(a);
//            }
//            
//            twoPower++;
//        }
//        
//        bVecIter++;
//    }
//    
//    return result;
//}



//void BigInteger::Add(BigInteger* b)
//{
//    if(vec->size() < b->vec->size())
//    {
//        while(vec->size() < b->vec->size())
//        vec->push_back(0);
//    }
//    
//    vec->push_back(0);
//    
//    unsigned int* vecArr = vec->GetArray();
//    unsigned int vecSize = vec->size();
//    
//    unsigned int* bVecArr = b->vec->GetArray();
//    unsigned int bVecSize = b->vec->size();
//    
//    uint64_t sum = 0;
//    unsigned int carry = 0;
//    
//    for(int i=0; i<vecSize; i++)
//    {
//        //sum = (i < bVecSize) ? (uint64_t)(vec[i] + b->vec[i] + carry) : (uint64_t)(vec[i] + carry);
//        
//        if(i < bVecSize)
//        {
//            sum = vecArr[i];
//            sum += bVecArr[i];
//            sum += carry;
//        }
//        else
//        {
//            sum = vecArr[i];
//            sum += carry;
//        }
//        
//        vecArr[i] = (unsigned int) ((sum << 32) >> 32);
//        
//        carry = (unsigned int) (sum >> 32);
//        
//        if(i >= bVecSize)
//        {
//            if(carry == 0)
//            break;
//        }
//    }
//    
//    int popCount = 0;
//    
//    for(int i=vecSize-1; i>=0; i--)
//    {
//        if(vecArr[i] == 0)
//        popCount++;
//        else
//        break;
//    }
//    
//    for(int i=0; i<popCount; i++)
//    {
//        vec->pop_back();
//    }
//    
//    addCount += 1; //GetTickCount() - startTime;
//}

//BigInteger* BigInteger::Mul_Exper(BigInteger* aBigInteger, BigInteger* bBigInteger)
//{
//    if(aBigInteger->vec->size() < bBigInteger->vec->size())
//    {
//        BigInteger* temp = aBigInteger;
//        aBigInteger = bBigInteger;
//        bBigInteger = temp;
//    }
//    
//    vector<BigInteger*> vec256;
//    
//    for(unsigned int i=0; i<256; i++)
//    {
//        vec256.push_back( BigInteger::Mul(aBigInteger, i) );
//    }
//    
//    unsigned int resultSize = aBigInteger->vec->size() + bBigInteger->vec->size() + 1;
//    
//    BigInteger* result = new BigInteger(0, resultSize+1024);
//    
//    result->vec->setSize(resultSize);
//    
//    memset(result->vec->GetArray(), 0, result->vec->capacity()*sizeof(unsigned int));
//    
//    unsigned char* b = (unsigned char*) bBigInteger->vec->GetArray();
//    
//    unsigned int bArrSize = bBigInteger->vec->size() * 4;
//    
//    //    mulCount = 0;
//    //
//    //    unsigned char* rChar = (unsigned char*)result->vec->GetArray();
//    //
//    //    int i=0;
//    //
//    //    for(; i<bArrSize-5; i+=5)
//    //    {
//    //        //Add_Exper(vec256[ b[i] ], result, i);
//    //
//    //        BigInteger* line1 = vec256[ b[i+0] ];
//    //
//    //        //uint64_t startTime = mach_absolute_time() / 1000000;
//    //
//    //        BigInteger* line2 = vec256[ b[i+1] ]->CloneAndLeftShiftBytes(1);
//    //        BigInteger* line3 = vec256[ b[i+2] ]->CloneAndLeftShiftBytes(2);
//    //        BigInteger* line4 = vec256[ b[i+3] ]->CloneAndLeftShiftBytes(3);
//    //        BigInteger* line5 = vec256[ b[i+4] ]->CloneAndLeftShiftBytes(4);
//    ////        BigInteger* line6 = vec256[ b[i+6] ]->CloneAndLeftShiftBytes(5);
//    ////        BigInteger* line7 = vec256[ b[i+7] ]->CloneAndLeftShiftBytes(6);
//    ////        BigInteger* line8 = vec256[ b[i+8] ]->CloneAndLeftShiftBytes(7);
//    //
//    //        //mulCount += (mach_absolute_time() / 1000000) - startTime;
//    //
//    //        unsigned int line1Size = line1->vec->size();
//    //        unsigned int line2Size = line2->vec->size();
//    //        unsigned int line3Size = line3->vec->size();
//    //        unsigned int line4Size = line4->vec->size();
//    //        unsigned int line5Size = line5->vec->size();
//    ////        unsigned int line6Size = line6->vec->size();
//    ////        unsigned int line7Size = line7->vec->size();
//    ////        unsigned int line8Size = line8->vec->size();
//    //
//    //
//    //        unsigned int maxSize = (line1Size > line2Size) ? line1Size : line2Size;
//    //                     maxSize = (line3Size > maxSize  ) ? line3Size : maxSize;
//    //                     maxSize = (line4Size > maxSize  ) ? line4Size : maxSize;
//    //                     maxSize = (line5Size > maxSize  ) ? line5Size : maxSize;
//    ////                     maxSize = (line6Size > maxSize  ) ? line6Size : maxSize;
//    ////                     maxSize = (line7Size > maxSize  ) ? line7Size : maxSize;
//    ////                     maxSize = (line8Size > maxSize  ) ? line8Size : maxSize;
//    //
//    //
//    //        //unsigned int maxSize = line8Size;
//    //
//    //        unsigned int* l1 = line1->vec->GetArray();
//    //        unsigned int* l2 = line2->vec->GetArray();
//    //        unsigned int* l3 = line3->vec->GetArray();
//    //        unsigned int* l4 = line4->vec->GetArray();
//    //        unsigned int* l5 = line5->vec->GetArray();
//    ////        unsigned int* l6 = line6->vec->GetArray();
//    ////        unsigned int* l7 = line7->vec->GetArray();
//    ////        unsigned int* l8 = line8->vec->GetArray();
//    //
//    //        unsigned int* r = (unsigned int*) &rChar[i];
//    //
//    //        uint64_t sum = 0;
//    //
//    //        for(int j=0; j<maxSize+1; j++)
//    //        {
//    //            sum = (uint64_t)l1[j] + (uint64_t)l2[j] + (uint64_t)l3[j] + (uint64_t)l4[j] + (uint64_t)l5[j] + (uint64_t)r[j] + (sum >> 32);
//    //
//    //            r[j] = (unsigned int) (( sum << 32) >> 32);
//    //        }
//    //
//    //        r[maxSize+1] = (sum >> 32);
//    //
//    //        delete line2;
//    //        delete line3;
//    //        delete line4;
//    //        delete line5;
//    ////        delete line6;
//    ////        delete line7;
//    ////        delete line8;
//    //    }
//    //
//    //
//    //    for(; i<bArrSize; i++)
//    //    {
//    //        Add_Exper(vec256[ b[i] ], result, i);
//    //    }
//    
//    
//    for(int i=0; i<bArrSize; i++)
//    {
//        Add_Exper(vec256[ b[i] ], result, i);
//    }
//    
//    printf("\n EXPR : %d", mulCount);
//    
//    for(int i=result->vec->size()-1; i>=0; i--)
//    {
//        if(result->vec->at(i) == 0)
//            result->vec->pop_back();
//        else
//            break;
//    }
//    
//    for(unsigned int i=0; i<256; i++)
//    {
//        delete vec256[i];
//    }
//    
//    return result;
//}
//
//void BigInteger::AddBytes(unsigned char* a, unsigned char* r, unsigned int size)
//{
//    unsigned char carry = 0;
//    
//    uint64_t l1 = 0;
//    uint64_t l2 = 0;
//    uint64_t sumL = 0;
//    
//    int i=0;
//    
//    for(; i<size-7; i+=7)
//    {
//        l1 = 0;
//        l2 = 0;
//        
//        //memcpy(&l1, &a[i], 7);
//        //memcpy(&l2, &r[i], 7);
//        
//        l1 = ((a[i] << 8) >> 8);
//        l2 = ((r[i] << 8) >> 8);
//        
//        sumL = l1 + l2 + carry;
//        
//        carry = (sumL >> 54);
//        
//        //memcpy(&r[i], &sumL, 7);
//        
//        r[i] = ((sumL << 8 ) >> 8);
//    }
//    
//    unsigned short sumS = 0;
//    
//    for(; i<size; i++)
//    {
//        sumS = a[i] + r[i] + carry;
//        
//        r[i] = (unsigned char)sumS;
//        
//        carry = (sumS >> 8);
//    }
//    
//    if(carry != 0)
//        r[size] = carry;
//}
//
//void BigInteger::Add_Exper(BigInteger* aBigInteger, BigInteger* rBigInteger, int startIndex)
//{
//    //    unsigned int aVecSize = aBigInteger->vec->size() * 4;
//    //
//    //    unsigned char* a = (unsigned char*)aBigInteger->vec->GetArray();
//    //    unsigned char* r = (unsigned char*)rBigInteger->vec->GetArray();
//    //
//    //    unsigned short sum = 0;
//    //
//    //    for(int i=0; i<aVecSize; i++)
//    //    {
//    //        sum = a[i] + r[startIndex + i] + (sum >> 8);
//    //
//    //        r[startIndex + i] = (unsigned char) ((sum << 8) >> 8);
//    //    }
//    //
//    //    r[startIndex + aVecSize] = (sum >> 8);
//    
//    
//    unsigned int aVecSize = aBigInteger->vec->size();
//    
//    unsigned int* a = aBigInteger->vec->GetArray();
//    unsigned char* rChar = (unsigned char*)rBigInteger->vec->GetArray();
//    unsigned int* r = (unsigned int*) &rChar[startIndex];
//    
//    AddBytes((unsigned char*)a, (unsigned char*)r, aVecSize*4);
//    
//    //    uint64_t sum = 0;
//    //
//    //    for(int i=0; i<aVecSize; i++)
//    //    {
//    //        sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32));
//    //
//    //        r[i] = (unsigned int)sum;
//    //    }
//    //
//    //    r[aVecSize] = (sum >> 32);
//    
//    
//    //    int i=0;
//    //
//    //    if( aVecSize > 10)
//    //    {
//    //        for(; i<aVecSize-10; i++)
//    //        {
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));    i++;
//    //            r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + (uint64_t)r[i] + (sum >> 32)));
//    //        }
//    //    }
//    //    
//    //    for(; i<aVecSize; i++)
//    //    {
//    //        r[i] = (unsigned int)  (sum = ((uint64_t)a[i] + r[i] + (sum >> 32)));
//    //    }
//    
//    
//    //r[aVecSize] = (sum >> 32);
//}
//


//char BigInteger::GetBitValue(unsigned int index)
//{
//    unsigned int arrIndex = index / 32;
//    unsigned int bitIndex = index % 32;
//    
//    if(arrIndex >= vec->size())
//		return -1;
//    
//    unsigned int val = vec->at(arrIndex);
//    
//    unsigned short leftShift = 31 - bitIndex;
//    
//    return ((val << leftShift) >> 31);
//}


//void BigInteger::LeftShift32Bits()
//{
//	unsigned int size = vec->size();
//
//	vec->push_back(0);
//
//	unsigned int* arr = vec->GetArray();
//
//	for(int i=size-1; i>=0; i--)
//	{
//		arr[i+1] = arr[i];
//	}
//
//	arr[0] = 0;
//}
//
//
//void BigInteger::LeftShift32BitMultiple(int multiple)
//{
//	unsigned int size = vec->size();
//
//	for(int i=0; i<multiple; i++)
//		vec->push_back(0);
//
//	unsigned int* arr = vec->GetArray();
//
//	for(int i=size-1; i>=0; i--)
//		arr[i+multiple] = arr[i];
//
//	for(int i=0; i<multiple; i++)
//		arr[i] = 0;
//}
//
//
//void BigInteger::RightShift32Bits()
//{
//	unsigned int size = vec->size();
//
//	vec->push_back(0);
//
//	unsigned int* arr = vec->GetArray();
//
//	for(int i=1; i<size; i++)
//	{
//		arr[i-1] = arr[i];
//	}
//
//	vec->pop_back();
//}


//void BigInteger::DivideBy2Power(int power)
//{
//	if(power <= 0)
//		return;
//
//	int sizeOfUInt = sizeof(unsigned int) * 8;
//
//	int numIndexShift = power / sizeOfUInt;
//	int remainderBits = power % sizeOfUInt;
//
//	for(int i=0; i<numIndexShift; i++)
//		RightShift32Bits();
//
//	if(remainderBits > 0)
//		RightShift_LessThan32( remainderBits );
//}
//
//
//void BigInteger::MulBy2Power(int power)
//{
//	if(power <= 0)
//		return;
//
//	int sizeOfUInt = sizeof(unsigned int) * 8;
//
//	int numIndexShift = power / sizeOfUInt;
//	int remainderBits = power % sizeOfUInt;
//
//	LeftShift32BitMultiple(numIndexShift);
//
//	if(remainderBits > 0)
//		LeftShift_LessThan32( remainderBits );
//}
