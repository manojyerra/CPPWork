#include "LinePrim.h"
#include "Includes.h"
#include "math.h"

#include <vector>
using namespace std;

LinePrim::LinePrim(float x1, float y1, float x2, float y2)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
}

void LinePrim::SetColor(int r, int g, int b, int a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void LinePrim::Draw()
{
	GLfloat ver[4];
	ver[0] = _x1;
	ver[1] = _y1;
	ver[2] = _x2;
	ver[3] = _y2;

	glColor4f( ((float)_r)/255.0f, ((float)_g)/255.0f,((float)_b)/255.0f,((float)_a)/(2.0f*255.0f));
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void LinePrim::Draw(float x1, float y1, float x2, float y2, unsigned int color)
{
	LinePrim::Draw(x1,y1,x2,y2,color,1);
}

void LinePrim::Draw(float x1, float y1, float x2, float y2, unsigned int color, float lineWidth)
{
	GLfloat ver[4];

	ver[0] = x1;	ver[1] = y1;
	ver[2] = x2;	ver[3] = y2;

	float red	= (float)((color >> 24) & 255);
	float green	= (float)((color >> 16) & 255);
	float blue	= (float)((color >> 8) & 255);
	float alpha	= (float)((color ) & 255);

	glLineWidth(lineWidth);
	glColor4f( red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void LinePrim::DrawStrippedLine(float x1, float y1, float x2, float y2, unsigned int color, float lineWidth)
{
	GLfloat ver[200];

	float vx = x2-x1;
	float vy = y2-y1;

	float length = sqrt(vx*vx + vy*vy);

	float nx = vx / length;
	float ny = vy / length;

	int count = 0;
	for(int i=0;i<length;)
	{
		ver[count] = x1 + nx*i; count++;
		ver[count] = y1 + ny*i; count++;

		i+=8;
		if(i>=length)break;

		ver[count] = x1 + nx*i; count++;
		ver[count] = y1 + ny*i; count++;

		i+=4;
	}

	float red	= (float)((color >> 24) & 255);
	float green	= (float)((color >> 16) & 255);
	float blue	= (float)((color >> 8) & 255);
	float alpha	= (float)((color ) & 255);

	glLineWidth(lineWidth);
	glColor4f( red/255.0f, green/255.0f, blue/255.0f, alpha/255.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glDrawArrays(GL_LINES,0,count/2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

LinePrim::~LinePrim()
{
}
