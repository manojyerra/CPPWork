#include "CommonLib/Input.h"
#include "Platform/Platform.h"
#include "UIFont.h"

#include "AboutPage.h"
#include "PagesManager.h"
#include "GameInfo.h"

MoreGames::MoreGames()
{
	int sw = GameInfo::GetInstance()->CodedW();
	int sh = GameInfo::GetInstance()->CodedH();

	_bg = new RectPrim(0,0,sw,sh, 0, 0x00000000);
	_bg->SetColor(90,90,140,255);

	_backBtn = new Button("pages/backNormal.png","pages/backOnTouch.png",0,0,218*0.625,97*0.625);
	_backBtn->_normalStateImg->SetUVBoundsInPixels(0,0,218,97);
	_backBtn->_onTouchImg->SetUVBoundsInPixels(0,0,218,97);

	_game1Btn = new Button("pages/moregames/game1.png","pages/moregames/game1.png",(sw-200)/2.0f,300,200,200);
}

void MoreGames::Update()
{
	if(_backBtn)
		_backBtn->Update();

	if(_game1Btn)
		_game1Btn->Update();

	if(_backBtn && _backBtn->IsClicked())
		PagesManager::GetInstance()->SetCurrPage(PagesManager::MAINMENU);
}

bool MoreGames::IsGame1Clicked()
{
	return _game1Btn->IsClicked();
}

void MoreGames::Draw()
{
	if(_bg)
		_bg->Draw();

	if(_game1Btn)
		_game1Btn->Draw();

	if(_backBtn)
		_backBtn->Draw();
}

MoreGames::~MoreGames()
{
	if(_bg)
	{
		delete _bg;
		_bg = NULL;
	}

	if(_backBtn)
	{
		delete _backBtn;
		_backBtn = NULL;
	}

	if(_game1Btn)
	{
		delete _game1Btn;
		_game1Btn = NULL;
	}
}

