#include "ModeSelectorForLB.h"
#include "SaveManager.h"
#include "ModuleManager.h"
#include "PagesManager.h"
#include "GameInfo.h"
#include "Input.h"
#include "Platform.h"
#include "RectPrim.h"
#include "ColorTheme.h"

ModeSelectorForLB::ModeSelectorForLB()
{
	GameInfo* gameInfo = GameInfo::GetInstance();

	int sw = gameInfo->CodedW();

	_homeBtn = new ButtonNew("Back",0,0,218*0.625,97*0.525,ButtonNew::COLOR_EMPTY);

	int y = 100;
	int w = 230*1.8;
	int h = 41*1.8;
	int gap = 45;

	_playBtn3 = NULL;
	_playBtn4 = NULL;
	_playBtn5 = NULL;

	int btnNum = 0;

	int colorID = ColorTheme::GetButtonColorID();

	_playBtn3 = new ButtonNew("High Scores ( 3x3 )", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;
	_playBtn4 = new ButtonNew("High Scores ( 4x4 )", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;
	_playBtn5 = new ButtonNew("High Scores ( 5x5 )", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;

	_playBtn3->SetFontSizeInPercent(0.5f);
	_playBtn4->SetFontSizeInPercent(0.5f);
	_playBtn5->SetFontSizeInPercent(0.5f);

	_leaderBoard = new LeaderBoard();
}

void ModeSelectorForLB::Update()
{
	if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Update();
	}
	else
	{
		PagesManager* pagesMgr = PagesManager::GetInstance();

		if(_playBtn3)				_playBtn3->Update();
		if(_playBtn4)				_playBtn4->Update();
		if(_playBtn5)				_playBtn5->Update();
		if(_homeBtn)				_homeBtn->Update();

		if(_playBtn3 && _playBtn3->IsClicked())
		{
			SaveManager::GetInstance()->SetGameID(SaveManager::NUM_3x3);
			_leaderBoard->SetActive(true);
		}
		else if(_playBtn4 && _playBtn4->IsClicked())
		{
			SaveManager::GetInstance()->SetGameID(SaveManager::NUM_4x4);
			_leaderBoard->SetActive(true);
		}
		else if(_playBtn5 && _playBtn5->IsClicked())
		{
			SaveManager::GetInstance()->SetGameID(SaveManager::NUM_5x5);
			_leaderBoard->SetActive(true);
		}
		else if(_homeBtn->IsClicked() || Input::IsBackPressed())
		{
			PagesManager::GetInstance()->SetCurrPage(PagesManager::MAINMENU);
			ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);
		}
	}
}

void ModeSelectorForLB::Draw()
{
	if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Draw();
	}
	else
	{
		ColorTheme::Draw();

		if(_playBtn3)				_playBtn3->Draw();
		if(_playBtn4)				_playBtn4->Draw();
		if(_playBtn5)				_playBtn5->Draw();
		if(_homeBtn)				_homeBtn->Draw();
	}
}

ModeSelectorForLB::~ModeSelectorForLB()
{
	if(_playBtn3)
	{
		delete _playBtn3;
		_playBtn3 = NULL;
	}
	if(_playBtn4)
	{
		delete _playBtn4;
		_playBtn4 = NULL;
	}
	if(_playBtn5)
	{
		delete _playBtn5;
		_playBtn5 = NULL;
	}

	if(_homeBtn)
	{
		delete _homeBtn;
		_homeBtn = NULL;
	}

	if(_leaderBoard)
	{
		delete _leaderBoard;
		_leaderBoard = NULL;
	}
}
