#ifndef DefinesAndIncludes_H
#define DefinesAndIncludes_H

#include <windows.h>
#include <stdio.h>

#define print DefinesAndIncludes::write

class DefinesAndIncludes
{
public:
	static void write(const char * pszFormat, ...);
};


#endif
