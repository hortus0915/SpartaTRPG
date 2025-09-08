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

	void BeginVPS(Side& _target);

	void MovoToCharacter(Side& _target);
	void ShieldToCharacter(Side& _self,Side& _attacker,float _attackDamage , float& _outAttackDamage, float& _outCounterDamage);

	int AttackToCharacter(Side& _attacker, Side& _defender, std::vector<Board::Pos>& outRange);
	int HealToCharacter(Side& _self);
	int HealToCharacter(Side& _self, stringstream& sStream);

};