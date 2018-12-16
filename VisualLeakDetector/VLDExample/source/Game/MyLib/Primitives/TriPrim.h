#ifndef TRI_PRIM_H
#define TRI_PRIM_H
#pragma once
#include "Prim.h"

class TriPrim : Prim
{
private:
	float _x[3];
	float _y[3];
	
	int _r;
	int _g;
	int _b;
	int _a;

public:
	TriPrim(float x1, float y1, float x2, float y2, float x3, float y3);
	~TriPrim();

	void SetColor(int r, int g, int b, int a);
	void Draw();
};

#endif
