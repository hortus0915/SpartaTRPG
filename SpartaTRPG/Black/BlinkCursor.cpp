#include "BlinkCursor.h"

#include "Singletons/CommonManagers.h"
#include "CommonFuncs.h"

void BlinkCursor::Update(float deltaTime)
{
    ++blinkCount;
    if (blinkCount % 10 == 0)
        isCursorOff = !isCursorOff;

    cursor = (isCursorOff ? " " : "V");

    fontColor = GetIntRange(BLACK + 1, COLOREND - 1);
}

void BlinkCursor::Render()
{
    SCENEMANAGER->RenderToBackbuffer(posX, posY, 1, 1, cursor, fontColor);
}

void BlinkCursor::SetPos(const int& x, const int& y)
{
    posX = x; posY = y;
}
