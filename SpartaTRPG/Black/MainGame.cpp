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

#pragma region Scene Test Code

	SCENEMANAGER->AddScene("TestScene", new TestScene("TestScene"));
	SCENEMANAGER->ChangeScene("TestScene");
	SCENEMANAGER->CurrentSceneInit();

#pragma endregion

}

void MainGame::Update(float _deltaTime)
{
	SCENEMANAGER->Update(_deltaTime);

	if (KEYMANAGER->IsOnceKeyDown(VK_ESCAPE))
	{
		MainGame::Quit();
	}
}

void MainGame::Release()
{
}

void MainGame::Render()
{
	doubleBuffer->ClearBuffer();

	string sharp = "#";
	// test
	for (int i = 0; i < screen.screenHeight; ++i)
	{
		CopyToBackbuffer(0, i, sharp.size(), 1, &sharp);
		CopyToBackbuffer(screen.screenWidth, i, sharp.size(), 1, &sharp);
	}
	for (int i = 0; i < screen.screenWidth + 1; ++i)
	{
		CopyToBackbuffer(i, 0, sharp.size(), 1, &sharp);
		CopyToBackbuffer(i, screen.screenHeight - 1, sharp.size(), 1, &sharp);
	}

	SCENEMANAGER->Render();

	doubleBuffer->BufferFlipping();
}

void MainGame::CopyToBackbuffer(const int& _posX, const int& _posY, const int& _width, const int& _height, char** _contents, Color _fontColor, Color _bgColor)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			doubleBuffer->BufferWrite(x + _posX, y + _posY, (char*)&_contents[y][x], _fontColor, _bgColor);
		}
	}
}

void MainGame::CopyToBackbuffer(const int& _posX, const int& _posY, const int& _width, const int& _height, string* _contents, Color _fontColor, Color _bgColor)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			doubleBuffer->BufferWrite(x + _posX, y + _posY, (char*)&_contents[y][x], _fontColor, _bgColor);
		}
	}
}
