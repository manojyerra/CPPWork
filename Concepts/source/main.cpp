#include "Base.h"
#include "Derived1.h"
#include "DefinesAndIncludes.h"

void VirtualKeyWordUsage();

int main()
{
	VirtualKeyWordUsage();

	print("\n\n************** End of program **************\n\n");
	return 0;
}

void VirtualKeyWordUsage()
{
	Derived1* derived1 = new Derived1();

	Base* base = (Base*)derived1;

	base->Method1();
	base->Method2();
	//base->Method3();	//compilatin error if we uncomment this line

	delete base;
}


/*
1. Containers in c++
2. Design patterns in c++
3. Copy constructor in c++  http://www.geeksforgeeks.org/copy-constructor-in-cpp/
4. deep copy shallow copy in c++
5. What is class, object, encapsulation, inheritance(MultiLevel, Multiple, Single), Runtime polymorphism.
6. Virtual keywords
7. Private virtual functions behavior in run time polymorphism
8. virtual destructors
9. dynamic casting and static casting and interprete casting
10. Data Structures
11. Multi Threading, Semaphores and Metaphores
12. Map, Vectors Usage and Advantages and dis-advantages
13. Sorted Map and UnSorted Map usage
14. Mutable array and unMutable array
15. Volatile and extern Keywords Usage
16. Smart pointers
17. Deletion of double dimension array
*/