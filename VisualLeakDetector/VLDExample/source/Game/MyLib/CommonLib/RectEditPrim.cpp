#include "RectEditPrim.h"
#include "AddData.h"
#include "Input.h"
#include "Includes.h"

RectEditPrim::RectEditPrim(float x, float y, float w, float h)
{
	_mainRect = new RectPrim(x, y, w, h, 0, 0x0000ffff);

	for(int i=0;i<4;i++)
	{
		RectPrim* rectPrim = new RectPrim(0, 0, 0, 0, 0, 0x000000ff);
		_rectPrimsVec.push_back(rectPrim);
	}

	_r = 0;
	_g = 255;
	_b = 0;
	_a = 255;
	_active = false;

	ResetRectBounds();
	_activeRect = NULL;
}


bool RectEditPrim::Update()
{
	if(!_active)
		return false;

	if(Input::IsMouseClicked())
	{
		_activeRect = GetEditRect(Input::MouseX, Input::MouseY);
		if(_activeRect)
			return true;
	}
	else if(Input::IsMousePressed() && _activeRect)
	{
		float dx = Input::MouseX - Input::PrevMouseX;
		float dy = Input::MouseY - Input::PrevMouseY;

		if(_activeRect == _rectPrimsVec[0])
		{
			SetSize(GetWidth()-dx, GetHeight());
			SetPos(GetX()+dx, GetY());
		}
		else if(_activeRect == _rectPrimsVec[1])
		{
			SetSize(GetWidth()+dx, GetHeight());
		}
		else if(_activeRect == _rectPrimsVec[2])
		{
			SetSize(GetWidth(), GetHeight()-dy);
			SetPos(GetX(), GetY()+dy);
		}
		else if(_activeRect == _rectPrimsVec[3])
		{
			SetSize(GetWidth(), GetHeight()+dy);
		}

		return true;
	}
	else if(Input::IsMouseReleased())
	{
		_activeRect = NULL;
	}

	return false;
}

RectPrim* RectEditPrim::GetEditRect(float x, float y)
{
	for(int i=0;i<(int)_rectPrimsVec.size();i++)
		if( _rectPrimsVec[i]->Contains((float)Input::MouseX, (float)Input::MouseY))
			return _rectPrimsVec[i];

	return NULL;
}


void RectEditPrim::SetColor(int r, int g, int b, int a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

float RectEditPrim::GetX()
{
	return _mainRect->GetX();
}

float RectEditPrim::GetY()
{
	return _mainRect->GetY();
}

float RectEditPrim::GetWidth()
{
	return _mainRect->GetWidth();
}

float RectEditPrim::GetHeight()
{
	return _mainRect->GetHeight();
}

void RectEditPrim::SetPos(float x, float y)
{
	_mainRect->SetPos(x,y);
	ResetRectBounds();
}

void RectEditPrim::SetSize(float w, float h)
{
	_mainRect->SetSize(w,h);
	ResetRectBounds();
}

void RectEditPrim::SetBounds(float x, float y, float w, float h)
{
	_mainRect->SetBounds(x,y,w,h);
	ResetRectBounds();
}

void RectEditPrim::	ResetRectBounds()
{
	float w = 0;
	float h = 0;

	float horRectW = _mainRect->GetWidth() * 0.2;
	float horRectH = _mainRect->GetHeight() * 0.6;

	w = horRectW;
	h = horRectH;

	if(w < 10)	w = 10;
	if(w > 20)	w = 20;

	if(h < 10)	h = 10;

	float mx = _mainRect->GetX();
	float my = _mainRect->GetY();
	float mw = _mainRect->GetWidth();
	float mh = _mainRect->GetHeight();

	_rectPrimsVec[0]->SetBounds( mx-w/2,	my+(mh-h)/2.0f, w, h);
	_rectPrimsVec[1]->SetBounds( mx+mw-w/2, my+(mh-h)/2.0f, w, h);

	//vertical rects

	float verRectW = _mainRect->GetWidth() * 0.6;
	float verRectH = _mainRect->GetHeight() * 0.2;

	w = verRectW;
	h = verRectH;

	if(w < 10)	w = 10;

	if(h < 10)	h = 10;
	if(h > 20)	h = 20;

	_rectPrimsVec[2]->SetBounds( mx+(mw-w)/2.0f, my-h/2,	w, h);
	_rectPrimsVec[3]->SetBounds( mx+(mw-w)/2.0f, my+mh-h/2, w, h);
}

void RectEditPrim::SetActive(bool active)
{
	_active = active;
}

bool RectEditPrim::IsActive()
{
	return _active;
}

void RectEditPrim::Draw()
{
	_mainRect->Draw();

	if(_active)
	{
		for(int i=0;i<(int)_rectPrimsVec.size();i++)
			_rectPrimsVec[i]->Draw();
	}
}

RectEditPrim::~RectEditPrim()
{
	for(int i=0;i<(int)_rectPrimsVec.size();i++)
	{
		if(_rectPrimsVec[i])
		{
			delete _rectPrimsVec[i];
			_rectPrimsVec[i] = NULL;
		}
	}
}
