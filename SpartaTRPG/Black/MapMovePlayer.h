#pragma once
#include "iMapMovable.h"
class MapMovePlayer : public iMapMovable
{
public:
	MapMovePlayer(string _sn) : iMapMovable(_sn) {}

	virtual void Init(int _startX, int _startY, int _width, int _height, Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK) override;

	// iMapMovable을(를) 통해 상속됨
	void Update(float deltaTime) override;
};

