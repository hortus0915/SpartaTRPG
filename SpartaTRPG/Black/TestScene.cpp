#include "TestScene.h"

#include "MapMovePlayer.h"
#include "CommonMacros.h"

#include "TextColors.h"
#include "../Red/MapData.h"

int TestScene::Init()
{
	map = new MapData();
	player = new MapMovePlayer(sceneName, map);
	player->Init(1, 1, WHITE, BLACK);

	return 0;
}

void TestScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(map);
}

void TestScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

void TestScene::Render()
{
	__super::Render();
}
