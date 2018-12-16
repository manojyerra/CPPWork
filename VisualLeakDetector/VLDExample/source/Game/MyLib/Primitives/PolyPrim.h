#ifndef POLY_PRIM_H
#define POLY_PRIM_H
#pragma once

#include "Prim.h"
#include "../MathLib/Point.h"
#include <vector>
using namespace std;

class PolyPrim : public Prim
{
private:
	vector<Point> _vec;
	int _r;
	int _g;
	int _b;
	int _a;

public:
	PolyPrim(vector<Point> vec);
	~PolyPrim();

	void SetColor(int r, int g, int b, int a);
	void Draw();
};

#endif
