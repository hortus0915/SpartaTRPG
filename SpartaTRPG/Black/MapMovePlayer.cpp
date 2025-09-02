#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"

void MapMovePlayer::Init(int _startX, int _startY, int _width, int _height)
{
	__super::Init(_startX, _startY, _width, _height);

						image[0][1] = '*';

	image[1][0] = '*';	image[1][1] = 'O';	image[1][2] = '*';

						image[2][1] = '*';
}

void MapMovePlayer::Update(float deltaTime)
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		MoveTo(-1, 0);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		MoveTo(1, 0);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		MoveTo(0, -1);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		MoveTo(0, 1);
	}
}