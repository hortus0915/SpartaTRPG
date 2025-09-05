#pragma once
#include "iMapMovable.h"
#include "../Red/TileInfo.h"

class MapPopup;

class MapMovePlayer : public iMapMovable
{
private:
	MapPopup* popup;
	bool activeCheck = false;
public:
	MapMovePlayer(string _sn, MapData* _mapData);

	virtual void Init(Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK) override;

	// iMapMovable을(를) 통해 상속됨
	void Update(float deltaTime) override;
	void Render() override;
	virtual void Release();

	void PopupInput();
	void MapInput();

	void ObjectActive(TileType _tileType);
	void CheckActive();
};

