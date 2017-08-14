#include "Looper.h"
#include "math.h"
#include "DefinesAndIncludes.h"
#include "stdint.h"
#include "VecUInt.h"
#include "BigInteger.h"


void Method2()
{
	uint64_t startTime = GetTickCount();
    
    BigInteger* bigInteger1 = new BigInteger((uint64_t)7797279247);
    
    for(int i=0; i<11; i++)
        bigInteger1->Mul(bigInteger1);

    BigInteger* bigInteger2 = new BigInteger((uint64_t)123987456789);

    for(int i=0; i<11; i++)
        bigInteger2->Mul(bigInteger2);
    
	writeConsole("\nstarted...\n\n");
    
    BigInteger* result = BigInteger::Mul(bigInteger1, bigInteger2);
    
    uint64_t endTime = GetTickCount();
    
    string resultStr = result->GetHexString();
    
    writeConsole("\nTime taken Norm : %d, len : %d\n", (int)(endTime - startTime), (int)resultStr.length());
    
	writeConsole("\n result :  %s\n",resultStr.c_str());
}

void Method1()
{
    BigInteger* b1 = new BigInteger((uint64_t)779721479247);
    
    b1->Mul( new BigInteger((uint64_t)10000000000) );
    b1->Add( new BigInteger((uint64_t) 8732016463) );

    b1->Mul( new BigInteger((uint64_t)10000000) );
    b1->Add( new BigInteger((uint64_t) 4419200) );

    
    BigInteger* b2 = new BigInteger((uint64_t)15898147326221);
    
    b2->Mul( new BigInteger((uint64_t)10000000000) );
    b2->Add( new BigInteger((uint64_t) 5788341546) );
    
    b2->Mul( new BigInteger((uint64_t)10000000) );
    b2->Add( new BigInteger((uint64_t) 1888000) );
    
    printf("\n1-- :    %s\n",b1->GetHexString().c_str());
    printf("\n2-- :  %s\n",b2->GetHexString().c_str());
    
    BigInteger* sum = BigInteger::Mul(b1, b2);
    
    printf("\n3-- :  %s\n",sum->GetHexString().c_str());
}


NumarAndDenom Element(unsigned int k)
{
    NumarAndDenom numerAndDenom;
    
    numerAndDenom.numar = new BigInteger((unsigned int) 1);
    numerAndDenom.denom = new BigInteger( (uint64_t)(8 * k + 1) );
    
    return numerAndDenom;
    

//    BigInteger a( (uint64_t)(8 * k + 1) );
//    BigInteger b( (uint64_t)(8 * k + 4) );
//    BigInteger c( (uint64_t)(8 * k + 5) );
//    BigInteger d( (uint64_t)(8 * k + 6) );
//    
//    BigInteger* ab = BigInteger::Mul(&a, &b);
//    BigInteger* cd = BigInteger::Mul(&c, &d);
//    
//    BigInteger* const1 = BigInteger::Mul(&b, cd);
//    const1->MulBy2Power(2);
//    
//    BigInteger* const2 = BigInteger::Mul(&a, cd);
//    const2->MulBy2Power(1);
//    
//    BigInteger* const3 = BigInteger::Mul(ab, &d);
//    BigInteger* const4 = BigInteger::Mul(ab, &c);
//    
//    const2->Add(const3);
//    const2->Add(const4);
//    
//    NumarAndDenom numerAndDenom;
//    
//    numerAndDenom.numar = BigInteger::Subtract(const1, const2);
//    numerAndDenom.denom = BigInteger::Mul(ab, cd);
//    
//    //printf("\nN:%s",numerAndDenom.numar->ToString().c_str());
//    //printf("\nD:%s",numerAndDenom.denom->ToString().c_str());
//    
//    delete ab;
//    delete cd;
//    delete const1;
//    delete const2;
//    delete const3;
//    delete const4;
//    
//    return numerAndDenom;
}


