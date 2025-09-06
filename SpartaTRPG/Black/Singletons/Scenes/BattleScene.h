#pragma once

#include "../SceneInterface.h"


class PlayerInfo;
class EnemyInfoBase;

class BattleScene : public iScene
{
private:
	PlayerInfo*		player;
	EnemyInfoBase*	enemy;





public:
	BattleScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;

	inline void SetBattlers(PlayerInfo* _player, EnemyInfoBase* _enemy) { player = _player; enemy = _enemy; }
};

