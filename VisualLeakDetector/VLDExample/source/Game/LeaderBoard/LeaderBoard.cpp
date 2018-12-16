#include "LeaderBoard.h"
#include "GameInfo.h"
#include "Platform.h"
#include "UIFont.h"
#include "Input.h"
#include "SaveManager.h"
#include "Flags.h"
#include "ColorTheme.h"

LeaderBoard::LeaderBoard()
{
	_isActive = false;
	_transY = 0;
	_speed = 0;
	_elapsedTime = 0;
	_speedCoff = 1.0f;
	_lastScrollTime = 0;
	_offLineRank = 0;
	_lbData = NULL;
	_userPic = NULL;

	int sw = GameInfo::GetInstance()->CodedW();
	int sh = GameInfo::GetInstance()->CodedH();

	_bg = new RectPrim(0,0, sw, sh, 0, 0x00000000);
	_bg->SetColor(82,153,251,255);

	_border = 10;
	_heading = 60;
	_cellH = 130;
	_cellsStartY = _bg->GetY() + _heading;

	ColorTheme* ct = ColorTheme::GetInstance();

	_bottomBorder = new RectPrim(_bg->GetX(), sh-_border, _bg->GetWidth(), _border, 0, 0x00000000);
	_bottomBorder->SetColor(ct->bgBR, ct->bgBG, ct->bgBB, ct->bgBA);

	_backBtn = new Button("pages/btns/close.png", "pages/btns/close.png",380,_bg->GetY()-0.5*_border,100,100);

	_cellBgBtn = new ButtonNew("", 0,0,0,0, 6);
	//_cellBgBtn->SetTopColor(255, 128, 255, 255);
	//_cellBgBtn->SetBottomColor(170, 128, 213, 255);

	_defaultPic = new Sprite("numberpuzzle/defaultpic.png",0,0,62,62);
	_circle = new Sprite("numberpuzzle/circle.png", 0,0,56,56);

	_showCells = SHOW_PLAYERS_ON_LB;
}

void LeaderBoard::SetActive(bool isActive)
{
	_isActive = isActive;
	_transY = 0;

	GameInfo::GetInstance()->SetLeaderBoardOn(_isActive);

	if(isActive)
	{
		_lbData = new LeaderBoardData();

		int size = sizeof(LeaderBoardData);

		std::string filePath = "";
		
		if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_3x3)
			filePath = Platform::GetPlatform()->GetSaveFolderPath()+"/lb_3x3.sda";
		else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_4x4)
			filePath = Platform::GetPlatform()->GetSaveFolderPath()+"/lb_4x4.sda";
		else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_5x5)
			filePath = Platform::GetPlatform()->GetSaveFolderPath()+"/lb_5x5.sda";

		FILE* fp = fopen(filePath.c_str(),"rb");

		if(fp != NULL)
		{
			int failCount = 0;

			while(true)
			{
				if(fread(_lbData, 1, size, fp) == size)
				{
					printLog("online rank : %d, offline rank going generate now... ", _lbData->Rank);

					fclose(fp);
					_lbData->SetUserInfo();

					GenerateOffLineRank();
					break;
				}
				else
				{
					failCount++;

					if(failCount == 10)
					{
						printLog("Unable to read LB data properly, making LB data empty and left reading.");

						if(_lbData)
						{
							delete _lbData;
							_lbData = new LeaderBoardData();
						}

						GenerateOffLineRank();

						break;
					}
					else
					{
						printLog("issue in reading LB data at cpp, might be reading while writing file in java...");
						printLog("Going try again in few seconds...");

						float val = 0;

						for(int i=0;i<5000;i++)
							val = sqrt((float)234);

						float tempVal = val;
						float temp2 = tempVal;
					}
				}
			}
		}
		else
		{
			printLog("LB file <%s> not found.", filePath.c_str());

			if(_lbData)
			{
				delete _lbData;
				_lbData = new LeaderBoardData();
			}

			GenerateOffLineRank();
		}
	}
	else
	{
		if(_lbData)
		{
			delete _lbData;
			_lbData = NULL;
		}

		for(int i=0;i<_picsVec.size();i++)
		{
			if(_picsVec[i] != NULL)
			{
				delete _picsVec[i];
				_picsVec[i] = NULL;
			}
		}

		_picsVec.clear();

		if(_userPic)
		{
			delete _userPic;
			_userPic = NULL;
		}
	}

	if(_lbData)
	{
		for(int i=0; i<(int)SHOW_PLAYERS_ON_LB; i++)
		{
			if(_lbData->ObjectID[i][0] != '\0')
			{
				char path[128];
				sprintf(path, "lbpics/%s.jpg", _lbData->ObjectID[i]);
				Sprite* sprite = new Sprite(path, 0,0,64,64, Platform::READ_FROM_IM);
				TextureInfo* texInfo = sprite->GetTextureInfo();

				if(texInfo->width == 0 || texInfo->height == 0)
				{
					//printLog("\n%s image not found...", path);
					delete sprite;
					sprite = NULL;
				}
				else if(texInfo->contentW > 0 && texInfo->contentH > 0)
				{
					sprite->SetUVToContent();
					sprite->SetSize( texInfo->contentW, texInfo->contentH );
				}

				_picsVec.push_back(sprite);
			}
			else
			{
				_picsVec.push_back(NULL);
			}
		}
	}

	_userPic = new Sprite("lbpic.jpg", 0,0,64,64, Platform::READ_FROM_IM);
	TextureInfo* texInfo = _userPic->GetTextureInfo();

	if(texInfo->width == 0 || texInfo->height == 0)
	{
		delete _userPic;
		_userPic = NULL;
	}
	else if(texInfo->contentW > 0 && texInfo->contentH > 0)
	{
		_userPic->SetUVToContent();
		_userPic->SetSize( texInfo->contentW, texInfo->contentH );
	}
}

