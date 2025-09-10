#pragma once
#include "iCharacter.h"

class PlayerInfo : public iCharacter
{
private:
	int maxExp;

	float startHP;
	float startSP;

	float startCriPer;
	float startCriDmg;
	float startCriDod;
	float startDamage;
	float startCounter;

	float equipDamage;

	int level=1;

public:
	//	PlayerInfo() : iCharacter(), level(1) {}

	virtual void Init(float _hp, float _sp, float _baseDamage, float _criPer, float _criDmg, float _dod, float _counter, int _exp) override;

	virtual void GainExp(int _exp);

	int GetLevel() const { return level; }

	void SetEquipDamage(const float _d) { equipDamage = _d; }
	float GetEquipDamage() const { return equipDamage; }

	inline float GetBaseDamage() const override { return baseDamage + equipDamage; }

	inline void AddCard(const int& _c) { deck.insert(_c); }

protected:
	virtual void LevelUp();
	virtual void CalcStatus();
};
