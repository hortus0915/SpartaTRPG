#pragma once

#include "SingletonMacro.h"

class Timer;

class TimeManager
{
	SINGLETON(TimeManager, : _timer(nullptr))

private:
	Timer* _timer;

public:
	void Init();
	void Update(float lock = 0.0f);

	float GetElapsedTime()	const;
	float GetWorldTile()	const;
};
