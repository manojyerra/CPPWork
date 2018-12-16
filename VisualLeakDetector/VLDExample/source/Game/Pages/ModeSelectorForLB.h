#ifndef MODESELECTORFORLB_H
#define MODESELECTORFORLB_H
#pragma once

#include "ButtonNew.h"
#include "Page.h"
#include "LeaderBoard.h"

class ModeSelectorForLB : Page
{
private:
	ButtonNew* _playBtn3;
	ButtonNew* _playBtn4;
	ButtonNew* _playBtn5;
	ButtonNew* _homeBtn;

	LeaderBoard* _leaderBoard;

public:
	ModeSelectorForLB();
	~ModeSelectorForLB();
	void Update();
	void Draw();
};

#endif
