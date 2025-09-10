#include "GameScene.h"

#include "../CommonManagers.h"

int GameScene::Init()
{
    SCENEMANAGER->ChangeChild("DungeonScene");
    SCENEMANAGER->CurrentSceneInit();

    return 0;
}

void GameScene::Release()
{
}
