#ifndef RECT_PRIM_H
#define RECT_PRIM_H
#pragma once
#include "Prim.h"

class RectPrim : Prim
{
private:
	float _x;
	float _y;
	float _w;
	float _h;
	float _angle;
	unsigned int _color;

public:
	RectPrim(float x, float y, float width, float height, float angle, unsigned int color);
	~RectPrim();

	bool Contains(float X, float Y);
	void SetRotation(float angle);

	void SetColor(int red, int green, int blue, int alpha);
	void SetColor(unsigned int color);
	
	unsigned int GetColor();

	void SetAlpha(int alpha);
	int GetAlpha();

	void SetX(float x);
	void SetY(float y);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetPos(float X, float Y);
	void SetSize(float w, float h);
	void SetBounds(float x, float y, float width, float height);

	float GetX();
	float GetY();
	float GetMidX();
	float GetMidY();
	float GetWidth();
	float GetHeight();

	void Draw();
	static void Draw(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2);
	static void Draw(float x, float y, float w, float h, float angle, unsigned int color);
	static void DrawBorder(float x, float y, float w, float h, float lineWidth, unsigned int color);
};
#endif
