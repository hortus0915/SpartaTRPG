#include "DungeonScene.h"

#include "../../../Red/MapData.h"
#include "../../MapMovePlayer.h"
#include "../CommonManagers.h"

DungeonScene::DungeonScene(string _sceneName) : iScene(_sceneName)
{
	map = new MapData();
	player = new MapMovePlayer(sceneName, map);
	AddUpdatable(player);
	AddRenderable(player);
}

int DungeonScene::Init()
{
	player->Init(WHITE, BLACK);

	return 0;
}

void DungeonScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(map);
}

void DungeonScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

void DungeonScene::Render()
{
	__super::Render();
}
