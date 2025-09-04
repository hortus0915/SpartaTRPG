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
		Card* card;
	};

	void MovoToCharacter(Side& target);
	int AttackToCharacter(Side& attacker, Side& defender);
	int ShieldToCharacter(Side& _self);
	int HealToCharacter(Side& _self);

};