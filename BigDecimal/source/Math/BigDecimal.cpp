#include "BigDecimal.h"
#include "BaseConverter.h"
#include "DefinesAndIncludes.h"

int BigDecimal::addCount = 0;
int BigDecimal::mulCount = 0;
int BigDecimal::divCount = 0;

BigDecimal::BigDecimal()
{
	vec = new VecUInt();
	vec->push_back(0);

	_delVector = true;
}

BigDecimal::BigDecimal(VecUInt* vecUInt)
{
	vec = vecUInt;
	_delVector = true;
}

BigDecimal::BigDecimal(unsigned int val, unsigned int vecCapacity)
{
	vec = new VecUInt(vecCapacity);
	vec->push_back(val);

	_delVector = true;
}

BigDecimal::BigDecimal(unsigned int val)
{
	vec = new VecUInt();
	vec->push_back(val);

	_delVector = true;
}

BigDecimal::BigDecimal(uint64_t val)
{
	vec = new VecUInt();

	unsigned int intVal0 = (unsigned int)((val << 32 ) >> 32);
	unsigned int intVal1 = (unsigned int)(val >> 32);

	vec->push_back(intVal0);

	if(intVal1 > 0)
		vec->push_back(intVal1);

	_delVector = true;
}

void BigDecimal::SetDeleteVector(bool del)
{
	_delVector = del;
}

bool BigDecimal::IsEvenNumber()
{
	bool isEven = true;

	if(vec->size() > 0)
		isEven = (vec->at(0) % 2 == 0);

	return isEven;
}

bool BigDecimal::IsOddNumber()
{
	bool isOdd = false;

	if(vec->size() > 0)
		isOdd = (vec->at(0) % 2 == 1);

	return isOdd;
}

bool BigDecimal::IsZero()
{
	bool isZero = false;

	if(vec->size() == 0)
		isZero = true;
	else if(vec->size() == 1)
		isZero = (vec->at(0) == 0);

	return isZero;
}

void BigDecimal::LeftShift_LessThan32(int leftShiftBits)
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

void BigDecimal::LeftShift32Bits()
{
	unsigned int size = vec->size();

	vec->push_back(0);

	unsigned int* arr = vec->GetArray();

	for(int i=size-1; i>=0; i--)
	{
		arr[i+1] = arr[i];
	}

	arr[0] = 0;
}

void BigDecimal::LeftShift32BitsMultiple(int multiple)
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

void BigDecimal::RightShift32Bits()
{
	unsigned int size = vec->size();

	vec->push_back(0);

	unsigned int* arr = vec->GetArray();

	for(int i=1; i<size; i++)
	{
		arr[i-1] = arr[i];
	}

	vec->pop_back();
}

void BigDecimal::RightShift_LessThan32(int rightShiftBits)
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


void BigDecimal::MultiplyBy2()
{
	LeftShift_LessThan32(1);
}

void BigDecimal::DivideBy2()
{
	RightShift_LessThan32(1);
}

void BigDecimal::DivideBy2Power(int power)
{
	if(power <= 0)
		return;

	int sizeOfUInt = sizeof(unsigned int) * 8;

	int numIndexShift = power / sizeOfUInt;
	int remainderBits = power % sizeOfUInt;

	for(int i=0; i<numIndexShift; i++)
		RightShift32Bits();

	if(remainderBits > 0)
		RightShift_LessThan32( remainderBits );
}


char BigDecimal::GetBitValue(unsigned int index)
{
	unsigned int arrIndex = index / 32;
	unsigned int bitIndex = index % 32;

	if(arrIndex >= vec->size())
		return -1;

	unsigned int val = vec->at(arrIndex);

	unsigned short leftShift = 31 - bitIndex;

	return ((val << leftShift) >> 31);
}


void BigDecimal::MultiplyBy2Power(int power)
{
	if(power <= 0)
		return;

	int sizeOfUInt = sizeof(unsigned int) * 8;

	int numIndexShift = power / sizeOfUInt;
	int remainderBits = power % sizeOfUInt;

	//for(int i=0; i<numIndexShift; i++)
	//	LeftShift32Bits();

	LeftShift32BitsMultiple(numIndexShift);

	if(remainderBits > 0)
		LeftShift_LessThan32( remainderBits );
}


