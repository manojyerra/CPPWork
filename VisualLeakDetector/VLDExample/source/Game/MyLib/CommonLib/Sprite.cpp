#include "Sprite.h"
#include "AddData.h"
#include "TextureManager.h"
#include "math.h"
#include "Rect2D.h"

Sprite::Sprite(const char *texturePath, float x, float y, float w, float h)
{
	_texture = TextureManager::GetInstance()->CreateTexture(texturePath);
	Reset(x, y, w, h, 0, 0, _texture->width, _texture->height);
}

Sprite::Sprite(const char *texturePath, float x, float y, float w, float h, int readFrom)
{
	_texture = TextureManager::GetInstance()->CreateTexture(texturePath, readFrom);
	Reset(x, y, w, h, 0, 0, _texture->width, _texture->height);
}

Sprite::Sprite(const char *texturePath, float x, float y, float drawWidth, float drawHeight, float u, float v, float cw, float ch)
{
	_texture = TextureManager::GetInstance()->CreateTexture(texturePath);
	Reset(x, y, drawWidth, drawHeight, u, v, cw, ch);
}

void Sprite::Reset(float x, float y, float drawWidth, float drawHeight, int u, int v, int cw, int ch)
{
	_x = x;
	_y = y;
	_drawWidth = drawWidth;
	_drawHeight = drawHeight;

	_u = u;
	_v = v;
	_cropWidth = cw;
	_cropHeight = ch;

	_visible = true;
	_red = 255;
	_green = 255;
	_blue = 255;
	_alpha = 255;
	_color = 0xffffffff;

	_rotateBasedOnCenter = false;

	_angle = 0.0f;
	_centerX = _x+_drawWidth/2;
	_centerY = _y+_drawHeight/2;
}

TextureInfo* Sprite::GetTextureInfo()
{
	return _texture;
}

void Sprite::Draw()
{
	if(_texture->textureID != 0 && _visible)
		DrawImageRegion( _x,_y, _drawWidth, _drawHeight, _u,_v,  _cropWidth,_cropHeight);
}

void Sprite::DrawFromCenter()
{
	if(_texture->textureID != 0 && _visible)
	{
		float x = _x;
		float y = _y;

		SetPos(_x-_drawWidth/2, _y-_drawHeight/2);

		DrawImageRegion( _x,_y, _drawWidth, _drawHeight, _u,_v,  _cropWidth,_cropHeight);

		SetPos(x, y);
	}
}

void Sprite::DrawImageRegion(float x, float y, float drawWidth, float drawHeight, int u, int v, int cropWidth, int cropHeight)
{
	GLfloat ver[12];
	GLfloat uvs[12];

	ver[0] = x;				ver[1] = y;
	ver[2] = x+drawWidth;	ver[3] = y;
	ver[4] = x;				ver[5] = y+drawHeight;
	ver[6] = x+drawWidth;	ver[7] = y;
	ver[8] = x;				ver[9] = y+drawHeight;
	ver[10] = x+drawWidth;	ver[11] = y+drawHeight;

	float u1 = (float)u/(float)_texture->width;
	float v1 = (float)v/(float)_texture->height;
	float u2 = ((float)(u+cropWidth))/(float)_texture->width;
	float v2 = ((float)(v+cropHeight))/(float)_texture->height;

	uvs[0] = u1;			uvs[1] = v1;
	uvs[2] = u2;			uvs[3] = v1;
	uvs[4] = u1;			uvs[5] = v2;
	uvs[6] = u2;			uvs[7] = v1;
	uvs[8] = u1;			uvs[9] = v2;
	uvs[10] = u2;			uvs[11] = v2;

	if(_rotateBasedOnCenter)
	{
		_centerX = x+drawWidth/2;
		_centerY = y+drawHeight/2;
	}

	if(_angle != 0.0f)
	{
		for(int i=0;i<12;i+=2)
		{
			Posf newpos = Posf::RotatePoint(ver[i], ver[i+1], _centerX, _centerY, _angle);
			ver[i] = newpos.x;
			ver[i+1] = newpos.y;
		}
	}

	glColor4f(((float)_red)/255.0f, ((float)_green)/255.0f, ((float)_blue)/255.0f, ((float)_alpha)/255.0f);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindTexture(GL_TEXTURE_2D, _texture->textureID);
	glVertexPointer(2, GL_FLOAT, 0, ver);
	glTexCoordPointer (2, GL_FLOAT, 0, uvs);

	glDrawArrays(GL_TRIANGLES,0,6);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

bool Sprite::CollidesWith(Sprite* img)
{
	Rect2D rect1(GetX(), GetY(), GetWidth(), GetHeight());
	Rect2D rect2(img->GetX(), img->GetY(), img->GetWidth(), img->GetHeight());

	return rect1.IsColliding(&rect2);
}

bool Sprite::Intersects(float rectX, float rectY, float rectWidth, float rectHeight)
{
	int tw = (int)_drawWidth;
	int th = (int)_drawHeight;
	int rw = (int)rectWidth;
	int rh = (int)rectHeight;

	if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) 
		return false; 

	int tx = (int)_x;
	int ty = (int)_y;
	int rx = (int)rectX;
	int ry = (int)rectY;

	rw += rx;
	rh += ry;
	tw += tx;
	th += ty;

	return ((rw < rx || rw > tx) &&	(rh < ry || rh > ty) &&	(tw < tx || tw > rx) && (th < ty || th > ry));	
}

bool Sprite::Contains(float X, float Y) 
{
	return ( X >= _x && X <= _x+_drawWidth && Y >= _y && Y <= _y+_drawHeight );
}

