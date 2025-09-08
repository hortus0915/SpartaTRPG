

#include "MinigameScene.h"
#include "../CommonManagers.h"

#include "../../../Red/MapData.h"
#include "../../MapMovePlayer.h"



int MinigameScene::Init()
{
    map = new MapData();
    player = new MapMovePlayer("MinigameScene", map);
    player->Init(WHITE, BLACK);
    return 0;
}

void MinigameScene::Release()
{
    SAFE_DELETE(player);
    SAFE_DELETE(map);
}

void MinigameScene::Update(float _deltaTime)
{
    __super::Update(_deltaTime);
}

void MinigameScene::Render()
{
    __super::Render();
}