void LeaderBoard::GenerateOffLineRank()
{
	_offLineRank = 0;

	int totStars = SaveManager::GetInstance()->GetTotalStars();
	int totTime = SaveManager::GetInstance()->GetTotalTime();
	int totMoves = SaveManager::GetInstance()->GetTotalMoves();
	string name(_lbData->UserName);
	string country(_lbData->UserCountryName);

	printLog("Total Stars : %d", totStars);

	for(int i=0;i<FETCH_NUM_PLAYERS;i++)
	{
		//printLog("%d) player stars %d",i,_lbData->NumStarsArray[i]);

		if(totStars > _lbData->NumStarsArray[i])
		{
			_offLineRank = i+1;
			//printLog("stars are more, rank : %d", _offLineRank);
			break;
		}
		else if(totStars == _lbData->NumStarsArray[i])
		{
			//printLog("stars count is same");

			if(totTime < _lbData->TimeArray[i] || _lbData->TimeArray[i] <= 0)
			{
				if(totTime == 0 && _lbData->TimeArray[i] > 0)
					continue;

				_offLineRank = i+1;
				//printLog("time is less, rank : %d", _offLineRank);
				break;
			}
			else if(totTime == _lbData->TimeArray[i])
			{
				//printLog("time count is same");

				if(totMoves < _lbData->NumMovesArray[i] || _lbData->NumMovesArray[i] <= 0)
				{
					_offLineRank = i+1;
					//printLog("moves are less, rank : %d", _offLineRank);
					break;
				}
				else if(totMoves == _lbData->NumMovesArray[i])
				{
					//printLog("moves count is same");

					if(i < SHOW_PLAYERS_ON_LB)
					{
						string otherName(_lbData->NamesArray[i]);

						//printLog("name <%s>, othername <%s>",name.c_str(), otherName.c_str());

						if(name.compare(otherName) <= 0)
						{
							_offLineRank = i+1;
							//printLog("names are same. rank : %d", _offLineRank);
							break;
						}
					}
					else
					{
						_offLineRank = i+1;
						break;
					}
				}
			}
		}
	}

	printLog("offline rank is %d", _offLineRank);

	if(_lbData->Rank > 0 && _lbData->Rank <= SHOW_PLAYERS_ON_LB)
	{
		for(int i=_lbData->Rank-1; i<SHOW_PLAYERS_ON_LB-1; i++)
		{
			for(int j=0;j<32;j++)
			{
				_lbData->ObjectID[i][j]				= _lbData->ObjectID[i+1][j];
				_lbData->NamesArray[i][j]			= _lbData->NamesArray[i+1][j];
				_lbData->CountryNameArray[i][j] 	= _lbData->CountryNameArray[i+1][j];
			}

			_lbData->NumStarsArray[i]				= _lbData->NumStarsArray[i+1];
			_lbData->TimeArray[i]					= _lbData->TimeArray[i+1];
			_lbData->NumMovesArray[i]				= _lbData->NumMovesArray[i+1];
			_lbData->LevelsPlayedArray[i]			= _lbData->LevelsPlayedArray[i+1];
		}
	}

	if(_offLineRank > 0 && _offLineRank <= SHOW_PLAYERS_ON_LB)
	{
		for(int i=SHOW_PLAYERS_ON_LB-1; i>=_offLineRank; i--)
		{
			for(int j=0;j<32;j++)
			{
				_lbData->ObjectID[i][j]				= _lbData->ObjectID[i-1][j];
				_lbData->NamesArray[i][j]			= _lbData->NamesArray[i-1][j];
				_lbData->CountryNameArray[i][j] 	= _lbData->CountryNameArray[i-1][j];
			}

			_lbData->NumStarsArray[i]				= _lbData->NumStarsArray[i-1];
			_lbData->TimeArray[i]					= _lbData->TimeArray[i-1];
			_lbData->NumMovesArray[i]				= _lbData->NumMovesArray[i-1];
			_lbData->LevelsPlayedArray[i]			= _lbData->LevelsPlayedArray[i-1];
		}

		for(int j=0;j<32;j++)
		{
			_lbData->NamesArray[_offLineRank-1][j]			= _lbData->UserName[j];
			_lbData->CountryNameArray[_offLineRank-1][j]	= _lbData->UserCountryName[j];
		}

		_lbData->NumStarsArray[_offLineRank-1]				= SaveManager::GetInstance()->GetTotalStars();
		_lbData->TimeArray[_offLineRank-1]					= SaveManager::GetInstance()->GetTotalTime();
		_lbData->NumMovesArray[_offLineRank-1]				= SaveManager::GetInstance()->GetTotalMoves();
		_lbData->LevelsPlayedArray[_offLineRank-1]			= SaveManager::GetInstance()->GetTotalLevelsPlayed();
	}

	printLog("End of : GenerateOffLineRank");
}

