#pragma once

#include "BasicInterfaces.h"

struct MapInfo
{
	int posX;
	int posY;

	int width;
	int height;
};

class iMapMovable : public IUpdatable, public IRenderable
{
protected:
	MapInfo info;

	char** image;

public:
	iMapMovable(string _targetSceneName);
	virtual ~iMapMovable();

	virtual void Init(int _startX, int _startY, int _width, int _height);
	virtual void Release();

	virtual void Render() override;

	virtual void MoveTo(int _deltaX, int _deltaY);
	virtual void SetPos(int _posX, int _posY);

	virtual bool IsCanMove(int _targetX, int _targetY);
};

