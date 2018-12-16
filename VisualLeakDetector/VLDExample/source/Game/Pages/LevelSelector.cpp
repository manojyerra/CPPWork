#include "Input.h"
#include "LevelSelector.h"
#include "PagesManager.h"
#include "ModuleManager.h"
#include "SaveManager.h"
#include "GameInfo.h"
#include "ColorTheme.h"

LevelSelector::LevelSelector()
{	
	GameInfo* gameInfo = GameInfo::GetInstance();
	int sw = gameInfo->CodedW();
	int sh = gameInfo->CodedH();

	_bg = new RectPrim(0,0,sw,sh, 0, 0x00000000);
	_bg->SetColor(90,90,140,255);

	_loadingImg = new Sprite("loading.png",(sw-256)/2,(sh-64)/2,256,64);

	_homeBtn = new ButtonNew("Back",0,0,218*0.625,97*0.525,ButtonNew::COLOR_EMPTY);

	_innerCirImg = new Sprite("pages/levelPointerBase.png",0,0,30,30);
	_ourterCirImg = new Sprite("pages/levelPointer.png",0,0,30,30);

	int rows = 4;
	int cols = 5;

	int totLevels = SaveManager::GetInstance()->GetNumTotalLevels();
	NUM_PAGES = totLevels / (rows * cols);

	if(totLevels % (rows * cols) != 0)
		NUM_PAGES++;

	for(int i=0;i<NUM_PAGES;i++)
	{
		LevelsShowScreen* levelShowScreen = new LevelsShowScreen(i+1, rows, cols);
		_levelScreensVec.push_back(levelShowScreen);
	}

	_activeLevelScreenIndex = 0;

	_startMoveRight = false;
	_startMoveLeft = false;
	_moveCount = 0;
	_moveSpeed = 80;

	_showLoading = false;
	_levelBtnNumber = 1;
}

void LevelSelector::Reset()
{
	_activeLevelScreenIndex = 0;

	_startMoveRight = false;
	_startMoveLeft = false;
	_moveCount = 0;
	_moveSpeed = 80;

	_showLoading = false;
	_levelBtnNumber = 1;

	for(int i=0;i<_levelScreensVec.size();i++)
	{
		_levelScreensVec[i]->Reset(i+1);
		_levelScreensVec[i]->Move(768*i, 0);
	}
}

void LevelSelector::Update()
{
	if(!_startMoveRight && !_startMoveLeft)
		_homeBtn->Update();

	if(_startMoveRight)
	{
		MoveAll(_moveSpeed,0);
		_moveCount += _moveSpeed;
		
		if(_moveCount >= 768)
		{
			MoveAll(768-_moveCount,0);
			_moveCount = 0;
			_startMoveRight = false;
			_activeLevelScreenIndex--;
		}
	}
	else if(_startMoveLeft)
	{
		MoveAll(-_moveSpeed,0);
		_moveCount -= _moveSpeed;

		if(_moveCount <= -768)
		{
			MoveAll(-768-_moveCount,0);
			_moveCount = 0;
			_startMoveLeft = false;
			_activeLevelScreenIndex++;
		}
	}
	else if(_homeBtn->IsClicked() || Input::IsBackPressed())
	{
		PagesManager::GetInstance()->SetCurrPage(PagesManager::MODE_SELECTOR);
		ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);
	}
	else if(Input::IsMouseReleased() && Input::GetDistBetweenClickAndRelease() > 15)
	{
		if(Input::MouseClickX > Input::MouseReleaseX)
		{
			if(_activeLevelScreenIndex+1 <= _levelScreensVec.size()-1)
				_startMoveLeft = true;
		}
		else if(Input::MouseClickX < Input::MouseReleaseX)
		{
			if(_activeLevelScreenIndex-1 >= 0)
				_startMoveRight = true;
		}
	}
	else
	{
		_levelScreensVec[_activeLevelScreenIndex]->Update();
		LevelBtn* levelBtn = _levelScreensVec[_activeLevelScreenIndex]->GetButton_OnClick();
		
		if(levelBtn)
		{
			_showLoading = true;
			_levelBtnNumber = levelBtn->GetNumber();
		}
	}
}

void LevelSelector::MoveAll(float x, float y)
{
	for(int i=0; i<_levelScreensVec.size(); i++)
		_levelScreensVec[i]->Move(x, y);
}

void LevelSelector::Draw()
{
	ColorTheme::Draw();

	_homeBtn->Draw();

	if(_startMoveLeft)
	{
		_levelScreensVec[_activeLevelScreenIndex]->Draw();
		_levelScreensVec[_activeLevelScreenIndex+1]->Draw();
	}
	else if(_startMoveRight)
	{
		_levelScreensVec[_activeLevelScreenIndex]->Draw();
		_levelScreensVec[_activeLevelScreenIndex-1]->Draw();
	}
	else
	{
		_levelScreensVec[_activeLevelScreenIndex]->Draw();
	}

	DrawPageIndicators();

	if(_showLoading)
	{
		SaveManager::GetInstance()->SetCurrLevel(_levelBtnNumber);
		SaveManager::GetInstance()->SaveGame();
		ModuleManager::GetInstance()->SetModule(ModuleManager::GAME);
		_showLoading = false;

		_loadingImg->Draw();
	}
}

void LevelSelector::DrawPageIndicators()
{
	GameInfo* gameInfo = GameInfo::GetInstance();
	int sw = gameInfo->CodedW();
	int sh = gameInfo->CodedH();

	float numPages = (float)_levelScreensVec.size();

	float gap = 12;
	float width = _innerCirImg->GetWidth();
	float initX = (sw - (numPages*width + (numPages-1)*gap))/2.0f;
	float initY = sh*0.93;

	float x = initX;
	for(int i=0; i<_levelScreensVec.size(); i++)
	{
		_innerCirImg->SetPos(x, initY);
		x += width+gap;
		_innerCirImg->Draw();
	}

	_ourterCirImg->SetPos(initX + _activeLevelScreenIndex * (width+gap), initY);
	_ourterCirImg->Draw();
}

LevelSelector::~LevelSelector()
{	
	if(_homeBtn)
	{
		delete _homeBtn;
		_homeBtn = NULL;
	}

	for(int i=0; i<_levelScreensVec.size(); i++)
	{
		if(_levelScreensVec[i])
		{
			delete _levelScreensVec[i];
			_levelScreensVec[i] = NULL;
		}
	}
	_levelScreensVec.clear();

	if(_innerCirImg)
	{
		delete _innerCirImg;
		_innerCirImg = NULL;
	}

	if(_ourterCirImg)
	{
		delete _ourterCirImg;
		_ourterCirImg = NULL;
	}

	if(_loadingImg)
	{
		delete _loadingImg;
		_loadingImg = NULL;
	}

	if(_bg)
	{
		delete _bg;
		_bg = NULL;
	}
}
