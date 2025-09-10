#include "GameOverScene.h"

#include "../../CommonMacros.h"
#include "../../CommonFuncs.h"
#include "../CommonManagers.h"

#include "../../Image.h"

#include "../../MainGame.h"
#include "../../DoubleBuffering.h"

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

	int screenWidth = rc.right - rc.left;
	int screenHeight = rc.bottom - rc.top;

	black.resize(4);
	black[0] = new Image;
	black[0]->Init(TEXT("black_0.bmp"), screenWidth - 50 - 52, 250);
	black[1] = new Image;
	black[1]->Init(TEXT("black_1.bmp"), screenWidth - 50 - 52, 250);
	black[2] = new Image;
	black[2]->Init(TEXT("black_2.bmp"), screenWidth - 50 - 52, 250);
	black[3] = new Image;
	black[3]->Init(TEXT("black_3.bmp"), screenWidth - 50 - 52, 250);

	red.resize(4);
	red[0] = new Image;
	red[0]->Init(TEXT("red_0.bmp"), screenWidth - 50 - 52, 50);
	red[1] = new Image;
	red[1]->Init(TEXT("red_1.bmp"), screenWidth - 50 - 52, 50);
	red[2] = new Image;
	red[2]->Init(TEXT("red_2.bmp"), screenWidth - 50 - 52, 50);
	red[3] = new Image;
	red[3]->Init(TEXT("red_3.bmp"), screenWidth - 50 - 52, 50);

	blue.resize(4);
	blue[0] = new Image;
	blue[0]->Init(TEXT("blue_0.bmp"), 50, 50);
	blue[1] = new Image;
	blue[1]->Init(TEXT("blue_1.bmp"), 50, 50);
	blue[2] = new Image;
	blue[2]->Init(TEXT("blue_2.bmp"), 50, 50);
	blue[3] = new Image;
	blue[3]->Init(TEXT("blue_3.bmp"), 50, 50);

	yellow.resize(4);
	yellow[0] = new Image;
	yellow[0]->Init(TEXT("yellow_0.bmp"), 50, 250);
	yellow[1] = new Image;
	yellow[1]->Init(TEXT("yellow_1.bmp"), 50, 250);
	yellow[2] = new Image;
	yellow[2]->Init(TEXT("yellow_2.bmp"), 50, 250);
	yellow[3] = new Image;
	yellow[3]->Init(TEXT("yellow_3.bmp"), 50, 250);




	animFrameDelayCount = 5;
	animFrameCount = 0;
	currentAnimIndex = 0;

	pinkPosX = GetIntRange(100, 500);
	pinkPosY = GetIntRange(300, 500);
	pinkTeleportDelayCount = 100;
	pinkTeleportCount = 0;
	currentPinkIndex = 0;

	pink.resize(8);
	pink[0] = new Image;
	pink[0]->Init(TEXT("pink_0.bmp"), pinkPosX, pinkPosY);
	pink[1] = new Image;
	pink[1]->Init(TEXT("pink_1.bmp"), pinkPosX, pinkPosY);
	pink[2] = new Image;
	pink[2]->Init(TEXT("pink_2.bmp"), pinkPosX, pinkPosY);
	pink[3] = new Image;
	pink[3]->Init(TEXT("pink_3.bmp"), pinkPosX, pinkPosY);
	pink[4] = new Image;
	pink[4]->Init(TEXT("pink_4.bmp"), pinkPosX, pinkPosY);
	pink[5] = new Image;
	pink[5]->Init(TEXT("pink_5.bmp"), pinkPosX, pinkPosY);
	pink[6] = new Image;
	pink[6]->Init(TEXT("pink_6.bmp"), pinkPosX, pinkPosY);
	pink[7] = new Image;
	pink[7]->Init(TEXT("pink_7.bmp"), pinkPosX, pinkPosY);

	return 0;
}

void GameOverScene::Release()
{
	SAFE_RELEASE_DELETE(pic);

	for (int i = 0; i < black.size(); ++i)
	{
		SAFE_DELETE(black[i]);
		SAFE_DELETE(red[i]);
		SAFE_DELETE(blue[i]);
		SAFE_DELETE(yellow[i]);
	}
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

	if (isShowImage)
	{
		++animFrameCount;
		if (animFrameCount % animFrameDelayCount == 0)
		{
			animFrameCount = 0;

			currentAnimIndex = (currentAnimIndex + 1) % black.size();
			currentPinkIndex = (currentPinkIndex + 1) % pink.size();
		}

		++pinkTeleportCount;
		if (pinkTeleportCount % pinkTeleportDelayCount == 0)
		{
			SCENEMANAGER->GetMainGame()->ClearBuffer();

			pinkPosX = GetIntRange(100, 500);
			pinkPosY = GetIntRange(300, 500);

			for (int i = 0; i < pink.size(); ++i)
				pink[i]->SetPos(pinkPosX, pinkPosY);

			SCENEMANAGER->GetMainGame()->BufferFlip();
		}

		if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			SCENEMANAGER->ChangeScene("TitleScene");
			SCENEMANAGER->CurrentSceneInit();
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

		black[currentAnimIndex]->Render();
		red[currentAnimIndex]->Render();
		blue[currentAnimIndex]->Render();
		yellow[currentAnimIndex]->Render();
		pink[currentPinkIndex]->Render();
	}
}
