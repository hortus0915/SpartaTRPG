#pragma once

#include "../Blue/Card/CardDB.h"

#include "BasicInterfaces.h"

#include <set>

#define LEVEL_MAX	10

class iCharacter
{
protected:
	float currentHP;
	float maxHP;
	float currentSP;
	float maxSP;

	float baseDamage;

	float criPer;
	float criDmg;

	float dodge;
	float counter;

	int exp;

	set<int> deck;

	string name="게임 개발자";


public:
	iCharacter();
	virtual ~iCharacter() {}

	virtual void Init(float _hp, float _baseDamage, float _sp, float _criPer, float _criDmg, float _dod, float _counter, int _exp);
	// Post Return : hitted real damage
	virtual float HitDamager(float damage, void (*OnHit)() = nullptr);
	float vSPCost=0;

	virtual bool IsCritical();
	virtual bool IsCounter();
	virtual float CalcCriDamage(float originDamage);

	virtual bool IsDodge();

	inline bool IsDie() { return currentHP <= 0.0f; }

	inline float GetMaxHP()	 const { return maxHP; }
	inline float GetCurHP()	 const { return currentHP; }
	inline float GetMaxSP()	 const { return maxSP; }
	inline float GetCurSP()	 const { return currentSP; }
	inline virtual float GetBaseDamage() const { return baseDamage; }
	inline float GetCriPer() const { return criPer; }
	inline float GetCriDmg() const { return criDmg; }
	inline float GetDodge()	 const { return dodge; }
	inline float GetCounter() const { return counter; }
	inline int   GetExp()    const { return exp; }
	inline set<int> GetDeck() const { return deck; }
	inline string GetName() const { return name; }

	inline void SetMaxHP(const float& _hp) { maxHP = _hp; }
	inline void SetCurHP(const float& _hp) { currentHP = _hp; }
	inline void SetMaxSP(const float& _sp) { maxSP = _sp; }
	inline void SetCurSP(const float& _sp) { currentSP = _sp; }
	inline void SetBaseDamage(const float& _dmg) { baseDamage = _dmg; }
	inline void SetCriPer(const float& _cri) { criPer = _cri; }
	inline void SetCriDmg(const float& _cri) { criDmg = _cri; }
	inline void SetDodge(const float& _dod) { dodge = _dod; }
	inline void SetCounter(const float& _counter) { counter = _counter; }
	inline void SetExp(const int& _exp) { exp = _exp; }
	inline void SetName(const string& _name) { name = _name; }

	 bool TryApplyVSPCost(const int& _vSPCost);

	void AddHP(int _amount);
	void AddSP(int _amount);
};

