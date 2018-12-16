#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"
#include "Page.h"
#include "RectPrim.h"
#include "MsgBox.h"

class MainMenu : Page
{
private:
	ButtonNew* _playBtn;
	ButtonNew* _highScoresBtn;
	ButtonNew* _submitDetailsBtn;
	ButtonNew* _reviewBtn;
	ButtonNew* _shareOnGPlusBtn;
	ButtonNew* _exitBtn;

	ButtonNew* _shareOnFacebookBtn;
	ButtonNew* _leaderBoardBtn;
	ButtonNew* _moreGamesBtn;

	MsgBox* _msgBox;
	bool _exit;

public:
	MainMenu();
	~MainMenu();
	void Update();
	void Draw();

	bool IsLeaderBoardBtnClicked();
	bool IsSubmitDetailsBtnClicked();
	bool IsReviewBtnClicked();
	bool IsShareOnGPlusBtnClicked();
	bool IsShareOnFacebookBtnClicked();
	bool IsExitClicked();
};

#endif
