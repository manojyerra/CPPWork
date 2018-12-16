#include "CommonLib/Input.h"
#include "Platform/Platform.h"

#include "Logos.h"

Logos::Logos()
{
	_currLogoIndex = 0;
	_timeCount = 0;
	_shownLogos = false;
	_transSpeed = 20;

	_spriteVec.clear();
	_timeVec.clear();

	Sprite* sprite;
	for(int i=0;i<NUM_LOGOS;i++)
	{
		char filePath[256];
		sprintf(filePath, "data/Logos/Logo%d.png",(i+1));
		sprite = new Sprite(filePath,i*768,0,768+2,1024);
		//sprite->SetAlpha(255);
		_spriteVec.push_back(sprite);
		_timeVec.push_back(2.0f);
	}
}

void Logos::Update()
{
	if(!_shownLogos)
	{
		//----------------Cheat--------------------
		if(Input::IsMouseClicked())
		{
			_shownLogos = true;
		}
		else
		//---------------- upto here --------------
		{
			if((int)_spriteVec[_currLogoIndex]->GetX() != 0)
			{
				if((int)_spriteVec[_currLogoIndex]->GetX() > 0)
					Move(-_transSpeed, 0);
				if((int)_spriteVec[_currLogoIndex]->GetX() < 0)
				{
					Move(-_spriteVec[_currLogoIndex]->GetX(), 0);
				}
			}
			else
			{
				_timeCount += 1.0f/30.0f; //Platform::deltaTime;

				if( _timeCount >= _timeVec[_currLogoIndex] )
				{
					_timeCount = 0;
					_currLogoIndex++;
					if(_currLogoIndex >= _spriteVec.size())
						_shownLogos = true;
				}
			}
		}
	}
}

bool Logos::HasShownLogos()
{
	return _shownLogos;
}

void Logos::Move(float dx, float dy)
{
	for(int i=0;i<(int)_spriteVec.size();i++)
		_spriteVec[i]->SetPos(_spriteVec[i]->GetX() + dx, _spriteVec[i]->GetY() + dy);
}

void Logos::Draw()
{
	if(!_shownLogos)
	{
		for(int i=0;i<(int)_spriteVec.size();i++)
			_spriteVec[i]->Draw();
	}
}

Logos::~Logos()
{
	for(int i=0;i<(int)_spriteVec.size();i++)
	{
		if(_spriteVec[i])
		{
			delete _spriteVec[i];
			_spriteVec[i] = NULL;
		}
	}

	_spriteVec.clear();
}
