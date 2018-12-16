#ifndef RECT_EDIT_PRIM_H
#define RECT_EDIT_PRIM_H
#pragma once

#include "../Primitives/RectPrim.h"

#include <vector>
using namespace std;

class RectEditPrim
{
private:
	RectPrim* _mainRect;
	vector<RectPrim*> _rectPrimsVec;
	RectPrim* _activeRect;

	int _r;
	int _g;
	int _b;
	int _a;
	bool _active;

	void ResetRectBounds();

public:
	RectEditPrim(float x, float y, float w, float h);
	~RectEditPrim();

	bool Update();
	void Move(float x, float y);
	void SetColor(int r, int g, int b, int a);
	RectPrim* GetEditRect(float x, float y);

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	void SetPos(float x, float y);
	void SetSize(float w, float h);
	void SetBounds(float x, float y, float w, float h);
	void SetActive(bool active);
	bool IsActive();

	void Draw();
	void Terminate();
};

#endif
