#ifndef AFTERLEVELOVER_H
#define AFTERLEVELOVER_H
#pragma once

#include "AnimSprite.h"
#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"
#include "LeaderBoard.h"
#include "MsgBox.h"

class AfterLevelOver
{
private:
	Sprite* _disableStars[3];
	ButtonNew* _platNextBtn;

	ButtonNew* _shareBtn;
	ButtonNew* _rateBtn;
	ButtonNew* _leaderBoardBtn;

	ButtonNew* _homeBtn;
	ButtonNew* _replayBtn;

	vector<AnimSprite*> _animStarsVec;

	LeaderBoard* _leaderBoard;
	MsgBox* _msgBox;
	MsgBox* _rateMsgBox;

	bool _isActive;
	float _timeCount;
	int _gameResult;
	int _atPresentShowNumStars;
	bool _showOnlyGlow;

	int _currStars;
	int _currTime;
	int _currMoves;

	int _rank;
	static int prevRank;

	string _rateFilePath;
	void SetLevelFinished();

public:
	static const int WIN = 1;
	static const int LOSE = 2;

	AfterLevelOver();

	void Update();
	void Draw();
	void SetGameResult(int gameResult);
	bool IsActive();
	void SetActive(bool isActive);

	void SetCurrStars(int stars);
	void SetCurrTime(int time);
	void SetCurrMoves(int moves);

	~AfterLevelOver();
};
#endif