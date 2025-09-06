#pragma once
#include "iMapMovable.h"
#include "../Red/TileInfo.h"

#define RUNSOUNDENDDURATION 0.3f

class SelectPopup;

class MapMovePlayer : public iMapMovable
{
private:
	bool activeCheck = false;
	float runSoundDuration;
public:
	MapMovePlayer(string _sn, MapData* _mapData);

	virtual void Init(Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK) override;

	// iMapMovable을(를) 통해 상속됨
	void Update(float deltaTime) override;
	void Render() override;
	virtual void Release();

	void MapInput(float deltaTime);

	void ObjectActive(TileType _tileType);
	void CheckActive();

	void ObjectSelectedActive(int selectValue);

	void CheckRunSoundPlay();
};