NumarAndDenom Spigot_Level_1(int startVal, int endVal)
{
    printf("\nL1 : %d - %d",startVal, endVal);
    
    BigInteger* totalNumar = new BigInteger((unsigned int)0);
    BigInteger* totalDenom = new BigInteger((unsigned int)1);
    
    //BigInteger sixTeen = new BigInteger(16);
    
    for(int k=endVal-1 ; k>=startVal; k--)
    {
        NumarAndDenom elementND = Element( k );
        
        BigInteger* ab = BigInteger::Mul(totalNumar, elementND.denom);
        BigInteger* cd = BigInteger::Mul(totalDenom, elementND.numar);
        
        BigInteger* newNumar = BigInteger::Add(ab, cd);
        
//        printf("\nab %s",ab->ToString().c_str());
//        printf("\ncd %s",cd->ToString().c_str());
//        printf("\nNewNumar : %s", newNumar->ToString().c_str());
        
        delete ab;
        delete cd;
        delete totalNumar;
        
        totalNumar = newNumar;
        
        totalDenom->Mul( elementND.denom );
        
        if(k != startVal)
        {
            totalDenom->MulBy2Power(4);
        }
        
        delete elementND.numar;
        delete elementND.denom;
    }
    
    NumarAndDenom numerAndDenom;
    
    numerAndDenom.numar = totalNumar;
    numerAndDenom.denom = totalDenom;
    
//    printf("\nNumar : %s", totalNumar->ToString().c_str());
//    printf("\nDenom : %s", totalDenom->ToString().c_str());
    
    return numerAndDenom;
}


NumarAndDenom Spigot_Level_2(int startVal, int increment, int numTimes)
{
    BigInteger* totalNumar = new BigInteger((unsigned int)0);
    BigInteger* totalDenom = new BigInteger((unsigned int)1);
    
    int endVal = startVal + increment * numTimes;
    
    for(int k=endVal ; k>startVal; k -= increment)
    {
        //printf("\nk2 = %d", (endVal-k));
        
        NumarAndDenom nd = Spigot_Level_1(k-increment, k);
        
        BigInteger* ab = BigInteger::Mul(totalNumar, nd.denom);
        BigInteger* cd = BigInteger::Mul(totalDenom, nd.numar);
        
        BigInteger* newNumar = BigInteger::Add(ab, cd);
        
        delete ab;
        delete cd;
        delete totalNumar;
        
        totalNumar = newNumar;
        
        totalDenom->Mul( nd.denom );
        
        if(k-increment != startVal)
            totalDenom->MulBy2Power(increment * 4);
    }
    
    NumarAndDenom numerAndDenom;
    
    numerAndDenom.numar = totalNumar;
    numerAndDenom.denom = totalDenom;
    
    return numerAndDenom;
}


NumarAndDenom Spigot_Level_3(int startVal, int increment, int numTimes)
{
    BigInteger* totalNumar = new BigInteger((unsigned int)0);
    BigInteger* totalDenom = new BigInteger((unsigned int)1);
    
    int endVal = startVal + increment * numTimes;
    
    for(int k=endVal ; k>startVal; k -= increment)
    {
        printf("\nk-3 = %d", (endVal-k));
        
        NumarAndDenom nd = Spigot_Level_2(k-increment, increment/10, 10);
        
        BigInteger* ab = BigInteger::Mul(totalNumar, nd.denom);
        BigInteger* cd = BigInteger::Mul(totalDenom, nd.numar);
        
        BigInteger* newNumar = BigInteger::Add(ab, cd);
        
        delete ab;
        delete cd;
        delete totalNumar;
        
        totalNumar = newNumar;
        
        totalDenom->Mul( nd.denom );
        
        if(k-increment != startVal)
        totalDenom->MulBy2Power(increment * 4);
    }
    
    NumarAndDenom numerAndDenom;
    
    numerAndDenom.numar = totalNumar;
    numerAndDenom.denom = totalDenom;
    
    return numerAndDenom;
}


Looper::Looper(int windowWidth, int windowHeight)
{
    //Method2();
    
    //Method1();
    
    //Element(234567);
    
    uint64_t startTime = GetTickCount();
    
//    Spigot_Level_3(0, 50000/10, 10);
    
    Spigot_Level_1(0, 1000);
    
    uint64_t endTime = GetTickCount();
    
    int timeTaken =(int)( endTime - startTime );
    
    writeConsole("\n\nTime taken : %d\n", timeTaken);    
}


void Looper::Draw(float deltaTime)
{
}

Looper::~Looper()
{
}


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
