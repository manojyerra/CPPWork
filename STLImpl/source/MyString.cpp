#include "MyString.h"

MyString::MyString()
{
	_capacity = 32;
	_size = 0;
	_arr = new char[_capacity];
	_arr[_size] = '\0';
}

MyString::MyString(const char* str)
{
	_capacity = 32;
	_size = 0;
	_arr = new char[_capacity];
	_arr[_size] = '\0';

	unsigned int strLen = strlen(str);
	MemCheck(strLen);

	memcpy(_arr, str, strLen * sizeof(char));
	_size += strLen;

	_arr[_size] = '\0';
}

MyString::MyString(const MyString& str)
{
	_capacity = str._capacity;
	_size = str._size;

	_arr = new char[_capacity];

	memcpy(_arr, str._arr, _capacity);
}

MyString& MyString::operator=(const MyString& str)
{
	_capacity = str._capacity;
	_size = str._size;

	delete[] _arr;
	_arr = new char[_capacity];

	memcpy(_arr, str._arr, _capacity);

	return *this;
}

MyString& MyString::operator+(const MyString& str)
{
	MyString* newStr = new MyString(_arr);
	newStr->append(((MyString&)str).c_str());
	return *newStr;
}

MyString& MyString::operator+=(const MyString& str)
{
	append(((MyString&)str).c_str());
	return *this;
}

MyString& MyString::operator++()
{
	append("plus");
	return *this;
}

const char* MyString::c_str()
{
	return _arr;
}

void MyString::append(const char* str)
{
	unsigned int strLen = strlen(str);
	MemCheck(strLen);

	memcpy(&_arr[_size], str, strLen * sizeof(char));
	_size += strLen;

	_arr[_size] = '\0';
}

void MyString::MemCheck(unsigned int extraMem)
{
	if (_size + extraMem + 1 >= _capacity)
	{
		ReCreateMem();
		//ToDo : Check for _size+extraMem+1 < _capacity 
		MemCheck(extraMem);
	}
}

void MyString::ReCreateMem()
{
	int newCapacity = 2*_capacity;
	char* newArr = 0;

	if(_arr)
	{
		newArr = new char[newCapacity];
		memcpy(newArr, _arr, _capacity*sizeof(char));
		delete[] _arr;
		_arr = newArr;
	}
	
	_capacity = newCapacity;
}

unsigned int MyString::size()
{
	return _size;
}

unsigned int MyString::capacity()
{
	return _capacity;
}

MyString::~MyString()
{
	if(_arr)
	{
		delete[] _arr;
		_arr = 0;
	}

	_size = 0;
	_capacity = 0;
}
