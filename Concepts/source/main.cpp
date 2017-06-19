#include "Base.h"
#include "Derived1.h"
#include "Derived2.h"
#include "Derived1Derived.h"
#include "Temp.h"
#include "DefinesAndIncludes.h"

#include <thread>

void VirtualKeyWordUsage();
void StaticAndDynamicCast();
void EvalueStatements();

void Thread1Method();
void Thread2Method();


int main()
{
	EvalueStatements();

	VirtualKeyWordUsage();

	StaticAndDynamicCast();

	std::thread thread1 (Thread1Method); 
	std::thread thread2 (Thread2Method); 
	
	// synchronize threads...
	thread1.join();					// pauses until first finishes
	thread2.join();					// pauses until second finishes

	print("\n\n************** End of program **************\n\n");
	return 0;
}

void Thread1Method()
{
	print("\n");

	for(int i=0; i<100; i++)
	{
		print("\nFrom Thread1Method %d", i);
	}
}

void Thread2Method()
{
	print("\n");

	for(int i=0; i<100; i++)
	{
		print("\nFrom Thread2Method %d", i);
	}
}


void EvalueStatements()
{
	int a = 123;
	int* b = &a;

	print("\n starting values \n a = %d, *b = %d, address of b = %d", a, (*b), b);

	(*b)++;
	print("\n after (*b)++ \n a = %d, *b = %d, address of b = %d", a, (*b), b);

	b++;

	print("\n after b++ \n a = %d, *b = %d, address of b = %d", a, (*b), b);

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
			print("dynamic_cast from base pointer to Derived1 class is unsuccessful.");
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


/*
6. Virtual keywords
9. dynamic casting and static casting and interprete casting
7. Private virtual functions behavior in run time polymorphism
8. virtual destructors


1. Containers in c++		http://www.geeksforgeeks.org/the-c-standard-template-library-stl/
							http://www.cplusplus.com/reference/stl/


2. Copy constructor in c++  http://www.geeksforgeeks.org/copy-constructor-in-cpp/
4. deep copy shallow copy in c++


3. Design patterns in c++	http://www.geeksforgeeks.org/design-patterns-set-1-introduction/
							http://www.geeksforgeeks.org/design-patterns-set-2-factory-method/


5. What is class, object, encapsulation, inheritance(MultiLevel, Multiple, Single), Runtime polymorphism.

10. Data Structures
11. Multi Threading, Semaphores and Metaphores
12. Map, Vectors Usage and Advantages and dis-advantages
13. Sorted Map and UnSorted Map usage
14. Mutable array and unMutable array
15. Volatile and extern Keywords Usage
16. Smart pointers
17. Deletion of double dimension array
*/
