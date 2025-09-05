#include "EffectTail.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"

void EffectTail::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	image = GetIntRange('!', '?');

	bgColor = GetIntRange(BLACK + 1, COLOREND - 1);

	float ratio = elapsedTime / duration;

	posX = Lerp(startPosX, endPosX, ratio);
	posY = Lerp(startPosY, endPosY, ratio);
}

void EffectTail::Render()
{
	SCENEMANAGER->RenderToBackbuffer(posX, posY, image.size(), 1, image, COLOREND - bgColor - 1, bgColor);
}
