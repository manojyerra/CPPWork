#include "string.h"
#include "math.h"
#include "stdio.h"

int GetNum(char ch)
{
	int val = -1;
		
	if(ch >='A' && ch <= 'Z')
		val = ch - 'A' + 1;
		
	return val;
}

int ExcelColumnNumber(char* str)
{
	int maxDigit = 26;
		
	int strLen = strlen(str);
	int sum = 0;
		
	for(int i=0; i<strLen; i++)
	{
		char ch = str[i];
		int val = GetNum(ch);
		int powVal = (int)(pow((double)maxDigit, (int)(strLen-1-i)));
			
		sum += val * powVal;
	}

	return sum;
}

int main(int argc, char **argv)
{
	char* str = "AB";

	int num = ExcelColumnNumber(str);

	printf("Excel column number of \"%s\" = %d",str,num);
}
