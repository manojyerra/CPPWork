#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#pragma once

#include "RectPrim.h"
#include "Button.h"
#include "ButtonNew.h"
#include "LeaderBoardData.h"


class FBuf
{
    unsigned char* buf;
    int pos;
 
public:
    FBuf(int size)
    {
        buf = (unsigned char*)malloc(size);
        pos = 0;
    }
    
    void add(unsigned char* copyFrom, int size)
    {
        memcpy(&buf[pos], copyFrom, size);
        pos += size;
    }
    
    int writeToFile(char* filePath)
    {
        int returnVal = 0;
        FILE *fp = fopen(filePath, "wb");
        
        if(fp != NULL)
        {
            fwrite(buf, 1, pos, fp);
            fclose(fp);
            returnVal = pos;
        }
        
        if(buf)
        {
            free(buf);
            buf = NULL;
        }
        
        pos = 0;
        
        return returnVal;
    }
    
    ~FBuf()
    {
        if(buf)
        {
            free(buf);
            buf = NULL;
        }
        
        pos = 0;
    }
};


class LeaderBoard
{
private:
	RectPrim* _bg;
	RectPrim* _bottomBorder;

	ButtonNew* _cellBgBtn;
	Button* _backBtn;
	Sprite* _circle;
	Sprite* _defaultPic;
	LeaderBoardData* _lbData;

	int _heading;
	int _border;
	int _cellH;
	int _cellsStartY;

	int _showCells;

	bool _isActive;
	float _transY;
	float _speed;
	float _elapsedTime;
	float _speedCoff;
	float _lastScrollTime;

	int _offLineRank;

	void DrawCell(int x, int y, int w, int h, int index);
	void DrawNumber(int num, int x, int y, int fontH, unsigned int color);
	void DrawStarsTimeMoves(int stars, int time, int moves, int x, int y, int fontH, bool isUser);
	void DrawUserInfo(string name, string country, int lastUnlock, int x, int y, int fontH, int gap, bool isUser);
	void DrawHeading(int x, int y, int w, int h, int fontH, unsigned int color);

	void GenerateOffLineRank();

	vector<Sprite*> _picsVec;
	Sprite* _userPic;

public:
	LeaderBoard();
	~LeaderBoard();
	void Update();
	void SetActive(bool isActive);
	bool IsActive();
	int GetRank();
	void Draw();
};

#endif

/*
int WriteTGA(const char *filename, int width, int height, int bytesPerPixel, unsigned char* image_data, bool compress);
int tga_write_row_RLE(FBuf* fBuf, int width, int height, unsigned char pixel_depth, const unsigned char *row);
unsigned char rle_packet_len(const unsigned char *row, int pos, int width, int bpp, unsigned char type);
unsigned char rle_packet_type(const unsigned char *row, int pos, int width, int bpp);
*/
