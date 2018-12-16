#include "Input.h"
#include "Platform/Platform.h"
#include "CommonLib/UIFont.h"

#include "CreditsPage.h"
#include "PagesManager.h"

CreditsPage::CreditsPage()
{
	_bg = NULL;
	_backBtn = NULL;

	_bg =new Sprite("data/credits.png",0,0,480,320);

	_backBtn = new Button("data/mainMenu.png","data/mainMenu.png", 10,320-44,33,34);
	_backBtn->_normalStateImg->SetUVBoundsInPixels(462,331,33,34);
	_backBtn->_onTouchImg->SetUVBoundsInPixels(462,369,33,34);
}

void CreditsPage::Update()
{
	if(_backBtn)
		_backBtn->Update();

	if(_backBtn && _backBtn->IsClicked())
	{
		PagesManager::GetInstance()->SetCurrPage(PagesManager::OPTIONS);
	}
}

void CreditsPage::Draw()
{
	if(_bg)
		_bg->Draw();
	
	if(_backBtn)
		_backBtn->Draw();
}

CreditsPage::~CreditsPage()
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
}

