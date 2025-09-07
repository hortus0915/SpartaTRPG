#include "MinigameScene.h"
#include "../CommonManagers.h"
int MinigameScene::Init()
{
    SCENEMANAGER->ChangeChild("QuizScene");
    SCENEMANAGER->CurrentSceneInit();
    return 0;
}

void MinigameScene::Release()
{
}