bool LeaderBoard::IsActive()
{
	return _isActive;
}

int LeaderBoard::GetRank()
{
	return _offLineRank;
}

void LeaderBoard::Update()
{
	_elapsedTime += GameInfo::deltaTime;

	if(_backBtn)
		_backBtn->Update();

	if((_backBtn && _backBtn->IsClicked()) || Input::IsBackPressed())
	{
		SetActive(false);
		return;
	}

	//if(Input::IsMousePressed() && Input::IsMouseClicked() == false)
	//	_transY += 5*(Input::MouseY - Input::PrevMouseY);

	_transY -= _speed;
	
	_speed *= 0.98;

	if(_speed > -1 && _speed < 1)
		_speed = 0;

	if(Input::IsMousePressed() && Input::IsMouseClicked() == false)
	{
		_speed = 0;
		_transY += (Input::MouseY - Input::PrevMouseY);
	}
	else if(Input::IsMouseReleased())
	{
		float dist = Input::GetDistBetweenClickAndRelease();
		float time = Input::GetTimeBetweenClickAndRelease();

		_speed = (int)((dist/time)/35);

		if(_elapsedTime > 0 && _elapsedTime - _lastScrollTime < 0.2)
		{
			_speedCoff += 0.5f;
			//printLog("Incresed Speed Coff %f", _speedCoff);
		}
		else
		{
			//printLog("Speed Coff %f", _speedCoff);
			_speedCoff = 1.0f;
		}

		_speed *= _speedCoff;

		if(Input::MouseClickY - Input::MouseReleaseY < 0)
			_speed = -_speed;
	}

	int sh = GameInfo::GetInstance()->CodedH();
	int len = _cellsStartY + SHOW_PLAYERS_ON_LB * _cellH - sh + _border;

	if(_transY > 0)
	{
		_transY = 0;
		_speed = 0;
	}
	else if(_transY < -len)
	{
		_transY = -len;
		_speed = 0;
	}

	if(_speed > 40 || _speed < -40)
		_lastScrollTime = _elapsedTime;
}

