#include "TestScene.h"

#include "MapMovePlayer.h"
#include "CommonMacros.h"

int TestScene::Init()
{
	player = new MapMovePlayer(sceneName);
	player->Init(1, 1, 3, 3);

	return 0;
}

void TestScene::Release()
{
	SAFE_DELETE(player);
}

void TestScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

void TestScene::Render()
{
	__super::Render();
}
