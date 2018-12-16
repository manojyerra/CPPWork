#include "PolyPrim.h"
#include "Includes.h"

PolyPrim::PolyPrim(vector<Point> vec)
{
	_vec = vec;

	_r = 255;
	_g = 255;
	_b = 255;
	_a = 255;
}

void PolyPrim::SetColor(int r, int g, int b, int a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

void PolyPrim::Draw()
{
	GLenum mode = 0;
	int verCount = 0;

#ifdef PLATFORM_WIN32
	mode = GL_POLYGON;
#endif
#ifdef PLATFORM_MARMALADE
	mode = GL_LINE_LOOP;
#endif

	glColor4f( ((float)_r)/255.0f, ((float)_g)/255.0f,((float)_b)/255.0f,((float)_a)/255.0f);
	glEnableClientState(GL_VERTEX_ARRAY);

	if(_vec.size() < 100)
	{
		GLfloat ver[100*2];

		for(int i=0;i<(int)_vec.size();i++)
		{
			ver[verCount] = _vec[i].x;
			ver[verCount+1] = _vec[i].y;
			verCount += 2;
		}
		glVertexPointer(2, GL_FLOAT, 0, ver);
	}
	else if(_vec.size() < 500)
	{
		GLfloat ver[500*2];

		for(int i=0;i<(int)_vec.size();i++)
		{
			ver[verCount] = _vec[i].x;
			ver[verCount+1] = _vec[i].y;
			verCount += 2;
		}
		glVertexPointer(2, GL_FLOAT, 0, ver);
	}
	else if(_vec.size() < 1000)
	{
		GLfloat ver[1000*2];

		for(int i=0;i<(int)_vec.size();i++)
		{
			ver[verCount] = _vec[i].x;
			ver[verCount+1] = _vec[i].y;
			verCount += 2;
		}
		glVertexPointer(2, GL_FLOAT, 0, ver);
	}


	glDrawArrays(mode,0,verCount);
	glDisableClientState(GL_VERTEX_ARRAY);
}


PolyPrim::~PolyPrim()
{
}
