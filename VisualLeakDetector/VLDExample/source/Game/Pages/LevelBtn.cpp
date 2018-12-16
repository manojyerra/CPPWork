#include "LevelBtn.h"
#include "Input.h"
#include "SaveManager.h"
#include "UIFont.h"
#include "GameInfo.h"

LevelBtn::LevelBtn(ButtonNew* btn, int number)
{
	_btn = btn;
	_number = number;

	float w = 22;
	float h = 20;
	float initX = btn->GetX() + 33;
	float initY = btn->GetY() + btn->GetHeight() - h - 45;
	float gap = 5;

	for(int i=0;i<3;i++)
	{
		_disableStars[i] = new Sprite("numberpuzzle/stars.png", initX+i*(w+gap),initY,w,h, 32,0,32,32);
		_enableStars[i]  = new Sprite("numberpuzzle/stars.png", initX+i*(w+gap),initY,w,h, 0,0,32,32);
	}
}

void LevelBtn::Update()
{
	_btn->Update();
}

bool LevelBtn::IsClicked()
{
	return _btn->IsClicked();
}

void LevelBtn::SetEnable(bool enable)
{
	_btn->SetEnable(enable);
}

bool LevelBtn::IsEnabled()
{
	return _btn->IsEnabled();
}

void LevelBtn::SetBounds(int xx, int yy, int ww, int hh)
{
	_btn->SetBounds(xx,yy,ww,hh);

	float w = 22;
	float h = 20;
	float initX = _btn->GetX() + 33;
	float initY = _btn->GetY() + _btn->GetHeight() - h - 45;
	float gap = 5;

	for(int i=0;i<3;i++)
	{
		_disableStars[i]->SetBounds(initX+i*(w+gap),initY,w,h);
		_enableStars[i]->SetBounds(initX+i*(w+gap),initY,w,h);
	}
}

void LevelBtn::Move(int x, int y)
{
	_btn->SetX( _btn->GetX() + x );
	_btn->SetY( _btn->GetY() + y );

	for(int i=0;i<3;i++)
	{
		_disableStars[i]->SetX(_disableStars[i]->GetX()+x);
		_disableStars[i]->SetY(_disableStars[i]->GetY()+y);

		_enableStars[i]->SetX(_enableStars[i]->GetX()+x);
		_enableStars[i]->SetY(_enableStars[i]->GetY()+y);
	}
}

int LevelBtn::GetNumber()
{
	return _number;
}

void LevelBtn::Draw()
{
	_btn->Draw();

	for(int i=0;i<3;i++)
		_disableStars[i]->Draw();

	int numStars = SaveManager::GetInstance()->GetNumStars( _number );
	for(int i=0;i<numStars;i++)
		_enableStars[i]->Draw();

	char arr[16];
	sprintf(arr, "%d",_number);

	if(_number <= SaveManager::GetInstance()->GetLastUnlockedLevel())
		UIFont::GetInstance()->SetColor(255,255,255,255);
	else
		UIFont::GetInstance()->SetColor(90,90,90,150);

	UIFont::GetInstance()->Begin(1);
	UIFont::GetInstance()->DrawFromCenter(arr, _btn->GetX()+_btn->GetWidth()/2, _btn->GetY()+_btn->GetHeight()*0.30, 45, -2);
	UIFont::GetInstance()->End();

	char movesArr[16];
	
	sprintf(movesArr, "Moves %d",SaveManager::GetInstance()->GetNumMoves(_number));

	int timeInSec = SaveManager::GetInstance()->GetTime(_number);

	UIFont::GetInstance()->Begin();
	UIFont::GetInstance()->DrawFromCenter(movesArr, _btn->GetX()+_btn->GetWidth()/2, _btn->GetY()+_btn->GetHeight()*0.73, 19, -1);
	UIFont::GetInstance()->DrawFromCenter(GameInfo::GetInstance()->GetTimeStr(timeInSec, "Time ", ""), 
												_btn->GetX()+_btn->GetWidth()/2, _btn->GetY()+_btn->GetHeight()*0.88, 19, -2);
	UIFont::GetInstance()->End();
}

LevelBtn::~LevelBtn()
{
	for(int i=0;i<3;i++)
	{
		if(_disableStars[i])
		{
			delete _disableStars[i];
			_disableStars[i] = NULL;
		}

		if(_enableStars[i])
		{
			delete _enableStars[i];
			_enableStars[i] = NULL;
		}
	}
}