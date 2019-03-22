#include "Looper.h"
#include "math.h"
#include "DefinesAndIncludes.h"
#include "stdint.h"
#include "VecUInt.h"
#include "MyString.h"
#include "stringExt.h"
#include "MyVec.h"

#include <string>
using namespace std;

Looper::Looper(int windowWidth, int windowHeight)
{
	//ConstructorTest();
	//AssignmentTest();
	//PlusOperatorTest();
	//PlusEqualsOperatorTest();
	//MemLeakTest();
	IncrementOperatorTest();

	MyVec<int> vec;
}

void Looper::IncrementOperatorTest()
{
	//string s7("seven");
	//string s8("eight");
	//string s9("nine");

	MyString ms7("seven7");
	MyString ms8("eight");
	MyString ms9("nine");

	//ms8 = ++ms7;

	Looper::Swap(ms7, ms8);

	MyString* str1 = new MyString("1");
	MyString* str2 = new MyString("two");

	Looper::Swap(str1, str2);
}

void Looper::ConstructorTest()
{
	string s1("aaa");
	string s2 = "bbb";
	string s3(s1);
	string s4 = s1;

	MyString ms1("aaa");
	MyString ms2 = "bbb";
	MyString ms3(ms1);
	MyString ms4 = ms1;
}

void Looper::AssignmentTest()
{
	//assignment operators
	string s5("five");
	string s6("six");
	string s7("seven");
	s5 = s6 = s7;
	s5.append("555");

	MyString ms5("five");
	MyString ms6("six");
	MyString ms7("seven");
	ms5 = ms6 = ms7;
	ms5.append("555");
}

void Looper::PlusEqualsOperatorTest()
{
	string s7("seven");
	string s8("eight");
	string s9("nine");
	s7 += s8 += s9;

	MyString ms7("seven");
	MyString ms8("eight");
	MyString ms9("nine");
	ms7 += ms8 += ms9;
}

void Looper::PlusOperatorTest()
{
	string s8("eight");
	string s9("nine");
	string s10("ten");
	string s11("eleven");
	s11 = s8 + s9 + s10;

	MyString ms8 = "eight";
	MyString ms9 = "nine";
	MyString ms10 = "ten";
	MyString ms11 = "eleven";
	ms11 = ms8 + ms9 + ms10;
}

void Looper::MemLeakTest()
{
	stringExt ms8("eight");
	stringExt ms9("nine");
	stringExt ms10("ten");

	//Approach 1
	stringExt temp = (stringExt&)(ms9 + ms10);
	ms8 = temp;

	//Approach 2
	ms8 = (stringExt&)(ms9 + ms10);

	//Approach 1 has 4 destructor calls.
	//Approach 2 has only 3 destructor calls. Is it leading to mem leak ?
	//Note: When you are checking here a approach, comment the other one.
}

Looper::~Looper()
{
}

void Looper::Draw(float deltaTime)
{
}
