#pragma once
#include "iCharacter.h"

class EnemyInfoBase : public iCharacter
{
};

void SpawnEnemyByLevel(EnemyInfoBase& enemy, int playerLevel);