#include "CirclePrim.h"
#include "Includes.h"
#include <math.h>

CirclePrim::CirclePrim(float cx, float cy, float radius)
{
	_cx = cx;
	_cy = cy;
	_radius = radius;
	_angle = 0;

	_red = 255;
	_green = 255;
	_blue = 255;
	_alpha = 255;
}

bool CirclePrim::Contains( float x, float y )
{
	return ((_cx-x)*(_cx-x)+(_cy-y)*(_cy-y)) < _radius*_radius;
}

void CirclePrim::SetColor(int r, int g, int b, int a)
{
	_red = r;
	_green = g;
	_blue = b;
	_alpha = a;
}

void CirclePrim::SetPos(float cx, float cy)
{
	_cx = cx;
	_cy = cy;
}

void CirclePrim::SetRadius(float radius)
{
	_radius = radius;
}

void CirclePrim::Draw()
{
	GLfloat ver[200];
	int count = 0;

	ver[count] = _cx;			ver[count+1] = _cy;		count +=2;
	ver[count] = _cx+_radius;	ver[count+1] = _cy;		count +=2;
	
	for( int angle=10; angle<360; angle += 10 )
	{
		float radians = angle*(22.0f/7.0f)/180.0f;
		float x = _cx+_radius*cosf(radians);	
		float y = _cy+_radius*sinf(radians);
		ver[count] = x;			ver[count+1] = y;		count +=2;
	}

	ver[count] = _cx+_radius;	ver[count+1] = _cy;		count +=2;

	glColor4f( ((float)_red)/255.0f, ((float)_green)/255.0f,((float)_blue)/255.0f,((float)_alpha)/(2.0f*255.0f));
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_TRIANGLE_FAN,0,count/2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

CirclePrim::~CirclePrim()
{
}