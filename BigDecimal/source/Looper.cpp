#include "Looper.h"
#include "Input.h"
#include "math.h"
#include "DefinesAndIncludes.h"
#include "ImageBuffer.h"
#include "Math/BaseConverter.h"
#include "Math/BigDecimal.h"
#include "stdint.h"
#include "Util/VecUInt.h"
#include "Util/CVector.h"

Looper::Looper(int windowWidth, int windowHeight)
{
	uint64_t val1 = 78948752;
	uint64_t val2 = 45458755;

	BigDecimal bigDecimal1(val1);
	BigDecimal bigDecimal2(val2);

	bigDecimal1.MultiplyBy2Power(100000);
	bigDecimal2.MultiplyBy2Power(800000);

	unsigned long startTime = GetTickCount();

	BigDecimal* result = bigDecimal1.Multiply(&bigDecimal2);

	unsigned long timeTaken = GetTickCount() - startTime;

	writeConsole("\nTime taken :%lu\n",timeTaken);

	string resultStr = result->ToString();

	writeConsole("\nResult Len: %d\n\n",resultStr.length());
	writeConsole("\n\nResult : %s\n\n",resultStr.c_str());
}

void Looper::Draw(float deltaTime)
{
}

Looper::~Looper()
{
}

//
//void shift_left(unsigned char *ar, int size, int leftShift)
//{
//	if(size <= 0)
//		return;
//
//	unsigned char carry = 0;
//
//	ar[0] <<= leftShift;
//
//	int rightShift = 8-leftShift;
//
//	for(int i=1; i<size; i++)
//	{
//		carry = ar[i] >> rightShift;
//		ar[i] <<= leftShift;
//		ar[i-1] |= carry;
//	}
//}
//
//int bitwiseadd(int x, int y)
//{
//    while (y != 0)
//    {
//        int carry = x & y;
//        x = x ^ y; 
//        y = carry << 1;
//    }
//    return x;
//}
//
//uint64_t bitwiseMultiply(uint64_t a, uint64_t b)
//{
//   uint64_t result = 0;
//   int count = 0;
//   
//   while(b != 0)               // Iterate the loop till b==0
//   {
//	   count++;
//
//	   writeConsole("\ncount   : %d",count);
//
//        if (b&01)                // Bitwise &  of the value of b with 01
//        {
//			writeConsole("\nBis Odd. before.\nA value   : %llu",a);
//			writeConsole("\nB value   : %llu",b);
//			writeConsole("\nR value   : %llu\n\n",result);
//						
//			result += a;
//
//			writeConsole("\nBis Odd. after .\nA value   : %llu",a);
//			writeConsole("\nB value   : %llu",b);
//			writeConsole("\nR value   : %llu\n\n",result);
//        }
//
//        a<<=1;
//        b>>=1;
//
//		writeConsole("\nA value   : %llu",a);
//		writeConsole("\nB value   : %llu",b);
//		writeConsole("\nR value   : %llu\n\n",result);
//   }
//
//   writeConsole("\nResult value   : %llu\n\n",result);
//   return result;
//}
//
//static const std::string base64_chars = 
//             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//             "abcdefghijklmnopqrstuvwxyz"
//             "0123456789+/";
//
//std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
//  std::string ret;
//  int i = 0;
//  int j = 0;
//  unsigned char char_array_3[3];
//  unsigned char char_array_4[4];
//
//  while (in_len--) {
//    char_array_3[i++] = *(bytes_to_encode++);
//    if (i == 3) {
//      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//      char_array_4[3] = char_array_3[2] & 0x3f;
//
//      for(i = 0; (i <4) ; i++)
//        ret += base64_chars[char_array_4[i]];
//      i = 0;
//    }
//  }
//
//  if (i)
//  {
//    for(j = i; j < 3; j++)
//      char_array_3[j] = '\0';
//
//    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
//    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//
//    for (j = 0; (j < i + 1); j++)
//      ret += base64_chars[char_array_4[j]];
//
//    while((i++ < 3))
//      ret += '=';
//
//  }
//
//  return ret;
//}



	//unsigned int temp = 23;

	//temp = temp >> 1;

	//unsigned int intVal  = 0x0000ffff;
	//unsigned int intVal2 = 0x000000ff;

	//unsigned int sum = intVal + intVal2;

	//unsigned long ans = bitwiseMultiply(40450, 94540);

	//int addResult = bitwiseadd(452, 120);
	//
	//int size = 800000;

	//unsigned char* arr1 = new unsigned char[size];
	//unsigned char* arr2 = new unsigned char[size];
	//unsigned char* result = new unsigned char[size+1];

	//memset(result, 0, size+10);

	//for(int i=0; i<size; i++)
	//{
	//	arr1[i] = abs( rand() % 2 );
	//	arr2[i] = abs( rand() % 2 );
	//}


	//unsigned long startTime = GetTickCount();

	//int carry = 0;

	//for(int i=size-1; i>=0; i--)
	//{
	//	if(arr1[i] == 1 || arr2[i] == 1)
	//	{
	//		result[i+1] = 1;
	//	}
	//}

	//unsigned long timeTaken = GetTickCount() - startTime;


	////3824143000

	//unsigned int intValShift2 = intVal << 1;

	//unsigned char charArr[4];

	//charArr[0] = 0x00;
	//charArr[1] = 0xff;
	//charArr[2] = 0xbb;
	//charArr[3] = 0xff;

	//unsigned int intBackBeforeShift = (unsigned int)((charArr[0]<<24) + (charArr[1]<<16) + (charArr[2]<<8) + charArr[3]);

	//shift_left(charArr, 4, 1);

	//unsigned int intBack = (unsigned int)((charArr[0]<<24) + (charArr[1]<<16) + (charArr[2]<<8) + charArr[3]);

	//0582724351
	//1441705913
	//2024430264

	//unsigned int intVal1 = 0x22bbaaff;
	//unsigned int intVal2 = 0x55eeafb9;
	//unsigned int intSum = intVal1 + intVal2;

	//unsigned char ch1[4];
	//unsigned char ch2[4];

	//ch1[0] = (intVal1 << 24) >> 24;
	//ch1[1] = (intVal1 << 16) >> 24;
	//ch1[2] = (intVal1 << 8) >> 24;
	//ch1[3] = (intVal1 << 0) >> 24;

	//ch2[0] = (intVal2 << 24) >> 24;
	//ch2[1] = (intVal2 << 16) >> 24;
	//ch2[2] = (intVal2 << 8) >> 24;
	//ch2[3] = (intVal2 << 0) >> 24;

	//unsigned char chSum[4];

	//unsigned short sum = 0;
	//unsigned char carry = 0;

	//for(int i=0; i<4; i++)
	//{
	//	sum = ch1[i] + ch2[i] + carry;

	//	chSum[i] = (unsigned char) ((sum << 8) >> 8);
	//	carry = (unsigned char) (sum >> 8);
	//}


	////0x22bbaaff

	//unsigned char chForBase[4];
	//chForBase[4] = 0x22;
	//chForBase[2] = 0xbb;
	//chForBase[1] = 0xaa;
	//chForBase[0] = 0xff;

	//std::string numberStr = base64_encode(chForBase, 4);

	//unsigned int iSum[4];

	//iSum[0] = chSum[0];
	//iSum[1] = chSum[1];
	//iSum[2] = chSum[2];
	//iSum[3] = chSum[3];

	//unsigned char iSumVerify[4];

	//iSumVerify[0] = (intSum << 24) >> 24;
	//iSumVerify[1] = (intSum << 16) >> 24;
	//iSumVerify[2] = (intSum << 8) >> 24;
	//iSumVerify[3] = (intSum << 0) >> 24;
	//unsigned int baseColor = (unsigned int)( (iSum[3]<<24) | (iSum[2]<<16) | (iSum[1]<<8) | iSum[0] );

	//uint64_t result1 = bitwiseMultiply(93000, 93000);

	//VecUInt vec;
	//vec.push_back(10);
	//vec.push_back(20);
	//vec.push_back(30);
	//vec.push_back(40);
	//vec.push_back(50);

	//vec.LeftShift(3);

	//for(int i=0; i<vec.size(); i++)
	//{
	//	writeConsole("\n%d", vec[i]);
	//}
