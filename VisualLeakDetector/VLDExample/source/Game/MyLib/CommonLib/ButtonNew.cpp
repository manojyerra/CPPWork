#include "ButtonNew.h"
#include "Input.h"
#include "UIFont.h"
#include "AddData.h"

ButtonNew::ButtonNew(string text, float x, float y, float w, float h, int colorID)
{
	_text = text;
	
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_isEnable = true;
	SetColorID(colorID);

	_isClicked = false;
	_fontSizePercent = 0.60;
	_addBump = true;

	_borderTex = TextureManager::GetInstance()->CreateTexture("border32.png");
}

void ButtonNew::SetColorID(int colorID)
{
	_colorID = colorID;

	if(_colorID == COLOR1)
	{
		int t1[4] = {127, 49, 213, 255};
		int t2[4] = {255, 0, 255, 255};

		//int t1[4] = {142, 110, 144, 255};
		//int t2[4] = {142, 110, 144, 255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	else if(_colorID == COLOR2)
	{
		int t1[4] = {255,0,255,255};
		int t2[4] = {100,100,255,255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	else if(_colorID == COLOR3)
	{
		int t1[4] = {100,100,255,255};
		int t2[4] = {255,0,255,255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	else if(_colorID == COLOR4)
	{
		int t1[4] = {230,100,230,255};
		int t2[4] = {200,0,200,255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	else if(_colorID == COLOR5)
	{
		int t1[4] = {90,160,90,255};
		int t2[4] = {50,245,50,255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	else if(_colorID == COLOR_EMPTY)
	{
		for(int i=0;i<4;i++)
		{
			c1[i] = 0;
			c2[i] = 0;
		}
	}
	/*
	else if(_colorID == COLOR_DISABLE)
	{
		int t1[4] = {120,120,120,255};
		int t2[4] = {150,150,150,255};

		for(int i=0;i<4;i++)
		{
			c1[i] = t1[i];
			c2[i] = t2[i];
		}
	}
	*/
}

string ButtonNew::GetName()
{
	return _text;
}

void ButtonNew::SetName(string text)
{
	_text = text;
}

void ButtonNew::SetColor(int r, int g, int b, int a)
{
	SetTopColor(r,g,b,a);
	SetBottomColor(r,g,b,a);
}

void ButtonNew::SetTopColor(int r, int g, int b, int a)
{
	c1[0] = r;
	c1[1] = g;
	c1[2] = b;
	c1[3] = a;
}

void ButtonNew::SetBottomColor(int r, int g, int b, int a)
{
	c2[0] = r;
	c2[1] = g;
	c2[2] = b;
	c2[3] = a;
}

void ButtonNew::SetFontSizeInPercent(float fontSizePercent)
{
	_fontSizePercent = fontSizePercent;
}

void ButtonNew::SetAddBump(bool addBump)
{
	_addBump = addBump;
}

void ButtonNew::Update()
{
	_isClicked = false;

	float x = Input::MouseX;
	float y = Input::MouseY;

	if( Input::IsMouseReleased() && (x >= _x && x <= _x+_w && y >= _y && y <= _y+_h) )
	{
		_isClicked = true;
	}
}

bool ButtonNew::Contains(float x, float y)
{
	return (x >= _x && x <= _x+_w && y >= _y && y <= _y+_h);
}

bool ButtonNew::IsClicked()
{
	return _isClicked;	
}

void ButtonNew::SetEnable(bool enable)
{
	_isEnable = enable;
}

bool ButtonNew::IsEnabled()
{
	return _isEnable;
}

void ButtonNew::Draw()
{
	float d = 4;
	
	if(_isEnable)
		DrawRect(_x+d,_y+d,_w-2*d,_h-2*d,  c1[0], c1[1], c1[2], c1[3],  c2[0], c2[1], c2[2], c2[3]);
	else
		DrawRect(_x+d,_y+d,_w-2*d,_h-2*d,  120,120,120,255,  150,150,150,255);

	UIFont::GetInstance()->SetColor(255,255,255,255);
	UIFont::GetInstance()->Begin(1);
	UIFont::GetInstance()->DrawFromCenter(_text, _x+_w/2, _y+_h/2, _h*_fontSizePercent, -1);
	UIFont::GetInstance()->End();

	DrawRoundedBorder(_x,_y,_w,_h);
}

void ButtonNew::SetBounds(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

void ButtonNew::SetX(float x) { SetPos(x, _y); }
void ButtonNew::SetY(float y) { SetPos(_x, y); }

void ButtonNew::SetPos(float x, float y)
{
	_x = x;
	_y = y;
}

float ButtonNew::GetX() { return _x; }
float ButtonNew::GetY() { return _y; }
float ButtonNew::GetWidth() { return _w; }
float ButtonNew::GetHeight() { return _h; }

void ButtonNew::DrawRect(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2)
{
	AddData addData(32,true,false,false);

	addData.glBegin(GL_TRIANGLE_STRIP);

	addData.glColor4ub(r1,g1,b1,a1);
	addData.glVertex3f(x,y,0);
	addData.glVertex3f(x+w,y,0);

	addData.glColor4ub(r2,g2,b2,a2);
	addData.glVertex3f(x,y+h,0);
	addData.glVertex3f(x+w,y+h,0);

	addData.glEnd();
}

void ButtonNew::DrawRoundedBorder(int x, int y, int w, int h)
{
	int imgW = 32;
	int imgH = 32;
	
	int a = 12;
	float b = 4;

	DrawRect(x+a,	y,			w-a*2,	b,		255,255,255,255, 255,255,255,255);
	if(_addBump)
		DrawRect(x+b,	y+b,		w-b*2,	b*2,	255,255,255,200, 255,255,255,64);

	DrawRect(x+a,	y+h-b,		w-a*2,	b,		255,255,255,255, 255,255,255,255);
	if(_addBump)
		DrawRect(x+b,	y+h-2*b,	w-b*2,	b,	255,255,255,64, 255,255,255,200);
	
	DrawRect(x,		y+a,	b,		h-a*2,	255,255,255,255, 255,255,255,255);
	DrawRect(x+w-b,	y+a,	b,		h-a*2,	255,255,255,255, 255,255,255,255);

	DrawRoundedRect(x,		y,			a,		a,		0,		0,		a,a);
	DrawRoundedRect(x+w-a,	y,			a,		a,		imgW-a,	0,		a,a);
	DrawRoundedRect(x,		y+h-a,		a,		a,		0,		imgW-a,	a,a);
	DrawRoundedRect(x+w-a,	y+h-a,		a,		a,		imgW-a,	imgW-a,	a,a);
}

void ButtonNew::DrawRoundedRect(int x, int y, int w, int h, float u, float v, float cw, float ch)
{
	GLfloat ver[12];
	GLfloat uvs[12];

	ver[0] = x;		ver[1] = y;
	ver[2] = x+w;	ver[3] = y;
	ver[4] = x;		ver[5] = y+h;
	ver[6] = x+w;	ver[7] = y;
	ver[8] = x;		ver[9] = y+h;
	ver[10] = x+w;	ver[11] = y+h;

	u /= _borderTex->width;
	v /= _borderTex->height;
	cw /= _borderTex->width;
	ch /= _borderTex->height;

	uvs[0] = u;			uvs[1] = v;
	uvs[2] = u+cw;		uvs[3] = v;
	uvs[4] = u;			uvs[5] = v+ch;
	uvs[6] = u+cw;		uvs[7] = v;
	uvs[8] = u;			uvs[9] = v+ch;
	uvs[10] = u+cw;		uvs[11] = v+ch;

	glColor4f(1,1,1,1);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, _borderTex->textureID);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glTexCoordPointer (2, GL_FLOAT, 0, uvs);

	glDrawArrays(GL_TRIANGLES,0,6);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

ButtonNew::~ButtonNew()
{
	TextureManager::GetInstance()->DeleteTexture(_borderTex);
	_borderTex = NULL;
}