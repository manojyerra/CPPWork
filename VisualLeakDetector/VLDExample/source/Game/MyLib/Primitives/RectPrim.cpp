#include "RectPrim.h"
#include "Includes.h"
#include "math.h"
#include "AddData.h"

RectPrim::RectPrim(float x, float y, float width, float height, float angle, unsigned int color)
{
	_x = x;
	_y = y;
	_w = width;
	_h = height;
	_angle = angle;
	_color = color;
}

bool RectPrim::Contains(float X, float Y)
{
	return ( X >= _x && X <= _x+_w && Y >= _y && Y <= _y+_h );
}

void RectPrim::SetX(float x) { _x = x; }
void RectPrim::SetY(float y) { _y = y; }
void RectPrim::SetWidth(float w) { _w = w; }
void RectPrim::SetHeight(float h) { _h = h; }

void RectPrim::SetSize(float w, float h)
{
	_w = w;
	_h = h;
}

void RectPrim::SetPos(float X, float Y)
{
	_x = X;
	_y = Y;
}

void RectPrim::SetBounds(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_w = width;
	_h = height;
}

float RectPrim::GetX(){ return _x; }
float RectPrim::GetY(){ return _y; }
float RectPrim::GetWidth(){ return _w; }
float RectPrim::GetHeight(){ return _h; }

float RectPrim::GetMidX() { return _x+_w/2; }
float RectPrim::GetMidY() { return _y+_h/2; }

void RectPrim::SetRotation(float angle)
{
	_angle = angle;
}

void RectPrim::SetColor(int red, int green, int blue, int alpha)
{
	if(red<0)	red		= 0; else if(red	> 255)	red		= 255;
	if(green<0) green	= 0; else if(green	> 255)	green	= 255;
	if(blue<0)	blue	= 0; else if(blue	> 255)	blue	= 255;
	if(alpha<0) alpha	= 0; else if(alpha	> 255)	alpha	= 255;

	_color = (unsigned int)( (red<<24) + (green<<16) + (blue<<8) + alpha );
}

void RectPrim::SetColor(unsigned int color)
{
	_color	= color;
}

unsigned int RectPrim::GetColor()
{
	return _color;
}

void RectPrim::Draw()
{
	Draw(_x, _y, _w, _h, _angle, _color);
}

void RectPrim::Draw(float x, float y, float w, float h, float angle, unsigned int color)
{
	GLfloat ver[8];

	ver[0] = x;			ver[1] = y;
	ver[2] = x+w;		ver[3] = y;
	ver[4] = x;			ver[5] = y+h;
	ver[6] = x+w;		ver[7] = y+h;

	float red	= (float)((color >> 24) & 255);
	float green	= (float)((color >> 16) & 255);
	float blue	= (float)((color >> 8) & 255);
	float alpha	= (float)((color ) & 255);

	glColor4f(((float)red)/255.0f, ((float)green)/255.0f, ((float)blue)/255.0f, ((float)alpha)/255.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void RectPrim::DrawBorder(float x, float y, float w, float h, float lineWidth, unsigned int color)
{
	x = (int)x;
	y = (int)y;
	w = (int)w;
	h = (int)h;

	float half = lineWidth/2;
	GLfloat ver[16];

	ver[0] = x-half;			ver[1] = y;
	ver[2] = x+w+half;			ver[3] = y;

	ver[4] = x+w;				ver[5] = y;
	ver[6] = x+w;				ver[7] = y+h;

	ver[8] = x+w+half;			ver[9] = y+h;
	ver[10] = x-half;			ver[11] = y+h;

	ver[12] = x;				ver[13] = y+h;
	ver[14] = x;				ver[15] = y;

	float red	= (float)((color >> 24) & 255);
	float green	= (float)((color >> 16) & 255);
	float blue	= (float)((color >> 8) & 255);
	float alpha	= (float)((color ) & 255);

	float prevLW = 1.0f;
	glGetFloatv(GL_LINE_WIDTH, &prevLW);

	glLineWidth(lineWidth);
	glColor4f(((float)red)/255.0f, ((float)green)/255.0f, ((float)blue)/255.0f, ((float)alpha)/255.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_LINES,0,8);
	glDisableClientState(GL_VERTEX_ARRAY);

	glLineWidth(prevLW);
}

void RectPrim::Draw(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2)
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

RectPrim::~RectPrim()
{
}
