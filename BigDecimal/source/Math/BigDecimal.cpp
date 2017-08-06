#include "BigDecimal.h"
#include "BaseConverter.h"
#include "DefinesAndIncludes.h"

int BigDecimal::addCount = 0;
int BigDecimal::mulCount = 0;
int BigDecimal::divCount = 0;

BigDecimal::BigDecimal()
{
	vec.push_back(0);
}

BigDecimal::BigDecimal(BigDecimal* cloneFrom)
{
	vec = cloneFrom->vec;
}

BigDecimal::BigDecimal(unsigned int val)
{
	vec.push_back(val);
}

BigDecimal::BigDecimal(uint64_t val)
{
	unsigned int intVal0 = (unsigned int)((val << 32 ) >> 32);
	unsigned int intVal1 = (unsigned int)(val >> 32);

	vec.push_back(intVal0);

	if(intVal1 > 0)
		vec.push_back(intVal1);

	//ToString();
}

bool BigDecimal::IsEvenNumber()
{
	bool isEven = true;

	if(vec.size() > 0)
		isEven = (vec[0] % 2 == 0);

	return isEven;
}

bool BigDecimal::IsOddNumber()
{
	bool isOdd = false;

	if(vec.size() > 0)
		isOdd = (vec[0] % 2 == 1);

	return isOdd;
}

bool BigDecimal::IsZero()
{
	bool isZero = false;

	if(vec.size() == 0)
		isZero = true;
	else if(vec.size() == 1)
		isZero = (vec[0] == 0);

	return isZero;
}

void BigDecimal::LeftShift_LessThan32(int leftShiftBits)
{
	unsigned int size = vec.size();

	unsigned int rightShiftBits = sizeof(int)*8 - leftShiftBits;
	unsigned int carry = 0;

	for(unsigned int i=0; i<size; i++)
	{
		unsigned int val = vec[i];

		vec[i] = (val << leftShiftBits) | carry;

		carry = val >> rightShiftBits;
	}

	if(carry != 0)
		vec.push_back(carry);
}

void BigDecimal::LeftShift32Bits()
{
	unsigned int size = vec.size();

	vec.push_back(0);

	for(int i=size-1; i>=0; i--)
	{
		vec[i+1] = vec[i];
	}

	vec[0] = 0;
}

void BigDecimal::LeftShift32BitsMultiple(int multiple)
{
	unsigned int size = vec.size();

	for(int i=0; i<multiple; i++)
		vec.push_back(0);

	for(int i=size-1; i>=0; i--)
	{
		vec[i+multiple] = vec[i];
	}

	for(int i=0; i<multiple; i++)
		vec[i] = 0;
}

void BigDecimal::RightShift32Bits()
{
	unsigned int size = vec.size();

	vec.push_back(0);

	for(int i=1; i<size; i++)
	{
		vec[i-1] = vec[i];
	}

	vec.pop_back();
}

void BigDecimal::RightShift_LessThan32(int rightShiftBits)
{
	unsigned int size = vec.size();

	if(size <= 0)
		return;

	unsigned int leftShiftBits = sizeof(int)*8 - rightShiftBits;
	unsigned int carry = 0;

	for(unsigned int i=size-1; ; i--)
	{
		unsigned int val = vec[i];

		vec[i] = (val >> rightShiftBits) | carry;

		carry = val << leftShiftBits;

		if(i == 0)
			break;
	}

	if(vec[size-1] == 0)
		vec.pop_back();
}


void BigDecimal::MultiplyBy2()
{
	LeftShift_LessThan32(1);
}

void BigDecimal::DivideBy2()
{
	unsigned long startTime = GetTickCount();

	RightShift_LessThan32(1);
	//str = ToString();

	divCount += GetTickCount() - startTime;
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

	if(arrIndex >= vec.size())
		return -1;

	unsigned int val = vec[arrIndex];

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


BigDecimal* BigDecimal::Multiply(BigDecimal* b)
{
	BigDecimal* result = new BigDecimal();

	int twoPower = 0;
	int bitIndex = 0;

	char bitVal = b->GetBitValue(bitIndex);

	int loopCount = 0;

	while(bitVal >= 0)
	{
		loopCount++;

		//if(b->IsOddNumber())

		if(bitVal == 1)
		{
			if(twoPower > 0)
			{
				MultiplyBy2Power( twoPower );

				twoPower = 0;
			}

			result->Add(this);
		}

		twoPower++;
		bitIndex++;

		bitVal = b->GetBitValue(bitIndex);

		//b->DivideBy2();
	}
	
	writeConsole("\nLoop count : %d",loopCount);
	//delete b;

	return result;
}

void BigDecimal::Add(BigDecimal* b)
{
	unsigned long startTime = GetTickCount();

	if(vec.size() < b->vec.size())
	{
		while(vec.size() < b->vec.size())
			vec.push_back(0);
	}

	vec.push_back(0);

	unsigned int vecSize = vec.size();
	unsigned int bVecSize = b->vec.size();

	uint64_t sum = 0;
	unsigned int carry = 0;

	for(int i=0; i<vecSize; i++)
	{
		//sum = (i < bVecSize) ? (uint64_t)(vec[i] + b->vec[i] + carry) : (uint64_t)(vec[i] + carry);

		if(i < bVecSize)
		{
			sum = vec[i];
			sum += b->vec[i];
			sum += carry;
		}
		else
		{
			sum = vec[i];
			sum += carry;
		}

		vec[i] = (unsigned int) ((sum << 32) >> 32);

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
		if(vec[i] == 0)
			popCount++;
		else
			break;
	}

	for(int i=0; i<popCount; i++)
	{
		vec.pop_back();
	}

	//str = ToString();

	addCount += GetTickCount() - startTime;
}


string BigDecimal::ToString()
{
	writeConsole("\naddcount : %d",addCount);
	writeConsole("\nmulcount : %d",mulCount);
	writeConsole("\ndivcount : %d",divCount);
	writeConsole("\nMem recreate time : %d", VecUInt::memCreateTime);
	writeConsole("\nResult len : %d\n", vec.size());

	const BaseConverter& dec2hex = BaseConverter::DecimalToHexConverter();

	string hexString;

	for(int i=vec.size()-1; i>=0; i--)
	{
		string temp = dec2hex.FromDecimal(vec[i]);

		int len = temp.length();

		if(len < 8)
			temp = std::string( 8-len, '0').append( temp);

		hexString.append( temp );
	}

	const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();


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

	str = hex2dec.Convert(hexString);

	return str;
}
