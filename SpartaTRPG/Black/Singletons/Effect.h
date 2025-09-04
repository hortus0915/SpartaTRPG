#pragma once

#include <string>
#include <vector>

using namespace std;

#include "../TextColors.h"

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

	vector<string> afterEffectList;

public:
	Effect(int _width, int _height, float _duration);
	virtual ~Effect() { Release(); }

	void Init(int width, int height, float _duration);
	virtual void Update(float deltaTime);
	virtual void Render() = 0;
	virtual void Release() {}

	void StartEffect(int _posX, int _posY);
	void StartEffect(int _startPosX, int _startPosY, int _endPosX, int _endPosY);
	void AddAfterEffect(string _effectName);

	inline bool IsRunning() { return (elapsedTime < duration); }

	inline int GetPosX()   const { return posX; }
	inline int GetPosY()   const { return posY; }
	inline int GetWidth()  const { return width; }
	inline int GetHeight() const { return height; }
};

