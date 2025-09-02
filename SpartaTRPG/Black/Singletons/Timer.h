#pragma once

#include <Windows.h>

class Timer
{
private:
	bool			_isHardware;
	float			_timeScale;
	float			_timeElapsed;

	__int64			_curTime;
	__int64			_lastTime;
	__int64			_periodFrequency;

	unsigned long	_frameRate;
	unsigned long	_FPSframeCount;

	float			 _FPSTimeElapsed;
	float			 _worldTime;

public:
	Timer()  {}
	~Timer() {}

	void Init();
	void tick(float lockFPS = 0.0f);

	inline float GetElapsedTime()	const { return _timeElapsed; }
	inline float GetWorldTime()		const { return _worldTime; }

	unsigned long GetFrameRate(char* str = nullptr) const;
};

