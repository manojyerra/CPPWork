#include "Utils.h"

unsigned int Utils::GetColor(unsigned int color, int colorID)
{
	unsigned char r	= (color >> 24) & 255;
	unsigned char g	= (color >> 16) & 255;
	unsigned char b	= (color >> 8) & 255;
	unsigned char a	= (color ) & 255;

	return GetColor(r, g, b, a, colorID);
}

unsigned int Utils::GetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, int colorID)
{
	if(colorID == RBG)
	{
		return (unsigned int)( (r<<24) + (b<<16) + (g<<8) + a );
	}
	else if(colorID == GRB)
	{
		return (unsigned int)( (g<<24) + (r<<16) + (b<<8) + a );
	}
	else if(colorID == GBR)
	{
		return (unsigned int)( (g<<24) + (b<<16) + (r<<8) + a );
	}
	else if(colorID == BRG)
	{
		return (unsigned int)( (b<<24) + (r<<16) + (g<<8) + a );
	}
	else if(colorID == BGR)
	{
		return (unsigned int)( (b<<24) + (g<<16) + (r<<8) + a );
	}

	return (unsigned int)( (r<<24) + (g<<16) + (b<<8) + a );
}

void Utils::SetColorToBuffer(unsigned char* buf, int w, int h, int bytesPP, int colorID)
{
	int size = w*h*bytesPP;

	if(colorID == RBG)
	{
		for(int i=0; i<size; i+=bytesPP)
		{
			unsigned char r = buf[i+0];
			unsigned char g = buf[i+1];
			unsigned char b = buf[i+2];

			buf[i+0] = r;
			buf[i+1] = b;
			buf[i+2] = g;
		}
	}
	else if(colorID == GRB)
	{
		for(int i=0; i<size; i+=bytesPP)
		{
			unsigned char r = buf[i+0];
			unsigned char g = buf[i+1];
			unsigned char b = buf[i+2];

			buf[i+0] = g;
			buf[i+1] = r;
			buf[i+2] = b;
		}
	}
	else if(colorID == GBR)
	{
		for(int i=0; i<size; i+=bytesPP)
		{
			unsigned char r = buf[i+0];
			unsigned char g = buf[i+1];
			unsigned char b = buf[i+2];

			buf[i+0] = g;
			buf[i+1] = b;
			buf[i+2] = r;
		}
	}
	else if(colorID == BRG)
	{
		for(int i=0; i<size; i+=bytesPP)
		{
			unsigned char r = buf[i+0];
			unsigned char g = buf[i+1];
			unsigned char b = buf[i+2];

			buf[i+0] = b;
			buf[i+1] = r;
			buf[i+2] = g;
		}
	}
	else if(colorID == BGR)
	{
		for(int i=0; i<size; i+=bytesPP)
		{
			unsigned char r = buf[i+0];
			unsigned char g = buf[i+1];
			unsigned char b = buf[i+2];

			buf[i+0] = b;
			buf[i+1] = g;
			buf[i+2] = r;
		}
	}
}