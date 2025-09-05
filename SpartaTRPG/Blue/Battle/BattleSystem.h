#pragma once
#include <set>
#include <vector>
#include "../../Black/iCharacter.h"
#include "Board.h"
#include "../Card/CardData.h"


struct BattleSystem {

	struct Side {
		iCharacter* chr;
		std::set<int>* deck;
		Board::Pos* pos;
		const Card* card;
	};

	void MovoToCharacter(Side& _target);
	int AttackToCharacter(Side& _attacker, Side& _defender);
	void ShieldToCharacter(Side& _self,Side& _attacker,float _attackDamage , float& _outAttackDamage, float& _outCounterDamage);
	int HealToCharacter(Side& _self);

};