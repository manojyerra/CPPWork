#include "TriPrim.h"
#include "Includes.h"

TriPrim::TriPrim(float x1, float y1, float x2, float y2, float x3, float y3)
{
	_x[0] = x1;
	_y[0] = y1;
	_x[1] = x2;
	_y[1] = y2;
	_x[2] = x3;
	_y[2] = y3;

	_r = 255;
	_g = 255;
	_b = 255;
	_a = 255;
}

void TriPrim::SetColor(int r, int g, int b, int a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void TriPrim::Draw()
{
	GLfloat ver[6];
	ver[0] = _x[0];
	ver[1] = _y[0];
	ver[2] = _x[1];
	ver[3] = _y[1];
	ver[4] = _x[2];
	ver[5] = _y[2];

	glColor4f( ((float)_r)/255.0f, ((float)_g)/255.0f,((float)_b)/255.0f,((float)_a)/(2.0f*255.0f));
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

TriPrim::~TriPrim()
{
}
