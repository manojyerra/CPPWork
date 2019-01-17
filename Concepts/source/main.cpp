#include "Base.h"
#include "Derived1.h"
#include "Derived2.h"
#include "Derived1Derived.h"
#include "Temp.h"
#include "MyVector.h"
#include "DefinesAndIncludes.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;


#include <thread>

void VirtualKeyWordUsage();
void StaticAndDynamicCast();
void EvalueStatements();
void BitwiseOperators();
void DifferenceBetweenCandCPP();
void WhatIsThisKeyword();
void SortVectorElements();

void ThreadsExample();
void Thread1Method();
void Thread2Method();

Temp testMethod()
{
	Temp t;
	return t;
}

int Max(Temp& a, Temp& b) {
	return 10;
}


//template <typename K> K const& Max(K const& a, K const& b) {
//	
//	K const& val = a < b ? b : a;
//	
//	return val;
//}


//template <typename T>
//inline T const& Max(T const& a, T const& b) {
//	return a < b ? b : a;
//}


int main()
{
	//DifferenceBetweenCandCPP();

	//WhatIsThisKeyword();

	//BitwiseOperators();

	//ThreadsExample();

	//EvalueStatements();

	//VirtualKeyWordUsage();

	//StaticAndDynamicCast();

	MyVector<int> vec;

	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	int val = vec.get(3);

	int a[2][3] = {
		{1,2,3},
		{1,2,3}
	};

	int arrSize = 3;
	int** b = new int*[arrSize];

	for (int i = 0; i < arrSize; i++)
	{
		b[i] = new int[4];
	}

	for (int f = 0; f < arrSize; f++)
	{
		for (int s = 0; s < 4; s++)
		{
			b[f][s] = 10;
		}
	}

	for (int i = 0; i < arrSize; i++)
	{
		delete[] b[i];
	}

	delete[] b;

	int* sArr = new int[90];
	delete[] sArr;


	SortVectorElements();

	writeStr("\n\n************** End of program **************\n\n");
	
	return 0;
}

void DifferenceBetweenCandCPP()
{
	//What are the differences between C and C++?
	//1) C++ is a kind of superset of C.
	//2) C is a procedural programming language, but C++ supports both procedural and Object Oriented programming.
	//3) Since C++ supports object oriented programming, it supports features like function overloading, templates, 
	//	inheritance, virtual functions, friend functions. These features are absent in C.
	//4) C++ supports exception handling at language level, in C exception handling is done in traditional if-else style.
	//5) C++ supports references, C doesn’t.
	//6) In C, scanf() and printf() are mainly used input/output. C++ mainly uses streams to perform input and output operations. 
	//	cin is standard input stream and cout is standard output stream.
}

void WhatIsThisKeyword()
{
	//What is this pointer?
	//The ‘this’ pointer is passed as a hidden argument to all nonstatic member function calls and is 
	//available as a local variable within the body of all nonstatic functions.
	//‘this’ pointer is a constant pointer that holds the memory address of the current object. 
	//‘this’ pointer is not available in static member functions as static member 
	//functions can be called without any object (with class name).
}

