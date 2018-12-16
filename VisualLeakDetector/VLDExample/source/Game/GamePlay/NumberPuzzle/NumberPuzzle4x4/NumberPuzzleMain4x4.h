#ifndef NUMBER_SLATE_GAME_H
#define NUMBER_SLATE_GAME_H
#pragma once

#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"
#include "NumGridsManager.h"
#include "NumberGrid.h"
#include "AfterLevelOver.h"
#include "PauseScreen.h"
#include "RectPrim.h"
#include "LeaderBoard.h"

#include <vector>
using namespace std;

class NumberPuzzleMain4x4
{
private:
	Sprite* _timerBarBgImg;
	Sprite* _timerBarFillImg;

	AfterLevelOver* _afterLevelOver;
	PauseScreen* _pauseScreen;
	LeaderBoard* _leaderBoard;

	ButtonNew* _pauseBtn;
	ButtonNew* _homeBtn;
	ButtonNew* _replayBtn;
	ButtonNew* _leaderBtn;
	ButtonNew* _picBtn;

	bool _isShowingPic;
	bool _showGlowEffect;
	float _glowTime;
	int _glowOnOffCount;
	float _playTimeCount;
	int _numMoves;
	float _timer100PercentW;

	NumGridsManager* _numGridsManager;

	NumberGrid* _activeGrid;
	float _prevX;
	float _prevY;

	void SaveStatus();
	void LevelGen();
	void GetLevelData_Num3x3(int levelNum, int* arr);
	void GetLevelData_Num4x4(int levelNum, int* arr);
	void GetLevelData_Num5x5(int levelNum, int* arr);

public:
	NumberPuzzleMain4x4();
	~NumberPuzzleMain4x4();
	void RunGamePlay();
	void Update();
	void Draw();
};

#endif