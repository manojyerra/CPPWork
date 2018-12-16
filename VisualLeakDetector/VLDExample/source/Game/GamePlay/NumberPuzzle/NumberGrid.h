#ifndef NUMBER_GRID_H
#define NUMBER_GRID_H
#pragma once

#include "Sprite.h"
#include "ButtonNew.h"
#include <vector>
#include <string>
using namespace std;

class NumberGrid
{
private:
	int _number;
	char _numStr[16];

	Sprite* _numberImg;

	bool _isMoving;
	bool _justNowMoveOver;
	int _direction;
	int _destin;
	float _speed;

	bool _glow;

	float _x;
	float _y;
	float _w;
	float _h;

	Sprite* _rightImg;
	int _statusImgW;

	float _initX;
	float _initY;

public:
	static const int NONE = 0;
	static const int LEFT = 1;
	static const int RIGHT = 2;
	static const int UP = 3;
	static const int DOWN = 4;

	NumberGrid(int number, float x, float y, float drawWidth, float drawHeight, int levelNum);
	~NumberGrid();

	bool Contains(float x, float y);
	void Update(float deltaTime);
	void Move(int directoin);
	bool MoveOverJustNow();
	bool IsMoving();
	void Glow(bool glow);

	void SetX(float x);
	void SetY(float y);
	void SetBounds(float x, float y, float w, float h);
	float GetX();
	float GetY();
	float GetW();
	float GetH();

	void Draw();
};

#endif