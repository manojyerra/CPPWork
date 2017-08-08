#include "VecUInt.h"
#include "stdio.h"
#include "string.h"
#include "DefinesAndIncludes.h"

int VecUInt::memCreateTime = 0;

VecUInt::VecUInt()
{
	_capacity = 1024;
	_size = 0;

	_arr = new unsigned int[_capacity];
}

VecUInt::VecUInt(unsigned int capacity)
{
	_capacity = capacity;
	_size = 0;

	_arr = new unsigned int[_capacity];
}

void VecUInt::ReCreateMem()
{
	unsigned startTime = GetTickCount();

	int newCapacity = 2*_capacity;

	writeConsole("\n****** ReCreateMem called.. Capacity %d, newCapacity %d ******\n", _capacity, newCapacity);

	unsigned int* newArr = NULL;

	if(_arr)
	{
		newArr = new unsigned int[newCapacity];

		memcpy(newArr, _arr, _capacity*sizeof(unsigned int));
		
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

unsigned int VecUInt::at(unsigned int i)
{
	return _arr[i];
}

unsigned int VecUInt::size()
{
	return _size;
}

void VecUInt::setSize(int size)
{
	_size = size; 
}

unsigned int VecUInt::capacity()
{
	return _capacity;
}

unsigned int* VecUInt::GetArray()
{
	return _arr;
}

VecUInt* VecUInt::Clone()
{
	VecUInt* newObj = new VecUInt(_capacity);

	newObj->setSize( _size );

	memcpy(newObj->GetArray(), _arr, _size*sizeof(unsigned int));

	return newObj;
}

VecUInt::~VecUInt()
{
	if(_arr)
	{
		delete[] _arr;
		_arr = NULL;
	}
}


//void VecUInt::LeftShift(int numIndex)
//{
//	unsigned int newCapacity = _capacity+numIndex;
//
//	unsigned int* newArr = new unsigned int[newCapacity];
//	memset(newArr, 0, newCapacity*sizeof(unsigned int));
//
//	memcpy(&newArr[numIndex], _arr, size()*sizeof(unsigned int));
//
//	delete[] _arr;
//
//	_arr = newArr;
//	_size = size() + numIndex;
//	_capacity = newCapacity;
//}
