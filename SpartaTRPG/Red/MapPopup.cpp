#include "MapPopup.h"
#include "../Black/Singletons/CommonManagers.h"

void MapPopup::Update(float deltaTime)
{
}

void MapPopup::Render()
{
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2, MAPPOPUP_WIDTH, MAPPOPUP_HEIGHT, image);
	SelectRender();
}

void MapPopup::SelectRender()
{
	string yes = "¾È³çÇÏ¼¼¿ä";
	string no = "[no ]";
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 12, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, yes.size(), 1, &yes);
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 44, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, no.size(), 1, &no);
	string temp = "   \n";

	if (isSelect)
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 13, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, &temp, GREEN, GREEN);
	else
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 45, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, &temp, RED, RED);
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

int MapPopup::SetActive(TileType tileType)
{
	isSelect = false;
	switch (tileType)
	{
	case Empty:
	case Wall:
	case Box:
	case Shop:
		isActive = false;
		return 0;
	case Monster:
	case MonsterActiveRange:
		isActive = false;
		return -1;
	case Exit:
	case BoxActive:
	case Key:
	case ShopActiveRange:
	case DungeonIn:
		isActive = true;
		return 1;
	default:
		return 0;
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