bool Sprite::Contains(float X, float Y, float offSetX, float offSetY)
{
	return ( X >= _x-offSetX && X <= _x+_drawWidth+2*offSetX && Y >= _y-offSetY && Y <= _y+_drawHeight+2*offSetY );
}

void Sprite::SetX(float x)						{	SetBounds(x, _y, _drawWidth, _drawHeight);	}
void Sprite::SetY(float y)						{	SetBounds(_x, y, _drawWidth, _drawHeight);	}
void Sprite::SetPos(float x, float y)			{	SetBounds(x, y, _drawWidth, _drawHeight);	}
void Sprite::SetWidth(float drawWidth)			{	SetBounds(_x, _y, drawWidth, _drawHeight);	}
void Sprite::SetHeight(float drawHeight)		{	SetBounds(_x, _y, _drawWidth, drawHeight);	}
void Sprite::SetSize(float drawW, float drawH)	{	SetBounds(_x, _y, drawW,	 drawH		);	}

void Sprite::SetMidPos(float midX, float midY)
{
	SetBounds(midX-_drawWidth/2.0f, midY-_drawHeight/2.0f, _drawWidth, _drawHeight);
}

void Sprite::SetBounds(float x, float y, float drawWidth, float drawHeight)
{
	_x = x;
	_y = y;
	_drawWidth = drawWidth;
	_drawHeight = drawHeight;

	if(_rotateBasedOnCenter)
		SetRotation(_angle);
}

void  Sprite::SetRotation(float angle)
{
	_rotateBasedOnCenter = true;
	_angle = ((int)angle%360) + (angle - (int)angle);
}

void Sprite::SetRotation(float angle, int centerX, int centerY)
{
	_rotateBasedOnCenter = false;
	_angle = ((int)angle%360) + (angle - (int)angle);
	_centerX = (float)centerX;
	_centerY = (float)centerY;
}

float Sprite::GetRotation()
{
	return _angle;
}

Posf Sprite::GetCenterInRotation()
{
	Posf newPos1 = Posf::RotatePoint(_x, _y, _centerX, _centerY, _angle);
	Posf newPos2 = Posf::RotatePoint(_x+_drawWidth, _y+_drawHeight, _centerX, _centerY, _angle);

	return Posf( (newPos1.x + newPos2.x)/2.0f, (newPos1.y + newPos2.y)/2.0f );
}

float Sprite::GetX() { return _x; }
float Sprite::GetY() { return _y; }
float Sprite::GetWidth() { return _drawWidth; }
float Sprite::GetHeight() { return _drawHeight; }


void Sprite::SetUVBoundsInPixels(int u, int v, int cropWidth, int cropHeight)
{
	_u = u;
	_v = v;
	_cropWidth = cropWidth;
	_cropHeight = cropHeight;
}

void Sprite::SetUVBounds0To1(float u, float v, float cropWidth, float cropHeight)
{
	_u = u * (float)_texture->width;
	_v = v * (float)_texture->height;
	_cropWidth = cropWidth * (float)_texture->width;
	_cropHeight = cropHeight * (float)_texture->height;
}

void Sprite::SetUVToContent()
{
	if(_texture->contentW > 0 && _texture->contentH > 0)
	{
		_u = 0;
		_v = 0;
		_cropWidth = _texture->contentW;
		_cropHeight = _texture->contentH;
	}
}

int Sprite::GetU() { return _u; }
int Sprite::GetV() { return _v; }
void Sprite::SetU(int u) {	_u = u; }
void Sprite::SetV(int v) {	_v = v; }


void Sprite::SetVisible(bool visible) { _visible = visible; }
bool Sprite::IsVisible() { return _visible; }


void Sprite::SetColor(int red, int green, int blue, int alpha)
{	if(red<0)	_red	= 0; else if(red	> 255)	_red	= 255; else _red	= red;
	if(green<0) _green	= 0; else if(green	> 255)	_green	= 255; else _green	= green;
	if(blue<0)	_blue	= 0; else if(blue	> 255)	_blue	= 255; else _blue	= blue;
	if(alpha<0) _alpha	= 0; else if(alpha	> 255)	_alpha	= 255; else _alpha	= alpha;

	_color = (unsigned int)( (_red<<24) + (_green<<16) + (_blue<<8) + _alpha );
}

void Sprite::SetColor(unsigned int color)
{
	_color	= color;
	_red	= (_color >> 24) & 255;
	_green	= (_color >> 16) & 255;
	_blue	= (_color >> 8) & 255;
	_alpha	= (_color ) & 255;
}

void Sprite::SetRed(int red) { SetColor( red, GetGreen(), GetBlue(), GetAlpha()); }
void Sprite::SetGreen(int green) { SetColor( GetRed(), green, GetBlue(), GetAlpha()); }
void Sprite::SetBlue(int blue) { SetColor( GetRed(), GetGreen(), blue, GetAlpha()); }
void Sprite::SetAlpha(int alpha) 
{
	if(alpha < 0)
		alpha = 0;
	SetColor( GetRed(), GetGreen(), GetBlue(), alpha ); 
}

int Sprite::GetColor() { return _color; }
int Sprite::GetRed() { return _red; };
int Sprite::GetGreen() { return _green; };
int Sprite::GetBlue() { return _blue; };
int Sprite::GetAlpha() { return _alpha; };

Sprite::~Sprite()
{
	if(_texture)
	{
		TextureManager::GetInstance()->DeleteTexture(_texture);
		_texture = NULL;
	}
}
