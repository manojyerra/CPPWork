#include"AfterLevelOver.h"
#include "GameInfo.h"
#include "ModuleManager.h"
#include "SaveManager.h"
#include "Input.h"
#include "UIFont.h"
#include "FileReader.h"
#include "Platform.h"
#include "ColorTheme.h"

int AfterLevelOver::prevRank = 0;

AfterLevelOver::AfterLevelOver()
{
	int ow = GameInfo::GetInstance()->CodedW();
	int oh = GameInfo::GetInstance()->CodedH();

	float y = oh / 2.0f;

	float initX = 65;
	float initY = y - 75;

	AnimSprite* starAnim;
	starAnim = new AnimSprite();
	starAnim->AddSprite("numberpuzzle/star.png",initX+115*0,initY,115,115);
	starAnim->AddSprite("numberpuzzle/starglow.png",initX+115*0,initY,115,115);
	starAnim->SetFrameRate(3);
	starAnim->PlayAnimation();
	_animStarsVec.push_back(starAnim);

	starAnim = new AnimSprite();
	starAnim->AddSprite("numberpuzzle/star.png",initX+115*1,initY,115,115);
	starAnim->AddSprite("numberpuzzle/starglow.png",initX+115*1,initY,115,115);
	starAnim->SetFrameRate(3);
	starAnim->PlayAnimation();
	_animStarsVec.push_back(starAnim);

	starAnim = new AnimSprite();
	starAnim->AddSprite("numberpuzzle/star.png",initX+115*2,initY,115,115);
	starAnim->AddSprite("numberpuzzle/starglow.png",initX+115*2,initY,115,115);
	starAnim->SetFrameRate(3);
	starAnim->PlayAnimation();
	_animStarsVec.push_back(starAnim);

	_disableStars[0] = new Sprite("numberpuzzle/stardisable.png",initX,			initY,115,115);
	_disableStars[1] = new Sprite("numberpuzzle/stardisable.png",initX+115,		initY,115,115);
	_disableStars[2] = new Sprite("numberpuzzle/stardisable.png",initX+115*2,	initY,115,115);

	_homeBtn = new ButtonNew("Home",(ow-250)/4 - 115/2,y+85,115,65,ButtonNew::COLOR_EMPTY);
	_replayBtn = new ButtonNew("Replay",(ow+250)/2 , y+85,115,65,ButtonNew::COLOR_EMPTY);
	_platNextBtn = new ButtonNew("Next Level",(ow-200)/2,y+85,200,65, ButtonNew::COLOR_EMPTY);

	_leaderBoardBtn = new ButtonNew("High Scores",(ow-200)/2,0,200,65,1);
	_shareBtn = new ButtonNew("Share",60,755,170,65,ButtonNew::COLOR_EMPTY);
	_rateBtn = new ButtonNew("Rate",ow-60-170,755,170,65,ButtonNew::COLOR_EMPTY);

	float percentVal = 0.50;
	_homeBtn->SetFontSizeInPercent(percentVal);
	_replayBtn->SetFontSizeInPercent(percentVal);
	_platNextBtn->SetFontSizeInPercent(percentVal);
	_leaderBoardBtn->SetFontSizeInPercent(percentVal);
	_shareBtn->SetFontSizeInPercent(percentVal);
	_rateBtn->SetFontSizeInPercent(percentVal);


	_isActive = false;
	_timeCount = 0.0f;
	_showOnlyGlow = false;
	_atPresentShowNumStars = 0;

	_currStars = 0;
	_currMoves = 0;
	_currTime = 0;

	_rank = 0;

	_leaderBoard = new LeaderBoard();

	if(_leaderBoard)
	{
		_leaderBoard->SetActive(true);
		prevRank = _leaderBoard->GetRank();
		_leaderBoard->SetActive(false);
	}

	_msgBox = new MsgBox("Do you want to replay?");
	_msgBox->SetBgSize(400,150);
	_msgBox->SetActive(false);
	_msgBox->SetInActiveOnBackPress(true);
	_msgBox->AddButton("Yes");
	_msgBox->AddButton("No");

	//If you enjoy using please take a moment to rate the app. Thank you for your support!

	_rateFilePath = Platform::GetPlatform()->GetSaveFolderPath()+"/rate.txt";

	_rateMsgBox = new MsgBox("Do you like this game?");
	_rateMsgBox->SetBgSize(460,225);
	_rateMsgBox->SetActive(false);
	_rateMsgBox->SetInActiveOnBackPress(true);
	_rateMsgBox->AddButton("Yes, I will");
	_rateMsgBox->AddButton("Later");
}

