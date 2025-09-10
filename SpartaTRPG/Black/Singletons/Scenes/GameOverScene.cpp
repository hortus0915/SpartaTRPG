#include "GameOverScene.h"

#include "../../CommonMacros.h"
#include "../../CommonFuncs.h"
#include "../CommonManagers.h"

#include "../../Image.h"

// -  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41
// 0     O  O  O  O  O  O  O                 O  O  O  O  O              O  O                 O  O        O  O  O  O  O  O  O  O  O
// 1  O                       O           O                 O           O     O           O     O        O                        
// 2  O                                   O                 O           O     O           O     O        O                        
// 3  O           O  O  O  O  O           O  O  O  O  O  O  O           O        O     O        O        O  O  O  O  O  O  O  O  O
// 4  O                       O        O                       O        O        O     O        O        O                        
// 5  O                       O        O                       O        O        O     O        O        O                        
// 6     O  O  O  O  O  O  O           O                       O        O           O           O        O  O  O  O  O  O  O  O  O
// 7                                                                                                                               
// 8     O  O  O  O  O  O  O           O                       O        O  O  O  O  O  O  O  O  O        O  O  O  O  O  O  O  O   
// 9  O                       O        O                       O        O                                O                       O
//11  O                       O        O                       O        O                                O                       O
//12  O                       O           O                 O           O  O  O  O  O  O  O  O  O        O  O  O  O  O  O  O  O   
//13  O                       O              O           O              O                                O                 O  	  
//14  O                       O                 O     O                 O                                O                    O  
//15     O  O  O  O  O  O  O                       O                    O  O  O  O  O  O  O  O  O        O                       O
// 

void GameOverScene::AddToVector(int _x, int _y)
{
	FramePoint p = { _x, _y };
	points.push_back(p);
}

void GameOverScene::Shuffle()
{
	for (int i = 0; i < 777; ++i)
	{
		int dst = GetIntRange(0, points.size() - 1);
		int src = GetIntRange(0, points.size() - 1);

		if (dst == src) continue;

		FramePoint temp = points[dst];
		points[dst] = points[src];
		points[src] = temp;
	}
}

int GameOverScene::Init()
{
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hWnd, &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	pic = new Image;
	pic->Init(TEXT("Image.bmp"), width / 2 - 293 / 2 - 71, height / 2 - 231 / 2 - 170);

	posX = MAX_SCREEN_WIDTH / 2 - 43 / 2;
	posY = MAX_SCREEN_HEIGTH / 2 - 15 / 2;

	frameDelayCount = 2;
	frameCount = 0;
	currentFrame = 0;
	
	origin[ 0] = " OOOOOOO     OOOOO    OO     OO  OOOOOOOOO";
	origin[ 1] = "O       O   O     O   O O   O O  O";
	origin[ 2] = "O           O     O   O O   O O  O";
	origin[ 3] = "O   OOOOO   OOOOOOO   O  O O  O  OOOOOOOOO";
	origin[ 4] = "O       O  O       O  O  O O  O  O";
	origin[ 5] = "O       O  O       O  O  O O  O  O";
	origin[ 6] = " OOOOOOO   O       O  O   O   O  OOOOOOOOO";
	origin[ 7] = "";
	origin[ 8] = " OOOOOOO   O       O  OOOOOOOOO  OOOOOOOO";
	origin[ 9] = "O       O  O       O  O          O       O";
	origin[10] = "O       O  O       O  O          O       O";
	origin[11] = "O       O   O     O   OOOOOOOOO  OOOOOOOO";
	origin[12] = "O       O    O   O    O          O     O";
	origin[13] = "O       O     O O     O          O      O";
	origin[14] = " OOOOOOO       O      OOOOOOOOO  O       O";

	if (points.size() <= 0)
	{
		for (int y = 0; y < 15; ++y)
		{
			for (int x = 0; x < origin[y].size(); ++x)
			{
				if (origin[y][x] == 'O')
				{
					AddToVector(x, y);
				}
			}
		}
	}

	Shuffle();

	image[ 0] = "                                           ";
	image[ 1] = "                                   ";
	image[ 2] = "                                   ";
	image[ 3] = "                                           ";
	image[ 4] = "                                   ";
	image[ 5] = "                                   ";
	image[ 6] = "                                           ";
	image[ 7] = "";
	image[ 8] = "                                          ";
	image[ 9] = "                                           ";
	image[10] = "                                           ";
	image[11] = "                                          ";
	image[12] = "                                         ";
	image[13] = "                                          ";
	image[14] = "                                           ";

	isDelayStart = false;
	delayTime = 2.0f;
	delayCurrentTime = 0.0f;
	isShowImage = false;

	return 0;
}

void GameOverScene::Release()
{
	SAFE_RELEASE_DELETE(pic);
}

void GameOverScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	if (currentFrame * 3 < points.size())
	{
		++frameCount;
		if (frameCount % frameDelayCount == 0)
		{
			frameCount = 0;

			for (int i = currentFrame * 3; i < currentFrame * 3 + 3; ++i)
			{
				if (i >= points.size()) break;

				image[points[i].y][points[i].x] = 'O';
			}

			++currentFrame;
		}
	}
	else
	{
		isDelayStart = true;
	}

	if (isDelayStart)
	{
		delayCurrentTime += _deltaTime;
		if (delayCurrentTime >= delayTime)
		{
			isShowImage = true;
		}
	}
}

void GameOverScene::Render()
{
	__super::Render();

	if (!isShowImage)
	{
		for (int i = 0; i < 15; ++i)
		{
			SCENEMANAGER->RenderToBackbuffer(posX, posY + i, image[i].size(), 1, image[i]);
		}
	}
	else
	{
		pic->Render();
	}
}
