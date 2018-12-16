#ifndef NUM_GRIDS_MANAGER_H
#define NUM_GRIDS_MANAGER_H
#pragma once

#include "CommonLib/Sprite.h"
#include "NumberGrid.h"
#include "Sprite.h"
#include <vector>
using namespace std;

class NumGridsManager
{
private:
	vector<NumberGrid*> _numbersVec;
	Sprite* _finalImg;

	int _initX;
	int _initY;
	int _drawWidth;
	int _drawHeight;

	float _borderX;
	float _borderY;
	float _borderW;
	float _borderH;

	int _numXGrids;
	int _totGrids;
	
	bool _showFinalImg;
	bool _glowAllGrids;

public:
	NumGridsManager(int numXGrids, int* arr);
	~NumGridsManager();
	NumberGrid* GetIntersectGrid(NumberGrid* numGrid);
	NumberGrid* GetGrid(float x, float y);
	int GetGridIndex(NumberGrid* grid);
	NumberGrid* GetGridByIndex(int index);
	int GetEmptySpaceDirection(NumberGrid* numberGrid);
	bool CanMove(NumberGrid* numberGrid, int dir);
	bool IsWithInBorder(float x, float y);
	bool IsAnyGridMoveFinishedJustNow();
	bool IsInCorrectOrder();
	bool IsAnyGridMoving();
	void Update(float deltaTime);
	void Glow(bool glow);
	bool IsAllGridsGlowing();
	void ShowFinalImg(bool showFinalImg);
	void Draw(NumberGrid* numGrid);
};

#endif