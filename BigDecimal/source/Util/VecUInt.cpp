#include "VecUInt.h"
#include "stdio.h"
#include "string.h"
#include "DefinesAndIncludes.h"

int VecUInt::memCreateTime = 0;

VecUInt::VecUInt()
{
	_capacity = 512;
	_incrementInCapacity = 512;

	_arr = new unsigned int[_capacity*3];

	_size = 0;
}

VecUInt::VecUInt(unsigned int capacity)
{
	_capacity = capacity;
	_incrementInCapacity = 512;

	_arr = new unsigned int[_capacity*3];

	_size = 0;
}

void VecUInt::SetIncrementCapacity(unsigned int incrementCapacity)
{
	_incrementInCapacity = incrementCapacity;
}

void VecUInt::ReCreateMem()
{
	unsigned startTime = GetTickCount();

	writeConsole("\n****** ReCreateMem called.. ******\n");

	int newCapacity = 2*_capacity; // + _incrementInCapacity;

	unsigned int* newArr = NULL;

	if(_arr)
	{
		newArr = new unsigned int[newCapacity];

		memcpy(newArr, _arr, _capacity);
		
		delete[] _arr;
		
		_arr = newArr;
	}
	
	_capacity = newCapacity;

	memCreateTime += GetTickCount() - startTime;
}

void VecUInt::push_back(unsigned int val)
{
	_arr[_size] = val;

	_size++;

	if(_size >= _capacity)
		ReCreateMem();
}

void VecUInt::pop_back()
{
	_size--;

	if(_size < 0)
		_size = 0;
}

unsigned int& const VecUInt::operator[](unsigned int i)const
{
	return _arr[i];
}

unsigned int& VecUInt::operator[](unsigned int i)
{
	return _arr[i];
}

void VecUInt::LeftShift(int numIndex)
{
	unsigned int newCapacity = _capacity+numIndex;

	unsigned int* newArr = new unsigned int[newCapacity];
	memset(newArr, 0, newCapacity*sizeof(unsigned int));

	memcpy(&newArr[numIndex], _arr, size()*sizeof(unsigned int));

	delete[] _arr;

	_arr = newArr;
	_size = size() + numIndex;
	_capacity = newCapacity;
}

unsigned int VecUInt::size()
{
	return _size;
}

VecUInt::~VecUInt()
{
	if(_arr)
		delete[] _arr;
}
