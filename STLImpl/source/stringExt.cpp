#include "stringExt.h"

stringExt::stringExt() : string()
{
}

stringExt::stringExt(const char* str) : string(str)
{
}

stringExt::stringExt(const stringExt& str) : string(str)
{
}

stringExt& stringExt::operator=(const stringExt& str)
{
	return (stringExt&)((string*)(this))->operator=(str);
}

stringExt::~stringExt()
{
	printf("destructor");
}
