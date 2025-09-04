#pragma once

#include "BasicInterfaces.h"

#define LEVEL_MAX	10

class iCharacter
{
protected:
	float currentHP;
	float maxHP;
	float currentSP;
	float maxSP;

	float criPer;
	float criDmg;

	float dodge;

	int exp;

public:
	iCharacter();
	virtual ~iCharacter() {}

	virtual void Init(float _hp, float _sp, float _criPer, float _criDmg, float _dod, float _exp);

	// Post Return : hitted real damage
	virtual float HitDamager(float damage);

	virtual bool IsCritical();
	virtual float CalcCriDamage(float originDamage);

	virtual bool IsDodge();
	
	inline bool IsDie() { return currentHP <= 0.0f; }

	inline float GetMaxHP()	 const { return maxHP; }
	inline float GetCurHP()	 const { return currentHP; }
	inline float GetMaxSP()	 const { return maxSP; }
	inline float GetCurSP()	 const { return currentSP; }
	inline float GetCriPer() const { return criPer; }
	inline float GetCriDmg() const { return criDmg; }
	inline float GetDodge()	 const { return dodge; }
	inline int   GetExp()    const { return exp; }

	inline void SetMaxHP(const float& _hp)   { maxHP = _hp; }
	inline void SetCurHP(const float& _hp)   { currentHP = _hp; }
	inline void SetMaxSP(const float& _sp)   { maxSP = _sp; }
	inline void SetCurSP(const float& _sp)   { currentSP = _sp; }
	inline void SetCriPer(const float& _cri) { criPer = _cri; }
	inline void SetCriDmg(const float& _cri) { criDmg = _cri; }
	inline void SetDodge(const float& _dod)  { dodge = _dod; }
	inline void SetExp(const int& _exp)      { exp = _exp;}

};

