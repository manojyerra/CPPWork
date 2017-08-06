#ifndef UtilFuncs_H
#define UtilFuncs_H

#include <vector>
#include <string>
using namespace std;

class UtilFuncs
{
public:
	static int floatToIntBits(float val);
	static float nearVal(float x);
	static double Exp(double xVal, int nVal, double factor);
	static double factorial(int n);

	static float* AddFloat(float* arr, int arrSize, float addVal);
	static vector<string> OpenFileDialog(char* filter = "All Files (*.*)\0*.*\0", bool allowMultiSel=true);
	static string SaveFileDialog(char* filter = "All Files (*.*)\0*.*\0");
	static string OpenFolderDialer();
};

#endif