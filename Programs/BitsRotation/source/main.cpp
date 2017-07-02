#include "string.h"
#include "math.h"
#include "stdio.h"

#define INT_BITS 32

long int RotateLeft(int num, int numRotateBits)
{
	return ( (num << numRotateBits) | (num >> (INT_BITS-numRotateBits)) );
}

long int RotateRight(int num, int numRotateBits)
{
	return ( (num >> numRotateBits) | (num << (INT_BITS-numRotateBits)) );
}

int main(int argc, char **argv)
{
	long int valueAfterLeftRotate = RotateLeft(8, 3);
	long int valueAfterRightRotate = RotateRight(64, 3);
}
