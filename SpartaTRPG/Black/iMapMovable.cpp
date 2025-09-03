#include "iMapMovable.h"

#include "Singletons/CommonManagers.h"
#include "CommonMacros.h"

#include <Windows.h>

iMapMovable::iMapMovable(string _targetSceneName)
	:
	image(nullptr),
	IUpdatable(_targetSceneName),
	IRenderable(_targetSceneName)
{
}

iMapMovable::~iMapMovable()
{
	if (image)
	{
		Release();
	}
}

void iMapMovable::Init(int _startX, int _startY, int _width, int _height, Color _characterColor, Color _bgColor)
{
	SetPos(_startX, _startY);

	info.width = _width;
	info.height = _height;

	if (image)
	{
		Release();
	}

	image = new char* [info.height];
	for (int i = 0; i < info.height; ++i)
	{
		image[i] = new char[info.width + 1];
		for (int j = 0; j < info.width; ++j)
			image[i][j] = ' ';

		image[i][info.width] = '\0';
	}

	charColor = _characterColor;
	bgColor = _bgColor;
}

void iMapMovable::Release()
{
	for (int i = 0; i < info.height; ++i)
	{
		SAFE_DELETE_ARR(image[i])
	}
	SAFE_DELETE_ARR(image)
}

void iMapMovable::MoveTo(int deltaX, int deltaY)
{
	if (!IsCanMove(info.posX + deltaX, info.posY + deltaY)) return;

	info.posX += deltaX;
	info.posY += deltaY;
}

void iMapMovable::SetPos(int posX, int posY)
{
	if (!IsCanMove(posX, posY)) return;

	info.posX = posX;
	info.posY = posY;
}

bool iMapMovable::IsCanMove(int _targetX, int _targetY)
{
	if (_targetX < 0 || _targetX + info.width  >= MAX_SCREEN_WIDTH)  return false;
	if (_targetY < 0 || _targetY + info.height >= MAX_SCREEN_HEIGTH) return false;

	return true;
}

void iMapMovable::Render()
{
	SCENEMANAGER->RenderToBackbuffer(info.posX, info.posY, info.width, info.height, image, charColor, bgColor);
}
