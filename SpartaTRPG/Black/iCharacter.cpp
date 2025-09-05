#include "iCharacter.h"

#include "CommonFuncs.h"
#include <iostream>

iCharacter::iCharacter()
	:
	currentHP(0.0f),
	baseDamage(0.0f),
	maxHP(0.0f),
	currentSP(0.0f),
	maxSP(0.0f),
	criPer(0.0f),
	criDmg(0.0f),
	dodge(0.0f),
	counter(0.0f),
	exp(0)
{
}

void iCharacter::Init(float _hp, float _baseDamage, float _sp, float _criPer, float _criDmg, float _dod, float _counter, int _exp)
{
	maxHP = currentHP = _hp;
	maxSP = currentSP = _sp;
	baseDamage = _baseDamage;

	criPer = _criPer;
	criDmg = _criDmg;

	dodge = _dod;

	counter = _counter;

	exp = _exp;
}

float iCharacter::HitDamager(float damage, void* OnHit(void))
{
	if (IsDodge()) 
	{
		std::cout << " 회피성공! \n";
		return 0.0f; 
	}

	currentHP = (currentHP - damage) < 0 ? 0.0f : currentHP - damage;

	if (OnHit)
	{
		OnHit();
	}

	return damage;
}

bool iCharacter::IsCritical()
{
	float rnd = GetFloatRange(0.0f, 100.0f);

	return rnd <= criPer;
}

bool iCharacter::IsCounter()
{
	float rnd = GetFloatRange(0.0f, 100.0f);

	return rnd <= counter;
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

void iCharacter::AddHP(int _amount)
{
	int current = (int)currentHP + _amount;

	currentHP = (current > (int)maxHP ? maxHP : current);

}

void iCharacter::AddSP(int _amount)
{
	int current = (int)currentSP + _amount;
	currentSP = (current > (int)maxSP ? maxSP : current);
}


