#ifndef COLORTHEME_H
#define COLORTHEME_H
#pragma once

#include "RectPrim.h"

class ColorTheme
{
private:
	static ColorTheme* _ref;

	ColorTheme();
	~ColorTheme();

public:
	unsigned char bgTR;
	unsigned char bgTG;
	unsigned char bgTB;
	unsigned char bgTA;

	unsigned char bgBR;
	unsigned char bgBG;
	unsigned char bgBB;
	unsigned char bgBA;

	static ColorTheme* GetInstance();
	static void DeleteInstance();

	static void Draw();
	static int GetButtonColorID();
};

#endif
