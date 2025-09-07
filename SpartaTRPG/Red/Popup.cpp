#include "Popup.h"
#include "../Black/Singletons/CommonManagers.h"

void Popup::Update(float deltaTime)
{
}

void Popup::Render()
{
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2, MAPPOPUP_WIDTH, MAPPOPUP_HEIGHT, image);
}

Popup::Popup(string _targetSceneName)
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

void Popup::Release()
{
	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		SAFE_DELETE_ARR(image[i])
	}
	SAFE_DELETE_ARR(image)
}

void Popup::SetActive(bool active)
{
	isActive = active;
}

void Popup::Init()
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
