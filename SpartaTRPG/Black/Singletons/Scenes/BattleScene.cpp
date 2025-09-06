#include "BattleScene.h"

#include "../CommonManagers.h"

#include <sstream>
using namespace std;

#include "../../PlayerInfo.h"
#include "../../EnemyInfoBase.h"

int BattleScene::Init()
{
    SOUNDMANAGER->ChangeBGM(Text("BattleSceneBGM.mp3"), 100);

    return 0;
}

void BattleScene::Release()
{
}

void BattleScene::Update(float _deltaTime)
{
    __super::Update(_deltaTime);


}

void BattleScene::Render()
{
    __super::Render();


    string temp = "이곳은 배틀씬~~~";
    SCENEMANAGER->RenderToBackbuffer(10, 10, temp.size(), 1, temp);

}
