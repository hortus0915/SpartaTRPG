#include "MainGame.h"

#include "../Black/CommonMacros.h"
#include "Singletons/CommonManagers.h"

#include "DoubleBuffering.h"

#include "TestScene.h"

MainGame::MainGame(int _appX, int _appY, int _appWidth, int _appHeight, int _screenWidth, int _screenHeight)
	: doubleBuffer(nullptr)
{
	srand(GetTickCount64());

	screen.posX = _appX;
	screen.posY = _appY;

	screen.appWidth = _appWidth;
	screen.appHeight = _appHeight;

	screen.screenWidth = _screenWidth;
	screen.screenHeight = _screenHeight;

	backbuffer = nullptr;
}

MainGame::~MainGame()
{
	SAFE_RELEASE_DELETE(doubleBuffer);
}

void MainGame::Init()
{
	isGameRun = true;

	TIMEMANAGER->Init();
	SCENEMANAGER->Init(this);

	stringstream stream;
	string mode;

	stream << "mode con: cols=" << screen.appWidth << " lines=" << screen.appHeight << " | title " << TITLE;
	mode = stream.str();

	system(mode.c_str());

	SAFE_RELEASE_DELETE(doubleBuffer);
	doubleBuffer = new DoubleBuffering(screen.appWidth, screen.appHeight);

	if (backbuffer)
	{
		Release();
	}

	backbuffer = new char*[screen.screenHeight];
	for (int i = 0; i < screen.screenHeight; ++i)
	{
		backbuffer[i] = new char[screen.screenWidth + 2];
		backbuffer[i][screen.screenWidth + 1] = '\0';
	}
	BackbufferClear();

#pragma region Scene Test Code

	SCENEMANAGER->AddScene("TestScene", new TestScene("TestScene"));
	SCENEMANAGER->ChangeScene("TestScene");
	SCENEMANAGER->CurrentSceneInit();

#pragma endregion

}

void MainGame::Update(float _deltaTime)
{
	// test
	for (int i = 0; i < screen.screenHeight; ++i)
	{
		backbuffer[i][0] = '#';
		backbuffer[i][screen.screenWidth] = '#';
	}
	for (int i = 0; i < screen.screenWidth + 1; ++i)
	{
		backbuffer[0][i] = '#';
		backbuffer[screen.screenHeight - 1][i] = '#';
	}

	SCENEMANAGER->Update(_deltaTime);

	if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
	{
		MainGame::Quit();
	}
}

void MainGame::Release()
{
	for (int i = 0; i < screen.screenHeight; i++)
		SAFE_DELETE_ARR(backbuffer[i]);

	SAFE_DELETE_ARR(backbuffer)
}

void MainGame::Render()
{
	doubleBuffer->ClearBuffer();

	SCENEMANAGER->Render();

	DWORD dw;
	for (int i = 0; i < screen.screenHeight; ++i)
	{
		doubleBuffer->BufferWrite(0, i, backbuffer[i]);
	}

	BackbufferClear();
	doubleBuffer->BufferFlipping();
}

void MainGame::CopyToBackbuffer(const int& _posX, const int& _posY, const int& _width, const int& _height, char** contents)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			backbuffer[y + _posY][x + _posX] = contents[y][x];
		}
	}
}

void MainGame::BackbufferClear()
{
	for (int y = 0; y < screen.screenHeight; ++y)
	{
		for (int x = 0; x < screen.screenWidth + 1; ++x)
			backbuffer[y][x] = ' ';
	}
}
