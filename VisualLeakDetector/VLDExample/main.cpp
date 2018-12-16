#include "vld.h"
#include <stdlib.h>

#include <vector>
#include <string>
using namespace std;

int main()
{
	int* pBuffer = new int[100];
	void* leak = malloc(222);
	return 0;
}