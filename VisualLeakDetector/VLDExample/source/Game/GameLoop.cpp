#include "GameLoop.h"
#include "Platform.h"
#include "Includes.h"
#include "PNGReadWrite.h"
#include "Input.h"
#include "ModuleManager.h"
#include "TextureManager.h"
#include "GameInfo.h"
#include "LeaderBoardData.h"
#include "SaveManager.h"
#include "UIFont.h"
#include "Flags.h"

GameLoop::GameLoop()
{
	_init = false;
	_onResume = false;
	_isMusicPlayingBeforePause = true;
	_bgmBtn = NULL;
	GameInfo::GetInstance()->SetCodedSize(1024, 600);
}

void GameLoop::Init()
{
	_gameInit = new GameInit();
	_init = true;

	//_tempSprite = new Sprite("temp.jpg", 0,0,500,500);
}

void GameLoop::onSizeChange(int surfaceW, int surfaceH)
{
	GameInfo::GetInstance()->SetSurfaceSize(surfaceW, surfaceH);
	GameInfo::GetInstance()->CalcDrawArea();
}

void GameLoop::Update(int deltaTimeInMillis)
{
	GameInfo::deltaTime = deltaTimeInMillis/1000.0f;
	Input::Update();
	ModuleManager::GetInstance()->Update();
}

int GameLoop::Draw(int deltaTimeInMillis)
{
	if(_onResume)
	{
		_onResume = false;
		TextureManager::GetInstance()->DeleteAllTextures();
		TextureManager::GetInstance()->CreateAllTextures();
	}

	if(_init == false)
	{
		Init();
		return 0;
	}

	Update(deltaTimeInMillis);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GameInfo* gameInfo = GameInfo::GetInstance();

	glViewport(gameInfo->drawX, gameInfo->drawY, gameInfo->drawW, gameInfo->drawH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, gameInfo->CodedW(), gameInfo->CodedH(), 0, -1, 1);

	ModuleManager::GetInstance()->Draw();

	//_tempSprite->Draw();

	if(GameInfo::GetInstance()->IsLeaderBoardOn() == false)
	{
		if(_bgmBtn)
			_bgmBtn->Draw();
	}

	if(ModuleManager::GetInstance()->GetModule() == ModuleManager::PAGES)
	{
		PagesManager* pages = (PagesManager*)(ModuleManager::GetInstance()->GetModuleObject(ModuleManager::PAGES));
		
		if(pages->GetCurrPageID() == PagesManager::MAINMENU)
		{
			MainMenu* mainMenu = (MainMenu*)pages->GetPage(PagesManager::MAINMENU);

			if(mainMenu->IsSubmitDetailsBtnClicked())
				return 3;
			else if(mainMenu->IsReviewBtnClicked())
				return 4;
			else if(mainMenu->IsShareOnGPlusBtnClicked())
				return 5;
			else if(mainMenu->IsExitClicked())
				return 9;
		}
	}

	if(GameInfo::GetInstance()->IsSubmitDetailsBtnClicked())
	{
		GameInfo::GetInstance()->SetSubmitClicked(false);
		return 3;
	}
	else if(GameInfo::GetInstance()->IsShareClicked())
	{
		GameInfo::GetInstance()->SetShareClicked(false);
		return 5;
	}
	else if(GameInfo::GetInstance()->IsReviewClicked())
	{
		GameInfo::GetInstance()->SetReviewClicked(false);
		return 4;
	}
	else if(GameInfo::GetInstance()->IsTimeToShowAd())
	{
		GameInfo::GetInstance()->SetTimeToShowAd(false);
		
		if(SaveManager::GetInstance()->GetTotalLevelsPlayed() >= 2)
			return 8;
	}

	return 0;
}

void GameLoop::onTouch(int x, int y, int eventID)
{
	Input::onTouch(x, y, eventID);
}

void GameLoop::onPause()
{
	//printLog("GameLoop::onPause called...");
}

void GameLoop::onResume()
{
	//printLog("GameLoop::onResume called...");
	_onResume = true;
}

void GameLoop::SetLanguageID(int languageID)
{
	GameInfo::GetInstance()->SetLanguage(languageID);
}

void GameLoop::SetBackKeyPressed()
{
	Input::SetBackKeyPressed();
}

GameLoop::~GameLoop()
{
	if(_bgmBtn)
	{
		delete _bgmBtn;
		_bgmBtn = NULL;
	}

	if(_gameInit)
	{
		delete _gameInit;
		_gameInit = NULL;
	}
}
