#ifndef CIRCLE_PRIM_H
#define CIRCLE_PRIM_H
#pragma once
#include "Prim.h"

class CirclePrim : Prim
{
private:
	float _cx;
	float _cy;
	float _radius;
	float _angle;
	int _red,_green,_blue,_alpha;

public:
	CirclePrim(float cx, float cy, float radius);
	~CirclePrim();

	bool Update();
	bool Contains(float x, float y);
	void SetColor(int r, int g, int b, int a);
	void SetPos(float cx, float cy);
	void SetRadius(float radius);
	void SetRotation(float angle);
	void Draw();

};

#endif
