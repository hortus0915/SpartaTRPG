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
}

iMapMovable::~iMapMovable()
{
	if (image)
	{
		Release();
	}
}

void iMapMovable::Init(int _startX, int _startY, Color _characterColor, Color _bgColor)
{
	SetPos(_startX, _startY);

	if (image)
	{
		Release();
	}

	image = new char* [MAX_SCREEN_HEIGTH];
	for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
	{
		image[i] = new char[MAX_SCREEN_WIDTH + 1];
		for (int j = 0; j < MAX_SCREEN_WIDTH; ++j)
			image[i][j] = ' ';
		image[i][MAX_SCREEN_WIDTH] = '\0';
	}

	mapData->CreateMap(MapType::Dungeon); 
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


	MapImageSet();
}

void iMapMovable::SetPos(int _posX, int _posY)
{
	if (!IsCanMove(_posX, _posY)) return;

	posX = _posX;
	posY = _posY;
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
}

bool iMapMovable::IsCanMove(int _targetX, int _targetY)
{
	if (_targetX < 0 || _targetX >= mapData->GetMapWidth())  return false;
	if (_targetY < 0 || _targetY >= mapData->GetMapHeight()) return false;

	auto mapInfo = mapData->GetMapInfo(_targetX, _targetY);

	if (mapInfo == TileType::Wall || mapInfo == TileType::Box)
		return false;

	return true;
}

void iMapMovable::Render()
{
	SCENEMANAGER->RenderToBackbuffer(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGTH, image, charColor, bgColor);
}
