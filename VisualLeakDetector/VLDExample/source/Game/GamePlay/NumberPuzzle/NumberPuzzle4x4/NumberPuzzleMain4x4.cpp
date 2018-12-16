#include "NumberPuzzleMain4x4.h"
#include "Input.h"
#include "GameInfo.h"
#include "ModuleManager.h"
#include "SaveManager.h"
#include "UIFont.h"
#include "Utils.h"
#include "Localize.h"
#include "ColorTheme.h"

NumberPuzzleMain4x4::NumberPuzzleMain4x4()
{
	int levelNum = SaveManager::GetInstance()->GetCurrLevel();

	int ow = GameInfo::GetInstance()->CodedW();
	int oh = GameInfo::GetInstance()->CodedH();

	float timerBgW = ow*0.85;
	float timerBgH = oh*0.04;

	float timerX = (ow-timerBgW)/2.0f;
	float timerY = oh-timerBgH-oh*0.039 + 35;

	_timerBarBgImg = new Sprite("numberpuzzle/progressbar.png",timerX, timerY, timerBgW, timerBgH);
	_timerBarBgImg->SetUVBounds0To1(0, 0, 611.0f/1024.0f, 44.0f/64.0f);

	_timerBarFillImg = new Sprite("numberpuzzle/progressbar.png", _timerBarBgImg->GetX()+8, _timerBarBgImg->GetY()+10, 0,15);
	_timerBarFillImg->SetUVBounds0To1(611.0f/1024.0f, 0, 22.0f/1024.0f, 22.0f/64.0f);

	_timer100PercentW = _timerBarBgImg->GetWidth() - 8*2;

	_isShowingPic = false;
	_showGlowEffect = false;
	_glowTime = 0.0f;
	_glowOnOffCount = 0;
	_playTimeCount = 0.0f;
	_numMoves = 0;

	_afterLevelOver = new AfterLevelOver();
	_pauseScreen =  new PauseScreen();
	_leaderBoard = new LeaderBoard();

	int btnW = 110;
	int btnH = 55;
	int hGap = 25;

	_pauseBtn = new ButtonNew("Pause",		0,(btnH+hGap) * 0,btnW,btnH,ButtonNew::COLOR_EMPTY);
	_homeBtn = new ButtonNew("Home",		0,(btnH+hGap) * 1,btnW,btnH,ButtonNew::COLOR_EMPTY);
	_replayBtn = new ButtonNew("Replay",	0,(btnH+hGap) * 2,btnW,btnH,ButtonNew::COLOR_EMPTY);
	_leaderBtn = new ButtonNew("HiScores",	0,(btnH+hGap) * 3,btnW,btnH,ButtonNew::COLOR_EMPTY);
	_picBtn = new ButtonNew("", 0,(btnH+hGap) * 6,btnW,btnH+25,ButtonNew::COLOR1);

	float percentVal = 0.43;
	_pauseBtn->SetFontSizeInPercent(percentVal);
	_homeBtn->SetFontSizeInPercent(percentVal);
	_replayBtn->SetFontSizeInPercent(percentVal);
	_leaderBtn->SetFontSizeInPercent(percentVal);
	_picBtn->SetFontSizeInPercent(percentVal);

	_activeGrid = NULL;
	_prevX = 0;
	_prevY = 0;


	int arr[25];
	
	int numXGrids = 4;

	if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_3x3)
	{
		numXGrids = 3;
		GetLevelData_Num3x3(levelNum, arr);
	}
	else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_4x4)
	{
		numXGrids = 4;
		GetLevelData_Num4x4(levelNum, arr);
	}
	else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_5x5)
	{
		numXGrids = 5;
		GetLevelData_Num5x5(levelNum, arr);
	}

	_numGridsManager = new NumGridsManager(numXGrids, arr);
}

void NumberPuzzleMain4x4::Update()
{
	if(_pauseScreen && _pauseScreen->IsActive())
	{
		_pauseScreen->Update();
	}
	else if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Update();
	}
	else if(_afterLevelOver && _afterLevelOver->IsActive())
	{
		_afterLevelOver->Update();
	}
	else
	{
		_homeBtn->Update();
		_replayBtn->Update();
		_pauseBtn->Update();
		_leaderBtn->Update();
		_picBtn->Update();

		//if(Input::IsBackPressed())
		//{
		//	PagesManager::GetInstance()->SetCurrPage(PagesManager::LEVEL_SELECTOR);
		//	ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);
		//}
		//else 
			if(_homeBtn->IsClicked())
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
		else if(_pauseBtn->IsClicked())
		{
			if(_pauseScreen)
				_pauseScreen->SetActive(true);
		}
		else if(_leaderBtn->IsClicked())
		{
			if(_leaderBoard)
				_leaderBoard->SetActive(true);
		}
		else if(_picBtn->IsClicked() && _activeGrid == NULL)
		{
			_isShowingPic = !_isShowingPic;			
			_numGridsManager->ShowFinalImg(_isShowingPic);
		}
		else
		{
			RunGamePlay();
		}
	}
}

