#include "TimeManager.h"

#include "Timer.h"
#include "../CommonMacros.h"

TimeManager* TimeManager::instance = nullptr;

void TimeManager::Init()
{
	_timer = new Timer;

	return _timer->Init();
}

void TimeManager::Release()
{
	SAFE_DELETE(_timer);
}

void TimeManager::Update(float lock)
{
	if (_timer)
		_timer->tick(lock);
}

float TimeManager::GetElapsedTime()	const { return _timer->GetElapsedTime(); }
float TimeManager::GetWorldTile()	const { return _timer->GetWorldTime(); }
