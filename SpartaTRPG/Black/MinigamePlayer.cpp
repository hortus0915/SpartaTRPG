#include "MinigamePlayer.h"

#include "Singletons/CommonManagers.h"
#include "CommonFuncs.h"

void MinigamePlayer::Update(float deltaTime)
{

    Player = "O";
   /* ++PlayerCount;
    if (PlayerCount % 10 == 0)
        isCursorOff = !isCursorOff;

    

    fontColor = GetIntRange(BLACK + 1, COLOREND - 1);*/
}

void MinigamePlayer::Render()
{
    SCENEMANAGER->RenderToBackbuffer(posX, posY, 1, 1, Player, fontColor);
}

int MinigamePlayer::GetPosX()
{
    return posX;
}

int MinigamePlayer::GetPosY()
{
    return posY;
}

void MinigamePlayer::SetPos(const int& x, const int& y)
{
    posX = x; posY = y;
}