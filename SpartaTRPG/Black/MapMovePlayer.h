#pragma once
#include "iMapMovable.h"
#include "../Red/TileInfo.h"
#include "../Red/Inventory.h"
#include "../Red/RandomItem.h"

#define RUNSOUNDENDDURATION 0.3f
#define RUNSOUNDENDDURATIONMAX 8

class SelectPopup;
class Effect;
class EnemyInfoBase;

class MapMovePlayer : public iMapMovable
{
private:
	bool activeCheck;
	float runResetSoundDuration;
	float runPlayDuration;
	float range_Of_Sight;

	int mapMove;
	Effect* monsterEffect;

	RandomItemType randomType;
	std::map<char, string> tileDescriptions;

	bool moveToShop;
	bool moveToMiniGame;

	bool isFirstPlay;
	bool isFirstShop;
	bool isFirstDungeon;
	bool isFirstDungeon2;

	EnemyInfoBase* boss;

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
	virtual void MapImageSet() override;
	void ObjectSelectedActive(int _selectValue);

	void CheckRunSoundPlay();

	void TileDescrtiptionRender();
	void PlayerInfoRender();
	void StageInfoRender();
	void CheckTileDescription(char _data);

	void SetVictory();
	void SetDefeat();

	void TutorialPopup(int _select);
	void ShopTutorialPopup(int _select);
	void DungeonTutorialPopup(int _select);
	void BossBattle(int _select);
};

