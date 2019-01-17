#ifndef MyVector_H
#define MyVector_H

template <class T> 
class MyVector
{
private:
	T *ptr;
	int size;
	int capacity;

public:
	MyVector();
	~MyVector();

	void push_back(T val);
	T get(int index);
};


template <class T>
MyVector<T>::MyVector()
{
	size = 0;
	capacity = 16;
	ptr = new T[capacity];
}

template <class T>
MyVector<T>::~MyVector()
{
}

template <class T>
void MyVector<T>::push_back(T val)
{
	if (size < capacity)
	{
		ptr[size] = val;
		size++;
	}
}

template <class T>
T MyVector<T>::get(int index)
{
	return ptr[index];
}

#endif