void BitwiseOperators()
{
	// http://www.geeksforgeeks.org/interesting-facts-bitwise-operators-c/

	//& (bitwise AND) Takes two numbers as operand and does AND on every bit of two numbers. 
	//The result of AND is 1 only if both bits are 1.

	{
	int a = 2;				//binary value is 10
	int b = 3;				//binary value is 11
	int c = a & b;			//binary result   10	-> 2
	writeStr("c = %d", c);
	}

	{
	int a = 8;				//binary value is 1000
	int b = 3;				//binary value is 0011
	int c = a & b;			//binary result   0000	-> 0
	writeStr("c = %d", c);
	}

	{
	int a = 2;				//binary value is 010
	int b = 3;				//binary value is 011
	int c = 4;				//binary value is 100
	int d = a & b & c;		//binary result   000	-> 0
	writeStr("d = %d", d);
	}


	//| (bitwise OR) Takes two numbers as operand and does OR on every bit of two numbers. 
	//The result of OR is 1 any of the two bits is 1.

	{
	int a = 8;				//binary value is 1000
	int b = 3;				//binary value is 0011
	int c = a | b;			//binary result   1011	-> 11
	writeStr("c = %d", c);
	}


	//^ (bitwise XOR) Takes two numbers as operand and does XOR on every bit of two numbers. 
	//The result of XOR is 1 if the two bits are different..

	{
	int a = 8;				//binary value is 1000
	int b = 3;				//binary value is 0011
	int c = a ^ b;			//binary result   1011	-> 11
	writeStr("c = %d", c);
	}

	//<< (left shift) Takes two numbers, left shifts the bits of first operand, 
	//the second operand decides the number of places to shift.

	{
	int a = 3;				//binary value is 11
	int b = 2;				
	int c = a << b;			//binary result   1100	-> 12
	writeStr("c = %d", c);
	}

	{
	int a = 8;				//binary value is 1000
	int b = 1;				
	int c = a << b;			//binary result   10000	-> 16
	
	//c = a * 2 pow(b);

	writeStr("c = %d", c);
	}

	//>> (right shift) Takes two numbers, right shifts the bits of first operand, 
	//the second operand decides the number of places to shift.

	{
	int a = 32;				//binary value is 100000
	int b = 2;				
	int c = a >> b;			//binary result   1000	-> 8

	//c = a * (1 / 2 pow(b));

	writeStr("c = %d", c);
	}

	{
	int a = 8;				//binary value is 1000
	int b = 2;				
	int c = a >> b;			//binary result   10	-> 2
	writeStr("c = %d", c);
	}

	//~ (bitwise NOT) Takes one number and inverts all bits of it

	{
	unsigned int a = 8;				//binary value is 00000000000000000000000000001000
	unsigned int b = ~a;			//binary vlaue is 11111111111111111111111111110111		->	4294967287
	writeStr("b = %d", b);
	}

	{
	int a = 8;						//binary value is 00000000000000000000000000001000
	int b = ~a;						//binary vlaue is 11111111111111111111111111110111		->	4294967287
	int c = 4294967287;				//value is -9
	writeStr("b = %d", b);
	}

	unsigned int color = 0xee00ff77;

	unsigned int r = (color) >> 24;		
	unsigned int g = (color << 8)  >> 24;
	unsigned int b = (color << 16) >> 24;
	unsigned int a = (color << 24) >> 24;

}

void ThreadsExample()
{
	std::thread thread1 (Thread1Method); 
	std::thread thread2 (Thread2Method); 
	
	// synchronize threads...
	thread1.join();					// pauses until first finishes
	thread2.join();					// pauses until second finishes
}


void Thread1Method()
{
	writeStr("\n");

	for(int i=0; i<50; i++)
	{
		writeStr("\nFrom Thread1Method %d", i);
		Sleep(5);
	}
}


void Thread2Method()
{
	writeStr("\n");

	for(int i=0; i<50; i++)
	{
		writeStr("\nFrom Thread2Method %d", i);
		Sleep(5);
	}
}


void EvalueStatements()
{
	int a = 10;
	int* b = &a;

	writeStr("\n starting values \n a = %d, *b = %d, address of b = %d", a, (*b), b);

	(*b)++;
	writeStr("\n after (*b)++ \n a = %d, *b = %d, address of b = %d", a, (*b), b);

	b++;
	writeStr("\n after b++ \n a = %d, *b = %d, address of b = %d", a, (*b), b);
}


void StaticAndDynamicCast()
{
	{
		//Here we know surely Dervied1 is devired from Base and safely casting to Derived1 again.
		Base* base = new Derived1();
		Derived1* derived1 = static_cast<Derived1*>(base);
		derived1->PrintValue();			//It prints 1234
	}

	{
		Base* base = new Derived1();
		//Temp* temp = static_cast<Temp*>(base);		//Gives complilation error because base class not either super class 
														//or sub class to Temp class.
	}

	{
		//Here Derived2 object memory with Derived1 class pointer leads to undefined behaviour.
		Base* base = new Derived2();
		Derived1* derived1 = static_cast<Derived1*>(base);
		derived1->PrintValue();		//It prints garbage value because it takes first 4 bytes of memory in Derived2 object memory 
									//becase of int date type.
									//If Derived2 class contains integer as first variable then it simply prints its value.
	}


	{
		//dynamic_cast example...

		Base* base = new Derived2();
		Derived1* derived1 = dynamic_cast<Derived1*>(base);

		if(derived1)
		{
			derived1->PrintValue();		//this functions wont execute because derived will be NULL.
		}
		else
		{
			writeStr("dynamic_cast from base pointer to Derived1 class is unsuccessful.");
		}
	}

}

