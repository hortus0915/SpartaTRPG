#pragma once
#include "iCharacter.h"

class PlayerInfo : public iCharacter
{
private:
	int maxExp;

	float startHP;
	float startSP;
	float startDamage;
	float startCriPer;
	float startCriDmg;
	float startCriDod;
	float startCounter;

	int level;

public:
//	PlayerInfo() : iCharacter(), level(1) {}

	virtual void Init(float _hp, float _sp, float _baseDamage, float _criPer, float _criDmg, float _dod, float _counter, int _exp) override;

	virtual void GainExp(int _exp);

protected:
	virtual void LevelUp();
	virtual void CalcStatus();
};
