#ifndef LEVELS_SHOW_SCREEN_H
#define LEVELS_SHOW_SCREEN_H
#pragma once

#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"
#include "LevelBtn.h"

#include <vector>
using namespace std;

class LevelsShowScreen
{
private:
	vector<LevelBtn*> _levelBtnsVec;
	vector<ButtonNew*> _buttonsVec;

	int _pageNum;
	int _totLevels;
	int _lastUnLockLevelNum;
	int _rows;
	int _cols;
	int _btnW;
	int _btnH;
	int _hGap;
	int _vGap;

public:
	LevelsShowScreen(int pageNum, int rows, int cols);
	~LevelsShowScreen();

	void Reset(int pageNum);

	void SetPageNumber(int pageNum);
	void SetTotalLevels(int totLevels);
	void SetLastUnlockedLevels(int lastUnLockLevelNum);
	void SetRowAndCols(int rows, int cols);
	void SetHorAndVerGap(int horGap, int verGap);
	void SetBtnSize(int width, int height);

	void Move(int x, int y);
	LevelBtn* GetButton_OnClick();
	void Update();
	void Draw();
	void DeleteButtons();
};

#endif
