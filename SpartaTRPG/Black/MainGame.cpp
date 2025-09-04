#include "MainGame.h"

#include "../Black/CommonMacros.h"
#include "Singletons/CommonManagers.h"

#include "DoubleBuffering.h"

#include "Singletons/EffectType.h"

#include "Singletons/Scenes.h"

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

#pragma endregion

	SCENEMANAGER->AddScene("TitleScene", new TitleScene("TitleScene"));

	SCENEMANAGER->AddScene("GameScene",  new GameScene ("GameScene"));
	//SCENEMANAGER->AddChild("GameScene", "TownScene",    new TownScene   ("TownScene"));
	SCENEMANAGER->AddChild("GameScene", "DungeonScene", new DungeonScene("DungeonScene"));
	SCENEMANAGER->AddChild("GameScene", "BattleScene",  new BattleScene ("BattleScene"));
	SCENEMANAGER->AddChild("GameScene", "MinigameScene",new MinigameScene("MinigameScene"));

	SCENEMANAGER->ChangeScene("TitleScene");
}

void MainGame::Update(float _deltaTime)
{
	SCENEMANAGER->Update(_deltaTime);
	EFFECTMANAGER->Update(_deltaTime);

	if (KEYMANAGER->IsOnceKeyDown('A'))
	{
		EFFECTMANAGER->StartEffect(Explosion, MAX_SCREEN_WIDTH / 2, MAX_SCREEN_HEIGTH / 2);
	}

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
	EFFECTMANAGER->Render();

	doubleBuffer->BufferFlipping();
}

void MainGame::CopyToBackbuffer(const int& _posX, const int& _posY, const int& _width, const int& _height, char** _contents, Color _fontColor, Color _bgColor)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			if (_contents[y][x] == EFFECT_NULL_CHAR)
			{
				_contents[y][x] = ' ';
				doubleBuffer->BufferWrite(x + _posX, y + _posY, (char*)&_contents[y][x], ORIGINCOLOR, BLACK);
			}
			else
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
			if (_contents[y][x] == EFFECT_NULL_CHAR)
			{
				_contents[y][x] = ' ';
				doubleBuffer->BufferWrite(x + _posX, y + _posY, (char*)&_contents[y][x], ORIGINCOLOR, BLACK);
			}
			else
				doubleBuffer->BufferWrite(x + _posX, y + _posY, (char*)&_contents[y][x], _fontColor, _bgColor);
		}
	}
}
