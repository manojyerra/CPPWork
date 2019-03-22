#ifndef stringExt_H
#define stringExt_H
#pragma once

#include <string>
using namespace std;

class stringExt : public string
{
private:

public:
	stringExt();
	stringExt(const char* str);
	stringExt(const stringExt& str);
	~stringExt();

	stringExt& operator=(const stringExt& str);
};

#endif
