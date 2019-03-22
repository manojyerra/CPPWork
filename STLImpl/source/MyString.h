#ifndef MyString_H
#define MyString_H
#pragma once

#include <string>
using namespace std;

class MyString
{
private:
	char* _arr;
	unsigned int _size;
	unsigned int _capacity;
	
	void ReCreateMem();
	void MemCheck(unsigned int extraMem);

public:
	MyString();
	MyString(const MyString& str);
	MyString(const char* str);
	~MyString();

	void append(const char* str);
	MyString& operator=(const MyString& str);
	MyString& operator+(const MyString& str);
	MyString& operator+=(const MyString& str);
	MyString& operator++();

	const char* c_str();

	unsigned int size();
	unsigned int capacity();
};

#endif
