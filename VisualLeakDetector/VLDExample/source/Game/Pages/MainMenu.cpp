#include "MainMenu.h"
#include "SaveManager.h"
#include "ModuleManager.h"
#include "PagesManager.h"
#include "GameInfo.h"
#include "Input.h"
#include "Platform.h"
#include "ColorTheme.h"

MainMenu::MainMenu()
{
	GameInfo* gameInfo = GameInfo::GetInstance();

	int sw = gameInfo->CodedW();

	_playBtn = NULL;
	_highScoresBtn = NULL;
	_leaderBoardBtn = NULL;
	_submitDetailsBtn = NULL;
	_reviewBtn = NULL;
	_shareOnGPlusBtn = NULL;
	_shareOnFacebookBtn = NULL;
	_moreGamesBtn = NULL;
	_exitBtn = NULL;

	int colorID = ColorTheme::GetButtonColorID();

	int y = 30;
	int w = 200*1.8;
	int h = 41*1.8;
	int gap = 40;

	int btnNum = 0;

	_playBtn = new ButtonNew("Play", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);							btnNum++;
	_highScoresBtn = new ButtonNew("High Scores", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);			btnNum++;
	_submitDetailsBtn = new ButtonNew("Edit Profile", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);		btnNum++;
	_exitBtn = new ButtonNew("Exit", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);							btnNum++;
	
	gap += 5;
	_reviewBtn = new ButtonNew("Rate", 10, y+btnNum*(h+gap), w, h, colorID);						
	_shareOnGPlusBtn = new ButtonNew("Share on g+", (sw-w-10), y+btnNum*(h+gap), w, h, colorID);			

	//_shareOnFacebookBtn = new ButtonNew("Share on Facebook", (sw-w)/2.0f, y+btnNum*(h+gap),w,h);		btnNum++;
	//_moreGamesBtn = new ButtonNew("More Games", (sw-w)/2.0f, y+btnNum*(h+gap), w, h);					btnNum++;

	_msgBox = new MsgBox("Do you want to exit the game?");
	_msgBox->SetBgSize(400,150);
	_msgBox->SetActive(false);
	_msgBox->SetInActiveOnBackPress(true);
	_msgBox->AddButton("Yes");
	_msgBox->AddButton("No");

	_exit = false;
}

void MainMenu::Update()
{
	if(_msgBox->IsActive())
	{
		_msgBox->Update();

		if(_msgBox->GetButtonIndex_OnClick() == 0)		//Yes
			_exit = true;	
	}
	else
	{
		PagesManager* pagesMgr = PagesManager::GetInstance();

		if(_playBtn)				_playBtn->Update();
		if(_highScoresBtn)			_highScoresBtn->Update();
		if(_submitDetailsBtn)		_submitDetailsBtn->Update();
		if(_reviewBtn)				_reviewBtn->Update();
		if(_shareOnGPlusBtn)		_shareOnGPlusBtn->Update();
		if(_shareOnFacebookBtn)		_shareOnFacebookBtn->Update();
		if(_moreGamesBtn)			_moreGamesBtn->Update();
		if(_exitBtn)				_exitBtn->Update();

		if(_playBtn && _playBtn->IsClicked())
		{
			pagesMgr->SetCurrPage(PagesManager::MODE_SELECTOR);
		}
		if(_highScoresBtn && _highScoresBtn->IsClicked())
		{
			pagesMgr->SetCurrPage(PagesManager::MODE_SELECTOR_FOR_LB);
		}
		else if(_moreGamesBtn && _moreGamesBtn->IsClicked())
		{
			pagesMgr->SetCurrPage(PagesManager::MORE_GAMES);
		}
		else if(Input::IsBackPressed())
		{
			_msgBox->SetActive(true);
		}
	}
}

bool MainMenu::IsLeaderBoardBtnClicked()
{
	return (_leaderBoardBtn) ? _leaderBoardBtn->IsClicked() : false;
}

bool MainMenu::IsReviewBtnClicked()
{
	return (_reviewBtn) ? _reviewBtn->IsClicked() : false;
}

bool MainMenu::IsShareOnGPlusBtnClicked()
{
	return (_shareOnGPlusBtn) ? _shareOnGPlusBtn->IsClicked() : false;
}

bool MainMenu::IsShareOnFacebookBtnClicked()
{
	return (_shareOnFacebookBtn) ? _shareOnFacebookBtn->IsClicked() : false;
}

bool MainMenu::IsSubmitDetailsBtnClicked()
{
	return (_submitDetailsBtn) ? _submitDetailsBtn->IsClicked() : false;
}

bool MainMenu::IsExitClicked()
{
	return (((_exitBtn) ? _exitBtn->IsClicked() : false) || _exit);
}

void MainMenu::Draw()
{
	ColorTheme::Draw();

	if(_playBtn)				_playBtn->Draw();
	if(_highScoresBtn)			_highScoresBtn->Draw();
	if(_submitDetailsBtn)		_submitDetailsBtn->Draw();
	if(_reviewBtn)				_reviewBtn->Draw();
	if(_moreGamesBtn)			_moreGamesBtn->Draw();
	if(_shareOnGPlusBtn)		_shareOnGPlusBtn->Draw();
	if(_shareOnFacebookBtn)		_shareOnFacebookBtn->Draw();
	if(_exitBtn)				_exitBtn->Draw();

	if(_msgBox && _msgBox->IsActive())
	{
		_msgBox->Draw();
	}
}

MainMenu::~MainMenu()
{
	if(_playBtn)
	{
		delete _playBtn;
		_playBtn = NULL;
	}

	if(_highScoresBtn)
	{
		delete _highScoresBtn;
		_highScoresBtn = NULL;
	}

	if(_submitDetailsBtn)
	{
		delete _submitDetailsBtn;
		_submitDetailsBtn = NULL;
	}

	if(_reviewBtn)
	{
		delete _reviewBtn;
		_reviewBtn = NULL;
	}

	if(_shareOnGPlusBtn)
	{
		delete _shareOnGPlusBtn;
		_shareOnGPlusBtn = NULL;
	}

	if(_shareOnFacebookBtn)
	{
		delete _shareOnFacebookBtn;
		_shareOnFacebookBtn = NULL;
	}

	if(_moreGamesBtn)
	{
		delete _moreGamesBtn;
		_moreGamesBtn = NULL;
	}

	if(_exitBtn)
	{
		delete _exitBtn;
		_exitBtn = NULL;
	}

	if(_msgBox)
	{
		delete _msgBox;
		_msgBox = NULL;
	}
}
