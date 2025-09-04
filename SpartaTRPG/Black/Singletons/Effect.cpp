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

void Effect::AddAfterEffect(string _effectName)
{
	afterEffectList.push_back(_effectName);
}
