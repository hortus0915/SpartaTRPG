#pragma once
#include "iMapMovable.h"
#include "../Red/TileInfo.h"

class MapPopup;

class MapMovePlayer : public iMapMovable
{
private:
	MapPopup* popup;
	bool showPopup = false;
public:
	MapMovePlayer(string _sn, MapData* _mapData);

	virtual void Init(Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK) override;

	// iMapMovable��(��) ���� ��ӵ�
	void Update(float deltaTime) override;
	void Render() override;
	virtual void Release();

	void ObjectActive(TileType _tileType);

	void CheckPopup();
};