void LeaderBoard::Draw()
{
	ColorTheme::Draw();

	char ch[256];

	if(_lbData)
	{
		int cellX = _bg->GetX() + _border;
		int cellW = _bg->GetWidth() - 2*_border;

		glPushMatrix();
		glTranslatef(0,_transY,0);

		for(int i=0; i<(int)SHOW_PLAYERS_ON_LB; i++)
			DrawCell(cellX, _cellsStartY+(i*_cellH), cellW, _cellH-15, i);

		glPopMatrix();

		DrawHeading(_bg->GetX(), _bg->GetY(), _bg->GetWidth(), _heading, 27, 0xffffffff);

		if(_backBtn)
			_backBtn->Draw();
	}

	_bottomBorder->Draw();

	/*
	static bool once = true;

	if(once)
	{
		once = false;
		int width = GameInfo::GetInstance()->SurfaceW();
		int height = GameInfo::GetInstance()->SurfaceH();
		int bytesPP = 4;

		void* buf = malloc(width * height * bytesPP);
		glReadPixels(0,0,width,height,GL_RGBA, GL_UNSIGNED_BYTE, buf);

		std::string savePath = "mnt/sdcard/sh.tga";
		//std::string savePath = "sh.tga";
		
		WriteTGA(savePath.c_str(), width, height, bytesPP, (unsigned char*)buf, true);
	}
	*/
}

void LeaderBoard::DrawCell(int x, int y, int w, int h, int index)
{
	bool isUser = (_offLineRank == index+1) ? true : false;

	int sh = GameInfo::GetInstance()->CodedH();

	float ty = y + _transY;
	if( ((ty > 0 && ty < sh) || (ty+h > 0 && ty+h < sh)) == false)
		return;

	int stars = _lbData->NumStarsArray[index];
	int time = _lbData->TimeArray[index];
	int moves = _lbData->NumMovesArray[index];
	int levelsPlayed = _lbData->LevelsPlayedArray[index];
	string name(_lbData->NamesArray[index]);
	string country(_lbData->CountryNameArray[index]);

	//if(index < countryNamesVec.size())
	//	country = countryNamesVec[index];

	_cellBgBtn->SetBounds(x,y,w,h);

	if(isUser == false)
	{
		if(moves == 0)
		{
			_cellBgBtn->SetColorID(ButtonNew::COLOR_EMPTY);
			_cellBgBtn->Draw();
		}
		else
		{
			_cellBgBtn->SetColorID(ButtonNew::COLOR_EMPTY);
			_cellBgBtn->Draw();
		}
	}
	else
	{
		_cellBgBtn->SetColorID(ButtonNew::COLOR4);
		_cellBgBtn->Draw();
	}

	//RectPrim::Draw(x+6,y+6,66,66, 0,0x5399ffff);	//Pic Bg

	if(isUser)
	{
		if(_userPic != NULL)
		{
			float sx = x+8;
			float sy = y+13;

			_userPic->SetPos(sx+32, sy+32);
			_userPic->DrawFromCenter();
		}
		else
		{
			_defaultPic->SetPos(x+8,y+13);
			_defaultPic->Draw();
		}
	}
	else
	{
		if((index < _picsVec.size() && _picsVec[index] != NULL) )
		{
			float sx = x+8;
			float sy = y+13;

			_picsVec[index]->SetPos(sx+32, sy+32);
			_picsVec[index]->DrawFromCenter();
		}
		else
		{
			_defaultPic->SetPos(x+8,y+13);
			_defaultPic->Draw();
		}
	}

	if(isUser == false)
		_circle->SetColor(92,231,251,255);
	else
		_circle->SetColor(255,255,255,255);

	_circle->SetPos(_bg->GetX()+_bg->GetWidth()-_border-_circle->GetWidth()-3, y+_border);
	_circle->Draw();

	//if(index < countryNamesVec.size())
		Flags::GetInstance()->Draw(country, x+330,y+11, 64,64);

	float numFontH = _circle->GetHeight()*0.53;
	DrawNumber(index+1, _circle->GetX()+_circle->GetWidth()/2, _circle->GetY()+_circle->GetHeight()/2 + numFontH*0.15, numFontH, 0x0000ffff);

	int fontH = 20;
	DrawStarsTimeMoves(stars, time, moves, x+25, y+h-fontH-3, fontH, isUser);

	if(moves != 0 || isUser)
		DrawUserInfo(name, country, levelsPlayed, x+86, y+10, fontH, 4, isUser);
	else
	{
		DrawUserInfo("unnamed", "unnamed", 0, x+86, y+10, fontH, 4, isUser);
	}
}

