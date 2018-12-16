#include "ColorTheme.h"
#include "GameInfo.h"

ColorTheme* ColorTheme::_ref = 0;

ColorTheme::ColorTheme()
{
	bgTR =253;
	bgTG =198;
	bgTB =98;
	bgTA =255;

	bgBR =253;
	bgBG =100;
	bgBB =136;
	bgBA =255;
}

ColorTheme::~ColorTheme()
{
}

int ColorTheme::GetButtonColorID()
{
	return 1;
}

void ColorTheme::Draw()
{
	int ow = GameInfo::GetInstance()->CodedW();
	int oh = GameInfo::GetInstance()->CodedH();

	ColorTheme* c = ColorTheme::GetInstance();

	RectPrim::Draw(0,0,ow,oh, c->bgTR, c->bgTG, c->bgTB, c->bgTA, c->bgBR, c->bgBG, c->bgBB, c->bgBA);	
}

ColorTheme* ColorTheme::GetInstance()
{
	if(_ref == 0)
		_ref = new ColorTheme();
	return _ref;
}

void ColorTheme::DeleteInstance()
{
	if(_ref)
	{
		delete _ref;
		_ref = 0;
	}
}