void AfterLevelOver::Update()
{
	_timeCount += GameInfo::deltaTime;

	if(_rateMsgBox->IsActive())
	{
		_rateMsgBox->Update();

		if(_rateMsgBox->GetButtonIndex_OnClick() == 0)
		{
			FILE* rateFP = fopen(_rateFilePath.c_str(), "w");
			fprintf(rateFP, "-1");
			fflush(rateFP);
			fclose(rateFP);

			GameInfo::GetInstance()->SetReviewClicked(true);

			return;
		}
		else
		{
			FILE* rateFP = fopen(_rateFilePath.c_str(), "w");
			fprintf(rateFP, "0");
			fflush(rateFP);
			fclose(rateFP);
		}
	}
	else if(_msgBox->IsActive())
	{
		_msgBox->Update();

		if(_msgBox->GetButtonIndex_OnClick() == 0)		//Yes
		{
			ModuleManager::GetInstance()->SetModule(ModuleManager::GAME);
			GameInfo::GetInstance()->SetTimeToShowAd(true);
			return;
		}
	}
	else if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Update();
	}
	else
	{
		_homeBtn->Update();
		_replayBtn->Update();
		_platNextBtn->Update();
		_leaderBoardBtn->Update();
		_shareBtn->Update();
		_rateBtn->Update();

		if(_gameResult == WIN)
		{
			if(_platNextBtn->IsClicked())
			{
				if(SaveManager::GetInstance()->GetCurrLevel() == SaveManager::GetInstance()->GetNumTotalLevels())
					SaveManager::GetInstance()->SetCurrLevel(1);
				else
					SaveManager::GetInstance()->SetCurrLevel(SaveManager::GetInstance()->GetCurrLevel()+1);

				SaveManager::GetInstance()->SaveGame();
				ModuleManager::GetInstance()->SetModule(ModuleManager::GAME);

				GameInfo::GetInstance()->SetTimeToShowAd(true);
			}
			else if(_shareBtn && _shareBtn->IsClicked())
			{
				GameInfo::GetInstance()->SetShareClicked(true);
			}
			else if(_rateBtn && _rateBtn->IsClicked())
			{
				GameInfo::GetInstance()->SetReviewClicked(true);
			}
			else if(_leaderBoardBtn && _leaderBoardBtn->IsClicked())
			{
				_leaderBoard->SetActive(true);
			}
			else if(_homeBtn->IsClicked())
			{
				PagesManager::GetInstance()->SetCurrPage(PagesManager::MAINMENU);
				ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);
				return;
			}
			else if(_replayBtn->IsClicked())
			{
				ModuleManager::GetInstance()->SetModule(ModuleManager::GAME);
				GameInfo::GetInstance()->SetTimeToShowAd(true);
				return;
			}
			else if(Input::IsBackPressed())
			{
				_msgBox->SetActive(true);
			}
			else if(_timeCount > 2.0f)
			{
				_showOnlyGlow = true;
			}
		}
	}
}

void AfterLevelOver::SetCurrStars(int numStars)
{
	_currStars = numStars;
}

void AfterLevelOver::SetCurrTime(int time)
{
	_currTime = time;
}

void AfterLevelOver::SetCurrMoves(int moves)
{
	_currMoves = moves;
}

void AfterLevelOver::SetActive(bool isActive)
{
	_isActive = isActive;

	SetLevelFinished();

	if(_leaderBoard)
		_leaderBoard->SetActive(true);

	_rank = _leaderBoard->GetRank();

	if(_leaderBoard)
		_leaderBoard->SetActive(false);

	if(SaveManager::GetInstance()->GetTotalLevelsPlayed() >= 1)
	{
		if(_rank == 1)
		{
			Platform::GetPlatform()->ShowMsg("");
		}
		else if(prevRank == _rank)
		{
			//Platform::GetPlatform()->ShowMsg("No improvement in rank");
		}
		else if(_rank < prevRank)
		{
			char chArr[256];
			sprintf(chArr, "Improved Rank from %d to %d", prevRank, _rank);
			Platform::GetPlatform()->ShowMsg(chArr);
		}
	}

	prevRank = _rank;
}

bool AfterLevelOver::IsActive()
{
	return _isActive; 
}

void AfterLevelOver::SetGameResult(int gameResult)
{
	_gameResult = gameResult;
}

void AfterLevelOver::SetLevelFinished()
{
	FILE* rateFP = fopen(_rateFilePath.c_str(), "r");
	
	if(rateFP == NULL)
	{
		rateFP = fopen(_rateFilePath.c_str(), "w");
		fprintf(rateFP, "1");
		fflush(rateFP);
		fclose(rateFP);
	}
	else
	{
		int levelsPlayed = 0;
		fscanf(rateFP, "%d", &levelsPlayed);
		fclose(rateFP);

		if(levelsPlayed >= 0)
		{
			rateFP = fopen(_rateFilePath.c_str(), "w");
			fprintf(rateFP, "%d", (levelsPlayed+1) );
			fflush(rateFP);
			fclose(rateFP);

			if(levelsPlayed > 1 && levelsPlayed%15 == 0)
			{
				_rateMsgBox->SetActive(true);
			}
		}
	}
}

