#include "Button.h"
#include "Input.h"
#include "UIFont.h"

Button::Button(string normalImgPath,string onTouchImagPath,float x,float y, float w,float h)
{
	_isClicked = false;
	
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_normalStateImg = new Sprite(normalImgPath.c_str(),_x,_y,_w,_h);
	_onTouchImg = new Sprite(onTouchImagPath.c_str(),_x,_y,_w,_h);
	_disableImg = NULL;

	_displayImg = _normalStateImg;

	_rectPrim = NULL;
	_color = 0xffffffff;
	_state = NORMAL;
}

Button::Button(string normalImgPath,string onTouchImagPath, string disableImgPath, float x,float y, float w,float h)
{
	_isClicked = false;
	
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_normalStateImg = new Sprite(normalImgPath.c_str(),_x,_y,_w,_h);
	_onTouchImg = new Sprite(onTouchImagPath.c_str(),_x,_y,_w,_h);
	_disableImg = new Sprite(disableImgPath.c_str(),_x,_y,_w,_h);

	_displayImg = _normalStateImg;

	_rectPrim = NULL;
	_color = 0xffffffff;	
	_state = NORMAL;
}

void Button::SetEanble(bool enable)
{
	if(enable == false)
		_displayImg = _disableImg;
	else
		_displayImg = _normalStateImg;
}

bool Button::IsEanbled()
{
	return (_displayImg != _disableImg);
}

Sprite* Button::GetSprite()
{
	return _displayImg;
}

int Button::GetState()
{
	return _state;
}

void Button::SetRotation(float angle)
{
	if(_normalStateImg)
		_normalStateImg->SetRotation(angle);
	if(_onTouchImg)
		_onTouchImg->SetRotation(angle);
	if(_disableImg)
		_disableImg->SetRotation(angle);
}

void Button::SetRotation(float angle, int centerX, int centerY)
{
	if(_normalStateImg)
		_normalStateImg->SetRotation( angle, centerX, centerY );
	if(_onTouchImg)
		_onTouchImg->SetRotation( angle, centerX, centerY );
	if(_disableImg)
		_disableImg->SetRotation( angle, centerX, centerY );
}

void Button::SetBackgroundColor(unsigned int color)
{
	_color = color;
	_rectPrim->SetColor(_color);
}

void Button::Update()
{
	_isClicked = false;

	if(Input::IsMouseClicked() && _displayImg->Contains((float)Input::MouseX, (float)Input::MouseY))
	{
		_validTouch = true;
	}

	if(Input::IsMousePressed() && _displayImg->Contains((float)Input::MouseX, (float)Input::MouseY))
	{
		if(IsEanbled())
		{
			_displayImg = _onTouchImg;
			_state = ON_TOUCH;
		}
	}
	else
	{
		if(_validTouch && Input::IsMouseReleased() && _displayImg->Contains((float)Input::MouseX, (float)Input::MouseY))
		{
			_validTouch = false;
			_isClicked = true;
		}

		if(IsEanbled())
		{
			_displayImg = _normalStateImg;
			_state = NORMAL;
		}
	}
}

bool Button::IsClicked()
{
	return _isClicked;	
}

void Button::Draw()
{
	_displayImg->Draw();
}

void Button::SetX(float x) { SetPos(x, _y); }
void Button::SetY(float y) { SetPos(_x, y); }

void Button::SetPos(float x, float y)
{
	_x = x;
	_y = y;

	if(_normalStateImg)
		_normalStateImg->SetPos(_x, _y);
	if(_onTouchImg)
		_onTouchImg->SetPos(_x, _y);
	if(_disableImg)
		_disableImg->SetPos(_x, _y);
}

float Button::GetX() { return _x; }
float Button::GetY() { return _y; }
float Button::GetWidth() { return _w; }
float Button::GetHeight() { return _h; }

Button::~Button()
{
	if(_normalStateImg)
	{
		delete _normalStateImg;
		_normalStateImg = NULL;
	}

	if(_onTouchImg)
	{
		delete _onTouchImg;
		_onTouchImg = NULL;
	}

	if(_disableImg)
	{
		delete _disableImg;
		_disableImg = NULL;
	}

	if(_rectPrim)
	{
		delete _rectPrim;
		_rectPrim = NULL;
	}
}