BigDecimal* BigDecimal::Multiply(BigDecimal* bigDecimal)
{
	BigDecimal* a = Clone();
	BigDecimal* b = bigDecimal;

	if(a->vec->size() < b->vec->size())
	{
		BigDecimal* temp = a;
		a = b;
		b = temp;
	}

	int twoPower = 0;

	unsigned int bVecSize = b->vec->size();
	unsigned int* bVecIter = b->vec->GetArray();

	BigDecimal* result = new BigDecimal(0, bVecSize + a->vec->size() + 2);

	for(int i=0; i<bVecSize; i++)
	{
		unsigned int val = (*bVecIter);

		for(int bitIndex=0; bitIndex<32; bitIndex++)
		{
			unsigned int bitVal = ((val << (31 - bitIndex)) >> 31);

			if(bitVal == 1)
			{
				if(twoPower > 0)
				{
					a->MultiplyBy2Power( twoPower );
					twoPower = 0;
				}

				result->Add(a);
			}

			twoPower++;
		}

		bVecIter++;
	}

	delete a;

	//if(vec)
	//{
	//	delete vec;
	//	vec = NULL;
	//}

	//vec = result->vec;

	//result->SetDeleteVector(false);

	//delete result;


	return result;
}

void BigDecimal::Add(BigDecimal* b)
{
	unsigned long startTime = GetTickCount();

	if(vec->size() < b->vec->size())
	{
		while(vec->size() < b->vec->size())
			vec->push_back(0);
	}

	vec->push_back(0);

	unsigned int* vecArr = vec->GetArray();
	unsigned int vecSize = vec->size();

	unsigned int* bVecArr = b->vec->GetArray();
	unsigned int bVecSize = b->vec->size();

	uint64_t sum = 0;
	unsigned int carry = 0;

	for(int i=0; i<vecSize; i++)
	{
		//sum = (i < bVecSize) ? (uint64_t)(vec[i] + b->vec[i] + carry) : (uint64_t)(vec[i] + carry);

		if(i < bVecSize)
		{
			sum = vecArr[i];
			sum += bVecArr[i];
			sum += carry;
		}
		else
		{
			sum = vecArr[i];
			sum += carry;
		}

		vecArr[i] = (unsigned int) ((sum << 32) >> 32);

		carry = (unsigned int) (sum >> 32);

		if(i >= bVecSize)
		{
			if(carry == 0)
				break;
		}
	}

	int popCount = 0;

	for(int i=vecSize-1; i>=0; i--)
	{
		if(vecArr[i] == 0)
			popCount++;
		else
			break;
	}

	for(int i=0; i<popCount; i++)
	{
		vec->pop_back();
	}

	addCount += 1; //GetTickCount() - startTime;
}


string BigDecimal::ToString()
{
	writeConsole("\naddcount : %d",addCount);
	writeConsole("\nmulcount : %d",mulCount);
	writeConsole("\ndivcount : %d",divCount);
	writeConsole("\nMem recreate time : %d", VecUInt::memCreateTime);
	writeConsole("\nResult len : %d\n", vec->size());

	const BaseConverter& dec2hex = BaseConverter::DecimalToHexConverter();

	string hexString;

	for(int i=vec->size()-1; i>=0; i--)
	{
		string temp = dec2hex.FromDecimal(vec->at(i));

		int len = temp.length();

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

	std::ofstream hexFile("outputHex.txt");
	hexFile << hexString;
	hexFile.close();

	const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();
	str = hex2dec.Convert(hexString);

	std::ofstream decimalFile("outputDecimal.txt");
	decimalFile << str;
	decimalFile.close();

	return str;
}

BigDecimal* BigDecimal::Clone()
{
	VecUInt* newVec = vec->Clone();

	return new BigDecimal(newVec);
}

BigDecimal::~BigDecimal()
{
	if(vec && _delVector)
	{
		delete vec;
		vec = NULL;
	}
}


//BigDecimal* BigDecimal::Multiply(BigDecimal* b)
//{
//	BigDecimal* result = new BigDecimal();
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