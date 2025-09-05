#include "iMapMovable.h"

#include "Singletons/CommonManagers.h"
#include "CommonMacros.h"
#include "../Red/MapData.h"

#include <Windows.h>

iMapMovable::iMapMovable(string _targetSceneName, MapData* _mapData)
	:
	image(nullptr),
	IUpdatable(_targetSceneName),
	IRenderable(_targetSceneName)
{
	mapData = _mapData;
	posX = 1;
	posY = 1;
}

iMapMovable::~iMapMovable()
{
	if (image)
	{
		Release();
	}
}

void iMapMovable::Init(Color _characterColor, Color _bgColor)
{
	if (image == nullptr)
	{
		image = new char* [MAX_SCREEN_HEIGTH];
		for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
		{
			image[i] = new char[MAX_SCREEN_WIDTH + 1];
			for (int j = 0; j < MAX_SCREEN_WIDTH; ++j)
				image[i][j] = ' ';
			image[i][MAX_SCREEN_WIDTH] = '\0';
		}

		mapData->CreateMap(MapType::Village);
	}

	MapImageSet();
	charColor = _characterColor;
	bgColor = _bgColor;
}

void iMapMovable::Release()
{
	for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
	{
		SAFE_DELETE_ARR(image[i])
	}
	SAFE_DELETE_ARR(image)
}

void iMapMovable::MoveTo(int deltaX, int deltaY)
{
	if (!IsCanMove(posX + deltaX, posY + deltaY)) return;

	posX += deltaX;
	posY += deltaY;

	SOUNDMANAGER->PlaySfx(Text("RunSound.wav"), 0.1f);
	MapImageSet();
}

void iMapMovable::SetPos(int _posX, int _posY)
{
	if (!IsCanMove(_posX, _posY)) return;

	posX = _posX;
	posY = _posY;

	MapImageSet();
}

void iMapMovable::MapImageSet()
{
	for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
	{
		for (int j = 0; j < MAX_SCREEN_WIDTH; ++j)
		{
			int harfX = MAX_SCREEN_WIDTH / 2;
			int harfY = MAX_SCREEN_HEIGTH / 2;

			if (i == 0 || i == MAX_SCREEN_HEIGTH - 1 || j == 0 || j == MAX_SCREEN_WIDTH - 1)
				image[i][j] = '#';
			else if (j == harfX && i == harfY)
				image[i][j] = 'O';
			else
			{
				int mapX = posX - ((MAX_SCREEN_WIDTH) / 2 - j + 1);
				int mapY = posY - ((MAX_SCREEN_HEIGTH) / 2 - i + 1);

				image[i][j] = mapData->GetMapData(mapX + 1, mapY + 1);
			}
		}
		image[i][MAX_SCREEN_WIDTH] = '\0';
	}
	isNewRender = true;
}

bool iMapMovable::IsCanMove(int _targetX, int _targetY)
{
	if (_targetX < 0 || _targetX >= mapData->GetMapWidth())  return false;
	if (_targetY < 0 || _targetY >= mapData->GetMapHeight()) return false;

	auto mapInfo = mapData->GetMapInfo(_targetX, _targetY);

	if (mapInfo == TileType::Wall || mapInfo == TileType::Box || mapInfo == TileType::Shop)
		return false;

	return true;
}

void iMapMovable::Render()
{
	SCENEMANAGER->RenderToBackbuffer(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGTH, image, charColor, bgColor);
}
