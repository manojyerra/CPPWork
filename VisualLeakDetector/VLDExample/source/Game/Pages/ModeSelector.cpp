#include "ModeSelector.h"
#include "SaveManager.h"
#include "ModuleManager.h"
#include "PagesManager.h"
#include "GameInfo.h"
#include "Input.h"
#include "Platform.h"
#include "RectPrim.h"
#include "ColorTheme.h"

ModeSelector::ModeSelector()
{
	GameInfo* gameInfo = GameInfo::GetInstance();

	int sw = gameInfo->CodedW();

	_homeBtn = new ButtonNew("Back",0,0,218*0.625,97*0.525,ButtonNew::COLOR_EMPTY);

	int y = 100;
	int w = 200*1.8;
	int h = 41*1.8;
	int gap = 45;

	_playBtn3 = NULL;
	_playBtn4 = NULL;
	_playBtn5 = NULL;

	int btnNum = 0;

	int colorID = ColorTheme::GetButtonColorID();

	_playBtn3 = new ButtonNew("3x3", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;
	_playBtn4 = new ButtonNew("4x4", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;
	_playBtn5 = new ButtonNew("5x5", (sw-w)/2.0f, y+btnNum*(h+gap), w, h, colorID);	btnNum++;
}

void ModeSelector::Update()
{
	PagesManager* pagesMgr = PagesManager::GetInstance();

	if(_playBtn3)				_playBtn3->Update();
	if(_playBtn4)				_playBtn4->Update();
	if(_playBtn5)				_playBtn5->Update();
	if(_homeBtn)				_homeBtn->Update();

	if(_playBtn3 && _playBtn3->IsClicked())
	{
		SaveManager::GetInstance()->SetGameID(SaveManager::NUM_3x3);
		LevelSelector* levelSelector = (LevelSelector*)pagesMgr->GetPage(PagesManager::LEVEL_SELECTOR);
		levelSelector->Reset();
		pagesMgr->SetCurrPage(PagesManager::LEVEL_SELECTOR);
	}
	else if(_playBtn4 && _playBtn4->IsClicked())
	{
		SaveManager::GetInstance()->SetGameID(SaveManager::NUM_4x4);
		LevelSelector* levelSelector = (LevelSelector*)pagesMgr->GetPage(PagesManager::LEVEL_SELECTOR);
		levelSelector->Reset();
		pagesMgr->SetCurrPage(PagesManager::LEVEL_SELECTOR);
	}
	else if(_playBtn5 && _playBtn5->IsClicked())
	{
		SaveManager::GetInstance()->SetGameID(SaveManager::NUM_5x5);
		LevelSelector* levelSelector = (LevelSelector*)pagesMgr->GetPage(PagesManager::LEVEL_SELECTOR);
		levelSelector->Reset();
		pagesMgr->SetCurrPage(PagesManager::LEVEL_SELECTOR);
	}
	else if(_homeBtn->IsClicked() || Input::IsBackPressed())
	{
		PagesManager::GetInstance()->SetCurrPage(PagesManager::MAINMENU);
		ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);
	}
}

void ModeSelector::Draw()
{
	ColorTheme::Draw();

	if(_playBtn3)				_playBtn3->Draw();
	if(_playBtn4)				_playBtn4->Draw();
	if(_playBtn5)				_playBtn5->Draw();
	if(_homeBtn)				_homeBtn->Draw();
}

ModeSelector::~ModeSelector()
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
}
