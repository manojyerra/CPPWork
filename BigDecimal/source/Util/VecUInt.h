#ifndef VecUInt_H
#define VecUInt_H
#pragma once

class VecUInt
{
private:
	unsigned int _capacity;
	unsigned int _incrementInCapacity;	

	int _size;
	unsigned int* _arr;
	
	void ReCreateMem();

public:
	static int memCreateTime;

	VecUInt();
	VecUInt(unsigned int capacity);
	~VecUInt();

	void SetIncrementCapacity(unsigned int incrementCapacity);
	unsigned int size();

	void push_back(unsigned int val);
	void pop_back();

	void LeftShift(int numIndex);

	unsigned int& const operator[](unsigned int i) const;
	unsigned int& operator[](unsigned int i);
};

#endif
