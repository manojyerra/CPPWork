//#ifdef _DEBUG
//   #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#else
//   #define DEBUG_CLIENTBLOCK
//#endif // _DEBUG
//
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#endif
//
//#ifdef _DEBUG
//#define new DEBUG_CLIENTBLOCK
//#endif

#include "vld.h"

int main()
{
	char* arr1 = new char[100];
	//delete[] arr1;

	return 0;
}
