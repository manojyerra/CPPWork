#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
	static const int RGB = 0;
	static const int RBG = 1;
	static const int GRB = 2;
	static const int GBR = 3;
	static const int BRG = 4;
	static const int BGR = 5;

	static unsigned int GetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, int colorID);
	static unsigned int GetColor(unsigned int color, int colorID);
	static void SetColorToBuffer(unsigned char* buf, int w, int h, int bytesPP, int colorID);
};

#endif