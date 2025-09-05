#include "PlayerInfo.h"

#define MAX_EXP_CALC	level * 100

void PlayerInfo::Init(float _hp, float _sp, float _baseDamage, float _criPer, float _criDmg, float _dod, float _counter, int _exp)
{
	__super::Init(_hp, _sp, _baseDamage, _criPer, _criDmg, _dod, _counter, _exp);

	maxExp = MAX_EXP_CALC;

	startHP = maxHP;
	startSP = maxSP;
	startDamage = baseDamage;

	startCriPer = criPer;
	startCriDmg = criDmg;
	startCriDod = dodge;

	exp = 0;
}

void PlayerInfo::GainExp(int _exp)
{
	exp += _exp;
	if (exp >= maxExp)
	{
		LevelUp();
	}
}

void PlayerInfo::LevelUp()
{
	do
	{
		level = (level + 1 > 10 ? LEVEL_MAX : level + 1);

		exp -= maxExp;

		CalcStatus();

	} while (exp >= maxExp);
}

void PlayerInfo::CalcStatus()
{
	maxExp = MAX_EXP_CALC;

	maxHP = startHP + (level - 1) * 20.0f;
	maxSP = startSP + (level - 1) * 20.0f;
	baseDamage = startDamage + (level - 1) * 2.0f;

	criPer += startCriPer * 0.05f;
	criDmg += startCriDmg * 0.05f;
	dodge  += startCriDod * 0.05f;
	counter += startCounter * 0.05f;
}