void NumberPuzzleMain4x4::RunGamePlay()
{
	if(_showGlowEffect)
	{
		_glowTime += GameInfo::deltaTime;

		if(_glowTime >= 0.20)
		{
			_glowTime = 0.0f;
			_numGridsManager->Glow(true);
			_glowOnOffCount++;

			if(_glowOnOffCount > 4)
			{
				_showGlowEffect = false;
				_afterLevelOver->SetActive(true);
			}
		}
	}
	else
	{
		//LevelGen();
		//return;

		_playTimeCount += GameInfo::deltaTime;

		if(_isShowingPic)
		{

		}
		else
		{
			_numGridsManager->Update(GameInfo::deltaTime);

			float totLevels = (float)SaveManager::GetInstance()->GetNumTotalLevels();
			float timerCurrW = (SaveManager::GetInstance()->GetTotalLevelsPlayed()) * _timer100PercentW / totLevels;
			_timerBarFillImg->SetWidth(timerCurrW);

			if(Input::IsMouseClicked())
			{
				NumberGrid* numberGrid = _numGridsManager->GetGrid(Input::MouseX, Input::MouseY);
					
				if(numberGrid)
				{
					_activeGrid = numberGrid;
					_prevX = _activeGrid->GetX();
					_prevY = _activeGrid->GetY();
				}
			}
			
			if(_activeGrid && Input::IsMousePressed())
			{
				int dx = Input::PrevMouseX - Input::MouseX;
				int dy = Input::PrevMouseY - Input::MouseY;

				_activeGrid->SetX(_activeGrid->GetX() - dx);
				_activeGrid->SetY(_activeGrid->GetY() - dy);
			}

			if(_activeGrid && Input::IsMouseReleased())
			{
				NumberGrid* grid = _numGridsManager->GetIntersectGrid(_activeGrid);

				if(grid == NULL)
				{
					_activeGrid->SetX(_prevX);
					_activeGrid->SetY(_prevY);
					_activeGrid = NULL;
				}
				else
				{
					_activeGrid->SetX(grid->GetX());
					_activeGrid->SetY(grid->GetY());

					grid->SetX(_prevX);
					grid->SetY(_prevY);

					_activeGrid = NULL;

					_numMoves++;
				}
			}

			if(_numGridsManager->IsInCorrectOrder())
			{
				//_playTimeCount = 56;		//hack...
				//_numMoves = 120;			//hack...

				_showGlowEffect = true;
				_numGridsManager->Glow(true);
				SaveStatus();
			}
		}

		if(Input::IsBackPressed())
		{
			PagesManager::GetInstance()->SetCurrPage(PagesManager::LEVEL_SELECTOR);
			ModuleManager::GetInstance()->SetModule(ModuleManager::PAGES);

			//hack...

			//_playTimeCount = 35;
			//_numMoves = 120;

			//_showGlowEffect = true;
			//_numGridsManager->Glow(true);
			//SaveStatus();
		}
	}
}