void VirtualKeyWordUsage()
{
	//In object-oriented programming, in languages such as C++, a virtual function or virtual method is an inheritable and 
	//overridable function or method for which dynamic dispatch is facilitated. This concept is an important 
	//part of the (runtime) polymorphism portion of object-oriented programming (OOP).


	//*) Can constructor made with virtual key word ? If yes/no what is the reason for it ?
	//first of all it is a compilation error if contructor made with virtual.
	//virtual functions are used in order to invoke functions based on the type of object pointed to by the pointer, 
	//and not the type of pointer itself. But a constructor is not "invoked". 
	//It is called only once when an object is declared. So, a constructor cannot be made virtual in C++


	//*) Can distructor made with virtual key word ? If yes/no what is the reason for it ?
	//If your base class destructor is virtual then objects will be destrcuted in a order(firstly derived object then base ). 
	//If your base class destructor is NOT virtual then only base class object will 
	//get deleted(because pointer is of base class "Base *myObj"). So there will be memory leak for derived object.


	//Example 1:
	{
		Derived1* derived1 = new Derived1();	//Create Derived class object
		Base* base = (Base*)derived1;			//Assign it to Base class pointer

		base->Method1();						//Calling virtual method of Base class.
												//Since Base class Method1 is virtual and Derived1 class has overridden Method1
												//Call will be directed to Derived1 class method at runtime.

		base->Method2();						//Base class Method2 method will be called.

		//base->Method3();						//Compile time error, Because Method3 is private in Base class and compiler simply
												//checks the pointer pointing to the class and method accessibility
	
		base->Method4();						//Since Base::Method4 is pure virtual method, Derived1 class Method4 will be called.

		delete base;
	}


	//Example 2:
	{
		Base* base = (Base*)new Derived1Derived();

		base->Method1();						//this will call to Derived1Derived::Method1 method.
												//Class order Base -> Dervied1 -> Dervied1Dervied
												//Method1 exist in Base class & Derived1 class which is immediate super class of 
												//Derived1Derived class. And virtual in Both Base and Derived1 classes.
		delete base;
	}
}


void SortVectorElements()
{
    int arr[] = {10, 20, 5, 23 ,42 , 15};
    int n = sizeof(arr)/sizeof(arr[0]);
    vector<int> vect(arr, arr+n);
 
    writeStr("\nVector is : ");

    for (int i=0; i<n; i++)
        writeStr(" %d ",vect[i]);
 
    // Sorting the Vector in Ascending order
    sort(vect.begin(), vect.end());
 
    writeStr("\nVector after sorting is : ");
    for (int i=0; i<n; i++)
        writeStr(" %d ",vect[i]);
 
    // Reversing the Vector
    reverse(vect.begin(), vect.end());
 
    writeStr("\nVector after reversing is : ");
    for (int i=0; i<n; i++)
        writeStr(" %d ",vect[i]);
 
    writeStr("\nMaximum element of vector is: ");
    writeStr("%d",*max_element(vect.begin(), vect.end()));
 
    writeStr("\nMinimum element of vector is: ");
    writeStr("%d",*min_element(vect.begin(), vect.end()));
 
    // Starting the summation from 0
    writeStr("\nThe summation of vector elements is: ");
    writeStr("%d",accumulate(vect.begin(), vect.end(), 0));
}



/*
9. dynamic casting and static casting and interprete casting
7. Private virtual functions behavior in run time polymorphism
11. Multi Threading, Semaphores and Metaphores

1. Containers in c++		http://www.geeksforgeeks.org/the-c-standard-template-library-stl/
							http://www.cplusplus.com/reference/stl/


2. Copy constructor in c++  http://www.geeksforgeeks.org/copy-constructor-in-cpp/
4. deep copy shallow copy in c++


3. Design patterns in c++	http://www.geeksforgeeks.org/design-patterns-set-1-introduction/
							http://www.geeksforgeeks.org/design-patterns-set-2-factory-method/


5. What is class, object, encapsulation, inheritance(MultiLevel, Multiple, Single), Runtime polymorphism.

10. Data Structures
12. Map, Vectors Usage and Advantages and dis-advantages
13. Sorted Map and UnSorted Map usage
14. Mutable array and unMutable array
15. Volatile and extern Keywords Usage
16. Smart pointers
17. Deletion of double dimension array
*/
