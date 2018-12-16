#ifndef LINE_PRIM_H
#define LINE_PRIM_H
#pragma once
#include "Prim.h"

class LinePrim : Prim
{
private:
	float _x1;
	float _y1;
	float _x2;
	float _y2;

	int _r;
	int _g;
	int _b;
	int _a;

public:
	LinePrim(float x1, float y1, float x2, float y2);
	~LinePrim();

	bool Update();
	void SetColor(int r, int g, int b, int a);
	void Draw();
	static void Draw(float x1, float y1, float x2, float y2, unsigned int color);
	static void Draw(float x1, float y1, float x2, float y2, unsigned int color, float lineWidth);
	static void DrawStrippedLine(float x1, float y1, float x2, float y2, unsigned int color, float lineWidth);
};

#endif