void NumberPuzzleMain4x4::SaveStatus()
{
	int numStars = 0;

	float factor = 1;
	
	if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_3x3)
		factor = 6.0f/15.0f;
	else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_4x4)
		factor = 15.0f/15.0f;
	else if(SaveManager::GetInstance()->GetGameID() == SaveManager::NUM_5x5)
		factor = 30.0f/15.0f;
	
	if(_playTimeCount < 30.0f*factor)									numStars = 3;
	else if(_playTimeCount < 2*40.0f*factor && _numMoves < 200*factor)	numStars = 2;
	else if(_playTimeCount < 4*40.0f*factor && _numMoves < 350*factor)	numStars = 1;
	

	SaveManager* saveMgr = SaveManager::GetInstance();

	if(saveMgr->GetCurrLevel() == saveMgr->GetLastUnlockedLevel())
	{
		saveMgr->SetNumStars(numStars, SaveManager::GetInstance()->GetCurrLevel());
		saveMgr->SetNumMoves(_numMoves, SaveManager::GetInstance()->GetCurrLevel());
		saveMgr->SetTime((int)_playTimeCount, SaveManager::GetInstance()->GetCurrLevel());
	}
	else
	{
		int bestStars = saveMgr->GetNumStars(saveMgr->GetCurrLevel());
		int bestTime = saveMgr->GetTime(saveMgr->GetCurrLevel());
		int bestMoves = saveMgr->GetNumMoves(saveMgr->GetCurrLevel());

		if(numStars > bestStars || (numStars == bestStars && (int)_playTimeCount < bestTime) || (numStars == bestStars && (int)_playTimeCount == bestTime && _numMoves < bestMoves))
		{
			saveMgr->SetNumStars(numStars, SaveManager::GetInstance()->GetCurrLevel());
			saveMgr->SetNumMoves(_numMoves, SaveManager::GetInstance()->GetCurrLevel());
			saveMgr->SetTime((int)_playTimeCount, SaveManager::GetInstance()->GetCurrLevel());
		}
	}

	if(saveMgr->GetCurrLevel() > saveMgr->GetTotalLevelsPlayed())
		saveMgr->SetLastUnlockedLevel(saveMgr->GetCurrLevel() + 1);
	
	saveMgr->SaveGame();

	//Don't Activate AfterLevelOver Screen here, just fill the data...
	_afterLevelOver->SetGameResult(AfterLevelOver::WIN);
	_afterLevelOver->SetCurrStars(numStars);
	_afterLevelOver->SetCurrTime(_playTimeCount);
	_afterLevelOver->SetCurrMoves(_numMoves);
}

void NumberPuzzleMain4x4::Draw()
{
	if(_pauseScreen && _pauseScreen->IsActive())
	{
		_pauseScreen->Draw();
	}
	else if(_leaderBoard && _leaderBoard->IsActive())
	{
		_leaderBoard->Draw();
	}
	else if(_afterLevelOver && _afterLevelOver->IsActive())
	{
		_afterLevelOver->Draw();
	}
	else
	{
		ColorTheme::Draw();
		
		_homeBtn->Draw();
		_replayBtn->Draw();
		_pauseBtn->Draw();
		_leaderBtn->Draw();
		_picBtn->Draw();

		_numGridsManager->Draw(_activeGrid);

		//_timerBarBgImg->Draw();
		//_timerBarFillImg->Draw();

		char movesArr[128];
		sprintf(movesArr, "%d",_numMoves); 

		char unlockArr[128];
		sprintf(unlockArr, "Levels Completed : %d / %d",SaveManager::GetInstance()->GetTotalLevelsPlayed(), SaveManager::GetInstance()->GetNumTotalLevels());

		UIFont::GetInstance()->SetColor(255,255,255,255);
		UIFont::GetInstance()->Begin(1);

		UIFont::GetInstance()->Draw("Moves", 20,330,25,0,0);
		UIFont::GetInstance()->DrawFromCenter(movesArr, 52,365,25,0);

		UIFont::GetInstance()->Draw("Time", 20,400,25,0,0);
		UIFont::GetInstance()->Draw(GameInfo::GetInstance()->GetTimeStr((int)_playTimeCount, "", ""), 2,425,25,0,0);

		UIFont::GetInstance()->SetColor(110,255,250,255);
		UIFont::GetInstance()->Draw(unlockArr, 50,765,30,0,15);

		if(_isShowingPic)
		{
			UIFont::GetInstance()->DrawFromCenter("Hide", 55,505,25,0);
			UIFont::GetInstance()->DrawFromCenter("Picture",55,535,25,0);
		}
		else
		{
			UIFont::GetInstance()->DrawFromCenter("Show", 55,505,25,0);
			UIFont::GetInstance()->DrawFromCenter("Picture",55,535,25,0);
		}

		UIFont::GetInstance()->End();
	}
}

