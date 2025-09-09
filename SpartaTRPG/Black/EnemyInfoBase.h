#pragma once
#include "iCharacter.h"

class EnemyInfoBase : public iCharacter
{
private:
	bool isBoss = false;

public:
	bool SetIsBoss(const bool _isBoss) { return isBoss = _isBoss; }
	bool GatIsBoss() const { return isBoss; }
};

void SpawnEnemyByLevel(EnemyInfoBase& enemy, int playerLevel);
void SpawnEnemyBoss(EnemyInfoBase& enemy,int playerLevel);