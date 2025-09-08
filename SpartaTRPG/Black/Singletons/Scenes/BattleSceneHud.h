#pragma once

#include <sstream>

using namespace std;

#include "../../BasicInterfaces.h"
#include "../../TextColors.h"

class PlayerInfo;
class EnemyInfoBase;

class BattleSceneHud : public IUpdatable, public IRenderable
{
private:
	int posX;
	int posY;

	PlayerInfo* player;
	EnemyInfoBase* enemy;

	string playerHP;
	string playerSP;
	Color playerHPBgColor;

	string enemyHP;
	string enemySP;
	Color enemyHPBgColor;

	stringstream sStream;

	static string upperOpen;
	static string upperClose;
	static string lowerOpen;
	static string lowerClose;

public:
	BattleSceneHud(string _sn) : IUpdatable(_sn), IRenderable(_sn), posX(0), posY(0) { }

	int Init(PlayerInfo* _player, EnemyInfoBase* _enemy, int _posX, int _posY);
	void Release();

	void Update(float _deltaTime);
	void BgColorSetting(const float& ratio, Color& targetBg);

	// IRenderable을(를) 통해 상속됨
	void Render() override;
};

