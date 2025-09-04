#include "GameScene.h"

#include "../CommonManagers.h"

int GameScene::Init()
{
    SCENEMANAGER->ChangeChild("BattleScene");
    SCENEMANAGER->CurrentSceneInit();

    return 0;
}

void GameScene::Release()
{
}
