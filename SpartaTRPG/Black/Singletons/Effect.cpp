#include "Effect.h"

#include "../CommonMacros.h"
#include "../CommonFuncs.h"
#include "CommonManagers.h"

Effect::Effect(int _width, int _height, float _duration)
{
	posX = 0;
	posY = 0;

	Init(_width, _height, _duration);
}

void Effect::Init(int _width, int _height, float _duration)
{
	width = _width;
	height = _height;

	duration = elapsedTime = _duration;
}

void Effect::Update(float _deltaTime)
{
	elapsedTime += _deltaTime;

	if (!IsRunning() && prevIsRunning)
	{
		EmitAfterEffects();
	}

	prevIsRunning = IsRunning();
}

void Effect::StartEffect(int _posX, int _posY)
{
	posX = Clamp(0, MAX_SCREEN_WIDTH - 1, _posX);
	posY = Clamp(0, MAX_SCREEN_HEIGTH - 1, _posY);

	elapsedTime = 0.0f;
}

void Effect::StartEffect(int _startPosX, int _startPosY, int _endPosX, int _endPosY)
{
	startPosX = Clamp(0, MAX_SCREEN_WIDTH - 1, _startPosX);
	startPosY = Clamp(0, MAX_SCREEN_HEIGTH - 1, _startPosY);

	endPosX = Clamp(0, MAX_SCREEN_WIDTH - 1, _endPosX);
	endPosY = Clamp(0, MAX_SCREEN_HEIGTH - 1, _endPosY);

	elapsedTime = 0.0f;
}

void Effect::AddAfterEffect(AfterEffectInfo _effectName)
{
	afterEffectList.push_back(_effectName);
}

void Effect::EmitAfterEffects()
{
	for (const auto& e : afterEffectList)
	{
		if (e.startDeltaX == e.endDeltaX &&
			e.startDeltaY == e.endDeltaY)
		{
			EFFECTMANAGER->StartEffect(e.effectName, posX + e.startDeltaX, posY + e.startDeltaY);
		}
		else
		{
			EFFECTMANAGER->StartEffect(e.effectName, posX + e.startDeltaX, posY + e.startDeltaY, posX + e.endDeltaX, posY + e.endDeltaY);
		}
	}
}
