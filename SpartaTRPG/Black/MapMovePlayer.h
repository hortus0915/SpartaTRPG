#pragma once
#include "iMapMovable.h"
class MapMovePlayer : public iMapMovable
{
public:
	MapMovePlayer(string _sn, MapData* _mapData) : iMapMovable(_sn, _mapData) {}

	virtual void Init(int _startX, int _startY, Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK) override;

	// iMapMovable��(��) ���� ��ӵ�
	void Update(float deltaTime) override;
};

