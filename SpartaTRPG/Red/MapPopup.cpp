#include "MapPopup.h"
#include "../Black/Singletons/CommonManagers.h"

void MapPopup::Update(float deltaTime)
{
}

void MapPopup::Render()
{
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2, MAPPOPUP_WIDTH, MAPPOPUP_HEIGHT, image);
	string test = "   \n";
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 15, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, &test, GREEN, GREEN);
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 45, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, &test, RED, RED);
}

MapPopup::MapPopup(string _targetSceneName)
	:
	IUpdatable(_targetSceneName),
	IRenderable(_targetSceneName)
{
	image = new char* [MAPPOPUP_HEIGHT];
	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		image[i] = new char[MAPPOPUP_WIDTH + 1];
		for (int j = 0; j < MAPPOPUP_WIDTH; ++j)
		{
			if (i == 0 || j == 0 || i == MAPPOPUP_HEIGHT - 1 || j == MAPPOPUP_WIDTH - 1)
				image[i][j] = '#';
			else
				image[i][j] = ' ';
		}
		image[i][MAPPOPUP_WIDTH] = '\0';
	}
}

void MapPopup::Release()
{
	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		SAFE_DELETE_ARR(image[i])
	}
	SAFE_DELETE_ARR(image)
}

void MapPopup::SetActive(TileType tileType)
{
	switch (tileType)
	{
	case Empty:
	case Wall:
	case Box:
	case Shop:
	case Monster:
		isActive = false;
		break;
	case Exit:
		isActive = true;
		break;
	case BoxActive:
		isActive = true;
		break;
	case Key:
		isActive = true;
		break;
	case MonsterActiveRange:
		isActive = true;
		break;
	case ShopActiveRange:
		isActive = true;
		break;
	case DungeonIn:
		isActive = true;
		break;
	default:
		break;
	}

}


void MapPopup::Init()
{
	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAPPOPUP_WIDTH; ++j)
		{
			if (i == 0 || j == 0 || i == MAPPOPUP_HEIGHT - 1 || j == MAPPOPUP_WIDTH - 1)
				image[i][j] = '#';
			else
				image[i][j] = ' ';
		}
		image[i][MAPPOPUP_WIDTH] = '\0';
	}
}
