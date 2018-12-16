#ifndef LEADERBOARDDATA_H
#define LEADERBOARDDATA_H
#pragma once

#define FETCH_NUM_PLAYERS 1000
#define SHOW_PLAYERS_ON_LB 1000

class LeaderBoardData
{
public:
	char ObjectID[SHOW_PLAYERS_ON_LB][32];
	char NamesArray[SHOW_PLAYERS_ON_LB][32];
	char CountryNameArray[SHOW_PLAYERS_ON_LB][32];

	int NumStarsArray[FETCH_NUM_PLAYERS];
	int TimeArray[FETCH_NUM_PLAYERS];
	int NumMovesArray[FETCH_NUM_PLAYERS];
	int LevelsPlayedArray[FETCH_NUM_PLAYERS];

	char UserName[32];
	char UserCountryName[32];

	int Rank;

	LeaderBoardData();
	void SetUserInfo();
};

#endif
