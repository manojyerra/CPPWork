#ifndef SAVEDATA_H
#define SAVEDATA_H
#pragma once

#define TOTAL_LEVELS_NUM_3x3 63
#define TOTAL_LEVELS_NUM_4x4 63
#define TOTAL_LEVELS_NUM_5x5 63

class SaveData
{
public:
	int TotalLevels_Num3x3;

	int NumStarsArray_Num3x3 [ TOTAL_LEVELS_NUM_3x3 ];
	int TimeArray_Num3x3 [ TOTAL_LEVELS_NUM_3x3 ];
	int NumMovesArray_Num3x3 [ TOTAL_LEVELS_NUM_3x3 ];

	int LastUnlockedLevel_Num3x3;
	int CurrLevel_Num3x3;



	int TotalLevels_Num4x4;

	int NumStarsArray_Num4x4 [ TOTAL_LEVELS_NUM_3x3 ];
	int TimeArray_Num4x4 [ TOTAL_LEVELS_NUM_3x3 ];
	int NumMovesArray_Num4x4 [ TOTAL_LEVELS_NUM_3x3 ];

	int LastUnlockedLevel_Num4x4;
	int CurrLevel_Num4x4;



	int TotalLevels_Num5x5;

	int NumStarsArray_Num5x5 [ TOTAL_LEVELS_NUM_5x5 ];
	int TimeArray_Num5x5 [ TOTAL_LEVELS_NUM_5x5 ];
	int NumMovesArray_Num5x5 [ TOTAL_LEVELS_NUM_5x5 ];

	int LastUnlockedLevel_Num5x5;
	int CurrLevel_Num5x5;


	int GameID;
};
#endif