void LeaderBoard::DrawStarsTimeMoves(int stars, int time, int moves, int x, int y, int fontH, bool isUser)
{
	char chArr[256];
	
	if(isUser)
		UIFont::GetInstance()->SetColor(0xffff00ff);
	else
		UIFont::GetInstance()->SetColor(0x0000ffff);

	UIFont::GetInstance()->Begin();

	string timeStr = GameInfo::GetInstance()->GetTimeStr((int)time, "", "");

	sprintf(chArr, "Stars :              Time : %s      Moves : %d ", timeStr.c_str(), moves);

	UIFont::GetInstance()->Draw(chArr, x, y, fontH, -2, 0);

	if(stars < 10)			sprintf(chArr, "00%d", stars);
	else if(stars < 100)	sprintf(chArr, "0%d ", stars);
	else					sprintf(chArr, "%d  ", stars);

	if(isUser)
		UIFont::GetInstance()->SetColor(0xffffffff);
	else
		UIFont::GetInstance()->SetColor(0xffffffff);

	UIFont::GetInstance()->Draw(chArr, x+65, y, fontH, -2, 0);

	UIFont::GetInstance()->End();
}

void LeaderBoard::DrawUserInfo(string name, string country, int levelsPlayed, int x, int y, int fontH, int gap, bool isUser)
{
	char chArr[256];

	unsigned int color = 0x000000ff;

	if(isUser)
		color = 0xffffffff;

	UIFont::GetInstance()->SetColor(color);
	UIFont::GetInstance()->Begin();
	UIFont::GetInstance()->Draw("Name: ", x, y+(0*(fontH+gap)), fontH, -1,0);

	sprintf(chArr, "%s", name.c_str());

	if(isUser)
		UIFont::GetInstance()->SetColor(0xffff00ff);
	else
		UIFont::GetInstance()->SetColor(0,0,255,255);
	
	UIFont::GetInstance()->Draw(chArr, x+60, y+(0*(fontH+gap)), fontH+3, -1,0);

	UIFont::GetInstance()->SetColor(color);

	sprintf(chArr, "Country: %s", country.c_str());
	
	UIFont::GetInstance()->Draw(chArr, x, y+(2*(fontH+gap)), fontH, -1,0);

	sprintf(chArr, "Levels Played: %d", levelsPlayed);

	UIFont::GetInstance()->Draw(chArr, x, y+(1*(fontH+gap)), fontH, -1,0);

	UIFont::GetInstance()->End();
}

void LeaderBoard::DrawHeading(int x, int y, int w, int h, int fontH, unsigned int color)
{
	ColorTheme* ct = ColorTheme::GetInstance();

	RectPrim::Draw(x,y,w,h, ct->bgTR, ct->bgTG, ct->bgTB, ct->bgTA, ct->bgTR, ct->bgTG, ct->bgTB, ct->bgTA); //Heading bg

	UIFont::GetInstance()->SetColor(color);
	UIFont::GetInstance()->Begin();
	UIFont::GetInstance()->DrawFromCenter("Leader Board (All Levels)", x+w/2, y+h/3, fontH, 0);
	UIFont::GetInstance()->End();

	char chArr[64];
	sprintf(chArr, "Rank : %d", _offLineRank);
	UIFont::GetInstance()->SetColor(0xffff00ff);
	UIFont::GetInstance()->Begin();
	UIFont::GetInstance()->DrawFromCenter(chArr, x+w/2, y+4*h/5, 4*fontH/5, 0);
	UIFont::GetInstance()->End();
}

void LeaderBoard::DrawNumber(int num, int x, int y, int fontH, unsigned int color)
{
	char ch[16];
	sprintf(ch, "%d", num);
	UIFont::GetInstance()->SetColor(color);
	UIFont::GetInstance()->Begin();
	UIFont::GetInstance()->DrawFromCenter(ch, x, y, fontH, -3);
	UIFont::GetInstance()->End();
}

