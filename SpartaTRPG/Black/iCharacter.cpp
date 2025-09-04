#include "iCharacter.h"

#include "CommonFuncs.h"

iCharacter::iCharacter()
	:
	currentHP(0.0f),
	maxHP(0.0f),
	currentSP(0.0f),
	maxSP(0.0f),
	criPer(0.0f),
	criDmg(0.0f),
	dodge(0.0f),
	exp(0)
{
}

void iCharacter::Init(float _hp, float _sp, float _criPer, float _criDmg, float _dod, float _exp)
{
	maxHP = currentHP = _hp;
	maxSP = currentSP = _sp;

	criPer = _criPer;
	criDmg = _criDmg;

	dodge = _dod;

	exp = _exp;
}

float iCharacter::HitDamager(float damage)
{
	float realDamage = (IsCritical() ? CalcCriDamage(damage) : damage);

	currentHP = (currentHP - damage) < 0 ? 0.0f : currentHP - realDamage;

	return realDamage;
}

bool iCharacter::IsCritical()
{
	float rnd = GetFloatRange(0.0f, 100.0f);

	return rnd <= criPer;
}

float iCharacter::CalcCriDamage(float _originDamage)
{
	return _originDamage * criDmg;
}

bool iCharacter::IsDodge()
{
	float rnd = GetFloatRange(0.0f, 100.0f);

	return rnd < dodge;
}