void AfterLevelOver::Draw()
{
	ColorTheme::Draw();

	if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Draw();
	}
	else
	{
		_homeBtn->Draw();
		_replayBtn->Draw();
		_shareBtn->Draw();
		_rateBtn->Draw();
		_leaderBoardBtn->Draw();
		_platNextBtn->Draw();

		if(_gameResult == WIN)
		{
			for(int  i=0; i<3; i++)
				_disableStars[i]->Draw();

			for(int  i=0; i<_currStars; i++)
			{
				if(_showOnlyGlow)
					_animStarsVec[i]->SetCurrFrameNum(1);

				_animStarsVec[i]->Draw();
			}
			
			int halfSW = GameInfo::GetInstance()->CodedW()/2;

			SaveManager* saveMgr = SaveManager::GetInstance();
			int currLevel = saveMgr->GetCurrLevel();
			int bestStars = saveMgr->GetNumStars(currLevel);
			int bestTime = saveMgr->GetTime(currLevel);
			int bestMoves = saveMgr->GetNumMoves(currLevel);
			
			string rankStr = "Rank";
			string movesStr = "Moves";
			string newRecordStr = "New Record";
			string bestRecordStr = "Best Record";
			
			{
				UIFont::GetInstance()->Begin(1);
				
				char rankArr[128];
				sprintf(rankArr, "%s : %d",rankStr.c_str(), _rank);
				UIFont::GetInstance()->SetColor(255,255,0,255);
				UIFont::GetInstance()->DrawFromCenter(rankArr, halfSW,128,46,0);

				if(bestStars == _currStars && bestTime == _currTime && bestMoves == _currMoves)
				{
					UIFont::GetInstance()->SetColor(0,255,0,255);
					UIFont::GetInstance()->DrawFromCenter(newRecordStr, halfSW,205,32,0);
				}

				UIFont::GetInstance()->SetColor(170,190,255,255);
				UIFont::GetInstance()->DrawFromCenter(GameInfo::GetInstance()->GetTimeStr(_currTime, "Time : ", ""), halfSW,245,28,1);

				char movesArr[128];
				sprintf(movesArr, "%s : %d",movesStr.c_str(), _currMoves); 			
				UIFont::GetInstance()->DrawFromCenter(movesArr, halfSW,284,28,0);
				UIFont::GetInstance()->End();

				if((bestStars == _currStars && bestTime == _currTime && bestMoves == _currMoves) == false)
				{
					char bestMovesArr[128];
					sprintf(bestMovesArr, "%s : %d", movesStr.c_str(), bestMoves); 

					int startY = 600;

					UIFont::GetInstance()->Begin(1);
					UIFont::GetInstance()->SetColor(0,255,0,255);
					UIFont::GetInstance()->DrawFromCenter(bestRecordStr, halfSW,startY,25,-2);
					UIFont::GetInstance()->SetColor(170,190,255,255);
					UIFont::GetInstance()->DrawFromCenter(GameInfo::GetInstance()->GetTimeStr(bestTime, "Time : ", ""), halfSW,startY+40,28,1);
					UIFont::GetInstance()->DrawFromCenter(bestMovesArr, halfSW,startY+80,28,1);
					UIFont::GetInstance()->End();
				}
			}
		}

		if(_msgBox && _msgBox->IsActive())
		{
			_msgBox->Draw();
		}
		else if(_rateMsgBox && _rateMsgBox->IsActive())
		{
			_rateMsgBox->Draw();

			int ow = GameInfo::GetInstance()->CodedW();
			int oh = GameInfo::GetInstance()->CodedH();

			UIFont::GetInstance()->SetColor(255,255,255,255);
			UIFont::GetInstance()->Begin(1);
			UIFont::GetInstance()->DrawFromCenter("Please take a moment to rate the game.", ow/2, oh/2 - 15, 27, -1);
			UIFont::GetInstance()->End();
		}
	}
}

AfterLevelOver::~AfterLevelOver()
{
	for(int i=0;i<3;i++)
	{
		if(_disableStars[i])
		{
			delete _disableStars[i];
			_disableStars[i] = NULL;
		}
	}

	for(int i=0; i<_animStarsVec.size();i++)
	{
		if(_animStarsVec[i])
		{
			delete _animStarsVec[i];
			_animStarsVec[i] = NULL;
		}
	}

	if(_platNextBtn)
	{
		delete _platNextBtn;
		_platNextBtn = NULL;
	}

	if(_leaderBoard)
	{
		delete _leaderBoard;
		_leaderBoard = NULL;
	}

	if(_leaderBoardBtn)
	{
		delete _leaderBoardBtn;
		_leaderBoardBtn = NULL;
	}

	if(_shareBtn)
	{
		delete _shareBtn;
		_shareBtn = NULL;
	}

	if(_rateBtn)
	{
		delete _rateBtn;
		_rateBtn = NULL;
	}

	if(_homeBtn)
	{
		delete _homeBtn;
		_homeBtn = NULL;
	}

	if(_replayBtn)
	{
		delete _replayBtn;
		_replayBtn = NULL;
	}

	if(_msgBox)
	{
		delete _msgBox;
		_msgBox = NULL;
	}

	if(_rateMsgBox)
	{
		delete _rateMsgBox;
		_rateMsgBox = NULL;
	}
}
