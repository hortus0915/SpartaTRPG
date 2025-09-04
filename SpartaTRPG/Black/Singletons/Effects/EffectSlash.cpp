#include "EffectSlash.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"

void EffectSlash::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	bgColor = GetIntRange(BLACK + 1, COLOREND - 1);

	float ratio = elapsedTime / duration;

	if (ratio < 0.25f)
	{
		image[0] = '@';
		image[1] = '@';
		image[2] = GetIntRange('!', '?');
		image[3] = '@';
		image[4] = '@';
	}
	else if (ratio < 0.45f)
	{
		image[0] = '@';
		image[1] = GetIntRange('!', '?');
		image[2] = GetIntRange('!', '?');
		image[3] = GetIntRange('!', '?');
		image[4] = '@';
	}
	else if (ratio < 0.55f)
	{
		image[0] = GetIntRange('!', '?');
		image[1] = GetIntRange('!', '?');
		image[2] = GetIntRange('!', '?');
		image[3] = GetIntRange('!', '?');
		image[4] = GetIntRange('!', '?');
	}
	else if (ratio < 0.75f)
	{
		image[0] = '@';
		image[1] = GetIntRange('!', '?');
		image[2] = GetIntRange('!', '?');
		image[3] = GetIntRange('!', '?');
		image[4] = '@';
	}
	else if (ratio < 1.0f)
	{
		image[0] = '@';
		image[1] = '@';
		image[2] = GetIntRange('!', '?');
		image[3] = '@';
		image[4] = '@';
	}

	posX = Lerp(startPosX, endPosX, ratio);
	posY = Lerp(startPosY, endPosY, ratio);
}

void EffectSlash::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		int realPosY = posY - 2 + i;

		if (0 <= realPosY && realPosY < MAX_SCREEN_HEIGTH)
		{
			SCENEMANAGER->RenderToBackbuffer(posX, realPosY, 1, 1, &image[i], COLOREND - bgColor - 1, bgColor);
		}
	}
}