NumberPuzzleMain4x4::~NumberPuzzleMain4x4()
{
	if(_pauseScreen)
	{
		delete _pauseScreen;
		_pauseScreen = NULL;
	}
	if(_afterLevelOver)
	{
		delete _afterLevelOver;
		_afterLevelOver = NULL;
	}
	if(_leaderBoard)
	{
		delete _leaderBoard;
		_leaderBoard = NULL;
	}
	if(_timerBarBgImg)
	{
		delete _timerBarBgImg;
		_timerBarBgImg = NULL;
	}
	if(_timerBarFillImg)
	{
		delete _timerBarFillImg;
		_timerBarFillImg = NULL;
	}
	if(_numGridsManager)
	{
		delete _numGridsManager;
		_numGridsManager = NULL;
	}

	if(_leaderBtn)
	{
		delete _leaderBtn;
		_leaderBtn = NULL;
	}
	if(_pauseBtn)
	{
		delete _pauseBtn;
		_pauseBtn = NULL;
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
}

void NumberPuzzleMain4x4::LevelGen()
{	
	char arr[256];
	sprintf(arr, "NewLevels3x3.txt");
	FILE* fp = fopen(arr, "w");

	for(int out = 0; out<=100; out++)
	{
		for(int loop = 0; loop <= 1000; loop++)
		{
			int numXGrids = 3;
			int totGrids = (numXGrids*numXGrids) - 1;

			int direction = NumberGrid::NONE;

			do{
				NumberGrid* numberGrid = _numGridsManager->GetGridByIndex(rand()%totGrids);
				
				if(numberGrid)
				{
					direction = _numGridsManager->GetEmptySpaceDirection(numberGrid);
					if(direction != NumberGrid::NONE)
					{
						numberGrid->Move(direction);
					}
				}
			}while(direction == NumberGrid::NONE);


			if(loop == 1000)
			{
				int screenW = GameInfo::GetInstance()->CodedW();

				int count = 0;
				int minusCount = 0;

				int drawWidth = 0;
				int drawHeight = 0;
				int initX = 0;
				int initY = 0;

				if(numXGrids == 3)
				{
					drawWidth = 140;
					drawHeight = 140;
					initX = (screenW - drawWidth*numXGrids)/2;
					initY = 225;
				}
				else if(numXGrids == 4)
				{
					drawWidth = 120;
					drawHeight = 120;
					initX = (screenW - drawWidth*numXGrids)/2;
					initY = 205;
				}
				else
				{
					drawWidth = 95;
					drawHeight = 95;
					initX = (screenW - drawWidth*numXGrids)/2;
					initY = 190;
				}

				fprintf(fp, "{");

				for(int row=0;row<numXGrids;row++)
				{
					for(int col=0;col<numXGrids;col++)
					{
						int x = initX + col*drawWidth + drawWidth/2;
						int y = initY + row*drawHeight + drawHeight/2;

						int index = _numGridsManager->GetGridIndex( _numGridsManager->GetGrid(x, y) );

						if(index >= 0)
						{
							if(count == 0)
								fprintf(fp, "%d", (index+1));
							else
								fprintf(fp, ",%d", (index+1));

							fflush(fp);

							count++;
							if(count >= totGrids)
								break;
						}
						else
						{
							minusCount++;

							if(minusCount == 2)
								printf("abc");
						}
					}

					if(count >= totGrids)
						break;
				}

				fprintf(fp, "},\n");
				fflush(fp);				
			}
		}
	}
}

void NumberPuzzleMain4x4::GetLevelData_Num3x3(int levelNum, int* arr)
{
	int num = 9;

	for(int i=0;i<num;i++)
		arr[i] = i+1;

	int limit = 50 + rand()%100;

	for(int i=0;i<limit;i++)
	{
		int randIndex1 = rand() % num;
		int randIndex2 = rand() % num;

		int temp = arr[randIndex1];
		arr[randIndex1] = arr[randIndex2];
		arr[randIndex2] = temp; 
	}
}


void NumberPuzzleMain4x4::GetLevelData_Num4x4(int levelNum, int* arr)
{
	int num = 16;

	for(int i=0;i<num;i++)
		arr[i] = i+1;

	int limit = 50 + rand()%100;

	for(int i=0;i<limit;i++)
	{
		int randIndex1 = rand() % num;
		int randIndex2 = rand() % num;

		int temp = arr[randIndex1];
		arr[randIndex1] = arr[randIndex2];
		arr[randIndex2] = temp; 
	}
}

void NumberPuzzleMain4x4::GetLevelData_Num5x5(int levelNum, int* arr)
{
	int num = 25;

	for(int i=0;i<num;i++)
		arr[i] = i+1;

	int limit = 50 + rand()%100;

	for(int i=0;i<limit;i++)
	{
		int randIndex1 = rand() % num;
		int randIndex2 = rand() % num;

		int temp = arr[randIndex1];
		arr[randIndex1] = arr[randIndex2];
		arr[randIndex2] = temp; 
	}
}