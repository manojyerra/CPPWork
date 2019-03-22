#ifndef Looper_H
#define Looper_H

using namespace std;



class Looper
{
private:
	void ConstructorTest();
	void AssignmentTest();
	void PlusOperatorTest();
	void PlusEqualsOperatorTest();
	void IncrementOperatorTest();
	void MemLeakTest();

	template <typename T>
	static void Swap(T& n1, T& n2)
	{
		T temp = n1;
		n1 = n2;
		n2 = temp;
	}

public:
	Looper(int windowWidth, int windowHeight);
	~Looper();
	void Draw(float deltaTime);
};

#endif