LeaderBoard::~LeaderBoard()
{
	if(_bg)
	{
		delete _bg;
		_bg = NULL;
	}

	if(_backBtn)
	{
		delete _backBtn;
		_backBtn = NULL;
	}

	if(_lbData)
	{
		delete _lbData;
		_lbData = NULL;
	}

	for(int i=0;i<_picsVec.size();i++)
	{
		if(_picsVec[i] != NULL)
		{
			delete _picsVec[i];
			_picsVec[i] = NULL;
		}
	}

	_picsVec.clear();

	if(_userPic)
	{
		delete _userPic;
		_userPic = NULL;
	}
	
	if(_bottomBorder)
	{
		delete _bottomBorder;
		_bottomBorder = NULL;
	}

	if(_defaultPic)
	{
		delete _defaultPic;
		_defaultPic = NULL;
	}

	if(_circle)
	{
		delete _circle;
		_circle = NULL;
	}

	if(_cellBgBtn)
	{
		delete _cellBgBtn;
		_cellBgBtn = NULL;
	}


}




/*
int LeaderBoard::WriteTGA(const char *filename, int width, int height, int bytesPerPixel, unsigned char* image_data, bool compress)
{
    int size = width*height*bytesPerPixel;

    for(int i=0; i<size; i+=bytesPerPixel)
    {
        unsigned char r = image_data[i+0];
        image_data[i+0] = image_data[i+2];
        image_data[i+2] = r;
    }
    
	unsigned char header[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	header[12] = width % 256;
	header[13] = width / 256;
	header[14] = height % 256;
	header[15] = height / 256;
	header[16] = bytesPerPixel * 8;

    FBuf tgaBuf(size+20);

	if(compress == false)
    {
        header[2] = 2;

        //fwrite(header, 1, 18, fp);
		//fwrite(image_data, 1, width * height * bytesPerPixel, fp);

        tgaBuf.add(header, 18);
        tgaBuf.add(image_data, width * height * bytesPerPixel);
    }
    else
    {
        header[2] = 10;

        //fwrite(header, 1, 18, fp);
        tgaBuf.add(header, 18);

		for(int row=0; row<height; row++)
			if(tga_write_row_RLE(&tgaBuf, width, height, bytesPerPixel*8, image_data + row*width*bytesPerPixel) == 0)
				return 0;
    }

    return tgaBuf.writeToFile((char*)filename);
}

#define PIXEL(ofs) ( row + (ofs)*bpp )
#define SAME(ofs1, ofs2) (memcmp(PIXEL(ofs1), PIXEL(ofs2), bpp) == 0)

int LeaderBoard::tga_write_row_RLE(FBuf* fBuf, int width, int height, unsigned char pixel_depth, const unsigned char *row)
{
    unsigned short pos = 0;
    unsigned short bpp = pixel_depth / 8;

	//unsigned char RAW = 0;
	unsigned char RLE = 1;

    while(pos < width)
    {
        unsigned char type = rle_packet_type(row, pos, width, bpp);
        unsigned char len = rle_packet_len(row, pos, width, bpp, type);
        unsigned char packet_header;

        packet_header = len - 1;
        if (type == RLE) packet_header |= (1 << 7);

        fBuf->add(&packet_header, 1);

		if (type == RLE)	fBuf->add((unsigned char*)PIXEL(pos), bpp);
        else				fBuf->add((unsigned char*)PIXEL(pos), bpp*len);	 // type == RAW

		pos += len;
    }

    return 1;
}

unsigned char LeaderBoard::rle_packet_len(const unsigned char *row, int pos, int width, int bpp, unsigned char type)
{
	unsigned char len = 2;

    if (pos == width - 1) return 1;
    if (pos == width - 2) return 2;

	unsigned char RAW = 0;
	unsigned char RLE = 1;

	if (type == RLE)
    {
        while (pos + len < width)
        {
            if (SAME(pos, pos+len))	len++; else return len;
            if (len == 128) return 128;
        }
    }
    else // type == RAW
    {
        while (pos + len < width)
        {
            if (rle_packet_type(row, pos+len, width, bpp) == RAW) len++; else return len;
            if (len == 128) return 128;
        }
    }
    return len; // hit end of row (width) 
}

unsigned char LeaderBoard::rle_packet_type(const unsigned char *row, int pos, int width, int bpp)
{
	unsigned char RAW = 0;
	unsigned char RLE = 1;

    if (pos == width - 1) return RAW; // one pixel
    if (SAME(pos,pos+1)) // dupe pixel
    {
        if (bpp > 1) return RLE;
        if ((pos < width - 2) && SAME(pos+1,pos+2)) return RLE;
    }

    return RAW;
}

#undef SAME
#undef PIXEL

*/