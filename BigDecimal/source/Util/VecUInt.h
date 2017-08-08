#ifndef VecUInt_H
#define VecUInt_H
#pragma once

class VecUInt
{
private:
	unsigned int* _arr;
	unsigned int _size;
	unsigned int _capacity;
	
	void ReCreateMem();

public:
	static int memCreateTime;

	VecUInt();
	VecUInt(unsigned int capacity);
	~VecUInt();

	unsigned int size();
	void setSize(int size);
	unsigned int capacity();

	void push_back(unsigned int val);
	void pop_back();

	unsigned int& const operator[](unsigned int i) const;
	unsigned int& operator[](unsigned int i);

	unsigned int at(unsigned int i);

	unsigned int* GetArray();

	VecUInt* Clone();
};

#endif


//void LeftShift(int numIndex);
