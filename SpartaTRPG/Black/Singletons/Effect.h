#pragma once

#include <string>
#include <vector>

using namespace std;

#include "../TextColors.h"

struct AfterEffectInfo
{
	AfterEffectInfo() { }
	AfterEffectInfo(int _sDeltaX, int _sDeltaY, int _eDeltaX, int _eDeltaY, string name)
		: startDeltaX(_sDeltaX), startDeltaY(_sDeltaY), endDeltaX(_eDeltaX), endDeltaY(_eDeltaY), effectName(name) { }

	int startDeltaX;
	int startDeltaY;

	int endDeltaX;
	int endDeltaY;

	string effectName;
};

class Effect
{
protected:
	int posX;
	int posY;

	int startPosX;
	int startPosY;

	int endPosX;
	int endPosY;

	int width;
	int height;

	float duration;
	float elapsedTime;

	vector<AfterEffectInfo> afterEffectList;

	bool prevIsRunning;

public:
	Effect(int _width, int _height, float _duration);
	virtual ~Effect() { Release(); }

	void Init(int width, int height, float _duration);
	virtual void Update(float deltaTime);
	virtual void Render() = 0;
	virtual void Release() {}

	void StartEffect(int _posX, int _posY);
	void StartEffect(int _startPosX, int _startPosY, int _endPosX, int _endPosY);
	void AddAfterEffect(AfterEffectInfo _effectName);
	void EmitAfterEffects();

	inline bool IsRunning() { return (elapsedTime < duration); }

	inline int GetPosX()   const { return posX; }
	inline int GetPosY()   const { return posY; }
	inline int GetWidth()  const { return width; }
	inline int GetHeight() const { return height; }
};

