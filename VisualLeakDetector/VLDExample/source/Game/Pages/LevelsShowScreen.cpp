#include "Input.h"
#include "Platform.h"

#include "LevelsShowScreen.h"
#include "ModuleManager.h"
#include "SaveManager.h"
#include "PagesManager.h"
#include "GameInfo.h"
#include "ColorTheme.h"

LevelsShowScreen::LevelsShowScreen(int pageNum, int rows, int cols)
{	
	_pageNum = pageNum;
	_totLevels = SaveManager::GetInstance()->GetNumTotalLevels();
	_lastUnLockLevelNum = 1;

	_rows = rows;
	_cols = cols;
	_btnW = 145;
	_btnH = 120;
	_hGap = 7;
	_vGap = 7;

	//Reset();
}

void LevelsShowScreen::Reset(int pageNum)
{
	_pageNum = pageNum;

	int numCols = _cols;
	int numRows = _rows;

	int width = _btnW;
	int height = _btnH;
	int hGap = _hGap;
	int vGap = _vGap;

	int ow = GameInfo::GetInstance()->CodedW();

	int initX = ( ow - (numCols*width + (numCols-1)*hGap) ) / 2.0f;
	int initY = 50;

	int levelNum = 1 + (_pageNum-1)*numCols*numRows;
	int counter = 0;

	for( int row=0; row<numRows; row++ )
	{
		for( int col=0; col<numCols; col++ )
		{
			if(levelNum > _totLevels)
				break;

			LevelBtn* levelBtn = NULL;

			if(counter < _levelBtnsVec.size())
			{
				levelBtn = _levelBtnsVec[counter];
				levelBtn->SetBounds(initX+col*(width+hGap), initY+row*(height+vGap), width, height);
			}
			else
			{
				int colorID = ColorTheme::GetButtonColorID();

				ButtonNew* btn = new ButtonNew("", initX+col*(width+hGap), initY+row*(height+vGap), width, height, colorID);
				_buttonsVec.push_back(btn);

				levelBtn = new LevelBtn(btn, levelNum);
				_levelBtnsVec.push_back(levelBtn);
			}

			if(levelNum > SaveManager::GetInstance()->GetLastUnlockedLevel())
				levelBtn->SetEnable(false);
			else
				levelBtn->SetEnable(true);

			levelNum++;
			counter++;
		}
	}
}

void LevelsShowScreen::SetPageNumber(int pageNum)
{
	_pageNum = pageNum;
}

void LevelsShowScreen::SetTotalLevels(int totLevels)
{
	_totLevels = totLevels;
}

void LevelsShowScreen::SetLastUnlockedLevels(int lastUnLockLevelNum)
{
	_lastUnLockLevelNum = lastUnLockLevelNum;
}

void LevelsShowScreen::SetRowAndCols(int rows, int cols)
{
	_rows = rows;
	_cols = cols;
}

void LevelsShowScreen::SetHorAndVerGap(int horGap, int verGap)
{
	_hGap = horGap;
	_vGap = verGap;
}

void LevelsShowScreen::SetBtnSize(int width, int height)
{
	_btnW = width;
	_btnH = height;
}

void LevelsShowScreen::Update()
{
	for(int i=0; i<_levelBtnsVec.size() && _totLevels; i++)
	{
		if(_levelBtnsVec[i]->GetNumber() <= SaveManager::GetInstance()->GetLastUnlockedLevel())
			_levelBtnsVec[i]->SetEnable(true);

		if(_levelBtnsVec[i]->IsEnabled())
			_levelBtnsVec[i]->Update();
	}
}

LevelBtn* LevelsShowScreen::GetButton_OnClick()
{
	for(int i=0;i<_levelBtnsVec.size();i++)
	{
		if(_levelBtnsVec[i]->IsEnabled() && _levelBtnsVec[i]->IsClicked())
			return _levelBtnsVec[i];
	}
	return NULL;
}

void LevelsShowScreen::Move(int x, int y)
{
	for(int i = 0; i < _levelBtnsVec.size(); i++)
		_levelBtnsVec[i]->Move(x,y);
}

void LevelsShowScreen::Draw()
{
	for(int i=0;i<_levelBtnsVec.size() && _totLevels;i++)
		_levelBtnsVec[i]->Draw();
}

void LevelsShowScreen::DeleteButtons()
{
	for(int i = 0; i < _levelBtnsVec.size(); i++)
	{
		if(_levelBtnsVec[i])
		{
			delete _levelBtnsVec[i];
			_levelBtnsVec[i] = NULL;
		}
	}

	for(int i = 0; i < _buttonsVec.size(); i++)
	{
		if(_buttonsVec[i])
		{
			delete _buttonsVec[i];
			_buttonsVec[i] = NULL;
		}
	}

	_levelBtnsVec.clear();
	_buttonsVec.clear();
}

LevelsShowScreen::~LevelsShowScreen()
{
	DeleteButtons();
}
