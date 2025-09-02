#pragma once

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>

using namespace std;

class DoubleBuffering;

struct ScreenPoint
{
	int posX;
	int posY;

	int appWidth;
	int appHeight;

	int screenWidth;
	int screenHeight;
};

class MainGame
{
private:
	ScreenPoint screen;

	DoubleBuffering* doubleBuffer;

	char** backbuffer;

	bool isGameRun;

public:
	MainGame(int _appX, int _appY, int _appWidth, int _appHeight, int _screenWidth, int _screenHeight);
	~MainGame();

	void Init();
	void Update(float _deltaTime);
	void Release();
	void Render();

	void CopyToBackbuffer(const int& _posX, const int& _posY, const int& _width, const int& _height, char** contents);

	void BackbufferClear();

	inline bool IsGameRun() { return isGameRun; }
	inline void Quit() { isGameRun = false; }

	inline char** GetBackbuffer() { return backbuffer; }

};

