#include "CommonLib/Input.h"
#include "Platform/Platform.h"
#include "CommonLib/UIFont.h"
//#include "Sound/SoundManager.h"

#include "Options.h"
#include "PagesManager.h"
#include "../SaveManager/SaveManager.h"

Options::Options()
{
	float drawW = 480; //Platform::GetOrthoWidth();
	float drawH = 320; ////Platform::GetOrthoHeight();
	float cropW = 480.0f;
	float cropH = 320.0f;

	_bg = new Sprite("data/mainMenu.png",0,0,drawW,drawH, 0,0,cropW,cropH);

	_backBtn = new Button("data/mainMenu.png","data/mainMenu.png", 10,320-44,33,34);
	_backBtn->_normalStateImg->SetUVBoundsInPixels(462,331,33,34);
	_backBtn->_onTouchImg->SetUVBoundsInPixels(462,369,33,34);

	//_creditsBtn = new Button("Credits",70,320-50,100,25,0xff0000ff);

	_sfxImg = new Sprite("data/mainMenu.png",10,55,75,78,297,331,75,78);
	_bgmImg = new Sprite("data/mainMenu.png",10,145,75,78,376,330,75,78);

	_sfxBarImg = new Sprite("data/slider.png",90,75,280,24);
	_musicBarImg = new Sprite("data/slider.png",90,165,280,24);

	_sfxPointerImg =new Sprite("data/pointer.png",90,70,32,32);
	_musicPointerImg =new Sprite("data/pointer.png",90,160,32,32);

	float totalDist = _sfxBarImg->GetWidth() - _sfxPointerImg->GetWidth();
	//_sfxPointerImg->SetX(_sfxPointerImg->GetX()+totalDist*SoundManager::GetInstance()->GetAllSFXVolume());

	totalDist = _musicBarImg->GetWidth() - _musicPointerImg->GetWidth();
	//_musicPointerImg->SetX(_musicPointerImg->GetX()+totalDist*SoundManager::GetInstance()->GetBGMVolume());

	_sfxActive = false;
	_bgmActive = false;
}

void Options::Update()
{
	if(_backBtn)
		_backBtn->Update();
	//if(_creditsBtn)
	//	_creditsBtn->Update();


	if(_backBtn->IsClicked())
	{
		PagesManager::GetInstance()->SetCurrPage(PagesManager::MAINMENU);
        SaveManager::GetInstance()->SaveGame();
        
	}
	//else if(_creditsBtn->IsClicked())
	//{
	//	PagesManager::GetInstance()->SetCurrPage(PagesManager::CREDITS);
	//}
	else if(Input::IsMousePressed())
	{
		if(_sfxActive)
		{
			UpdateSFXBar();
		}
		else if(_bgmActive)
		{
			UpdateBGMBar();
		}
		else
		{
			UpdateSFXBar();
			UpdateBGMBar();
		}
	}
	if(Input::IsMouseReleased())
	{
		_sfxActive = false;
		_bgmActive = false;
	}
}

void Options::UpdateSFXBar()
{
	if(_sfxPointerImg->Contains( Input::MouseX, Input::MouseY, 0, 35) || _sfxActive)
	{
		_sfxActive = true;
		_bgmActive = false;

		_sfxPointerImg->SetX( Input::MouseX - _sfxPointerImg->GetWidth()/2);

		if(_sfxPointerImg->GetX()+_sfxPointerImg->GetWidth() > _sfxBarImg->GetX()+_sfxBarImg->GetWidth())
		{
			_sfxPointerImg->SetX( _sfxBarImg->GetX()+_sfxBarImg->GetWidth() - _sfxPointerImg->GetWidth() );
		}
		else if(_sfxPointerImg->GetX() < _sfxBarImg->GetX())
		{
			_sfxPointerImg->SetX( _sfxBarImg->GetX());
		}

		float totalDist = _sfxBarImg->GetWidth() - _sfxPointerImg->GetWidth();
		float currDist = _sfxPointerImg->GetX() - _sfxBarImg->GetX();

		//SoundManager::GetInstance()->SetAllSFXVolume( currDist / totalDist);
		//SoundManager::GetInstance()->SetSFXMute(false);
	}
}

void Options::UpdateBGMBar()
{
	if(_musicPointerImg->Contains( Input::MouseX, Input::MouseY, 0, 35) || _bgmActive)
	{
		_bgmActive = true;
		_sfxActive = false;

		_musicPointerImg->SetX( Input::MouseX - _musicPointerImg->GetWidth()/2);

		if(_musicPointerImg->GetX()+_musicPointerImg->GetWidth() > _musicBarImg->GetX()+_musicBarImg->GetWidth())
		{
			_musicPointerImg->SetX( _musicBarImg->GetX()+_musicBarImg->GetWidth() - _musicPointerImg->GetWidth() );
		}
		else if(_musicPointerImg->GetX() < _musicBarImg->GetX())
		{
			_musicPointerImg->SetX( _musicBarImg->GetX());
		}

		float totalDist = _musicBarImg->GetWidth() - _musicPointerImg->GetWidth();
		float currDist = _musicPointerImg->GetX() - _musicBarImg->GetX();

		//SoundManager::GetInstance()->SetBGMVolume( currDist / totalDist);
		//SoundManager::GetInstance()->SetBGMMute(false);
	}
}

void Options::Draw()
{
	//_bg->Draw();
	_backBtn->Draw();
	//_creditsBtn->Draw();

	_sfxImg->Draw();
	_bgmImg->Draw();
	_sfxBarImg->Draw();
	_musicBarImg->Draw();
	_sfxPointerImg->Draw();
	_musicPointerImg->Draw();
}

Options::~Options()
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
	//if(_creditsBtn)
	//{
	//	delete _creditsBtn;
	//	_creditsBtn = NULL;
	//}
	if(_sfxImg)
	{
		delete _sfxImg;
		_sfxImg = NULL;
	}
	if(_bgmImg)
	{
		delete _bgmImg;
		_bgmImg = NULL;
	}
	if(_sfxBarImg)
	{
		delete _sfxBarImg;
		_sfxBarImg = NULL;
	}
	if(_musicBarImg)
	{
		delete _musicBarImg;
		_musicBarImg = NULL;
	}
	if(_sfxPointerImg)
	{
		delete _sfxPointerImg;
		_sfxPointerImg = NULL;
	}
	if(_musicPointerImg)
	{
		delete _musicPointerImg;
		_musicPointerImg = NULL;
	}
}
