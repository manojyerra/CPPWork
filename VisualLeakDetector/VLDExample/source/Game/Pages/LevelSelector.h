#ifndef LEVEL_SELECTOR_H
#define LEVEL_SELECTOR_H
#pragma once

#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"
#include "LevelsShowScreen.h"
#include "RectPrim.h"

#include "Page.h"
#include <vector>
using namespace std;

class LevelSelector : public Page
{
private:
	RectPrim* _bg;
	Sprite* _loadingImg;
	ButtonNew* _homeBtn;
	
	Sprite* _innerCirImg;
	Sprite* _ourterCirImg;

	int NUM_PAGES;
	
	vector<LevelsShowScreen*> _levelScreensVec;
	int _activeLevelScreenIndex;
	
	int _activeLetters;
	int _moveCount;
	int _moveSpeed;
	bool _startMoveRight;
	bool _startMoveLeft;
	
	bool _showLoading;
	int _levelBtnNumber;

	void DrawPageIndicators();

public:
	LevelSelector();
	~LevelSelector();

	void Reset();
	void Update();
	void MoveAll(float x, float y);

	void Draw();
};

#endif
