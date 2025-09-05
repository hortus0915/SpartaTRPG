
#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>
#include "Blue/Battle/Board.h"
#include "Blue/Card/CardData.h"
#include "Black/PlayerInfo.h"
#include "Black/iCharacter.h"
#include "Blue/Card/CardDB.h"
#include "Blue/Battle/BattleSystem.h"

//test view UI 
static void PrintBoard(const Board::Pos& p, const Board::Pos& m) {
	for (int y = 0; y < Board::H; ++y) {
		for (int x = 0; x < Board::W; ++x) {
			if (p.x == x && p.y == y) std::cout << " P ";
			else if (m.x == x && m.y == y) std::cout << " M ";
			else std::cout << " . ";
		}
		std::cout << "\n";
	}
}


int main() {
	std::srand((unsigned)std::time(nullptr));

	CardDB::InitDefaults();


	PlayerInfo player;  player.Init(100, 100, 10,50, 1.5f, 50,50, 0);
	iCharacter monster; monster.Init(80, 100, 10,5, 1.3f, 50, 50, 0);

	Board::Pos pPos{ 0, 1 };
	Board::Pos mPos{ 3, 1 };


	std::set<int> pdeck = { 101,102,103,104,111,112,201,301,401 };
	std::set<int> mdeck = { 101,104,201,401 };

	BattleSystem sys;
	BattleSystem::Side P{ &player, &pdeck, &pPos };
	BattleSystem::Side M{ &monster, &mdeck, &mPos };

	int damage = 0;

	while (true) {
		std::cout << "\n=== 테스트 ===\n";
		std::cout << "[P] (" << pPos.x << "," << pPos.y << ")   [M] (" << mPos.x << "," << mPos.y << ")\n";
		PrintBoard(pPos, mPos);

		std::vector<const Card*> moveCards;
		for (int idx : pdeck) {
			const Card* c = CardDB::Get(idx);
			if (!c) continue;
			moveCards.push_back(c);
		}

		std::cout << "\n카드 목록:\n";
		for (size_t i = 0; i < moveCards.size(); ++i) {
			const Card* c = moveCards[i];
			cout << "  " << (i + 1) << ") ";
			c->PrintInfo();

		}
		std::cout << "  0) 종료\n선택: ";

		int sel = 0;
		if (!(std::cin >> sel)) return 0;
		if (sel <= 0 || sel > (moveCards.size())) break;

		const Card* chosen = moveCards[sel - 1];
		P.card = chosen;

		float playerAttackDamage = 0;
		float monsterAttackDamage = 0;

		if ( P.card->GetType() == MOVE) {
			std::cout << "[P 이동] "; sys.MovoToCharacter(P); cout << "\n";
		}
		if ( M.card->GetType() == MOVE) {
			std::cout << "[M 이동] "; sys.MovoToCharacter(M); cout << "\n";
		}

		if (P.card->GetType() == HEAL)
		{
			std::cout << "[P 회복] "; sys.HealToCharacter(P);
		}
		if (M.card->GetType() == HEAL)
		{
			std::cout << "[M 회복] "; sys.HealToCharacter(M);
		}

		if (P.card->GetType() == ATTACK)
		{
			playerAttackDamage = (float)sys.AttackToCharacter(P, M);
			if (playerAttackDamage > 0)
			{
				std::cout << "[P 공격] " << "데미지 :" << playerAttackDamage;
				if (M.card->GetType() == SHIELD)
				{
					sys.ShieldToCharacter(M, P, playerAttackDamage);
				}
			}
			else
			{
				std::cout << "[P 공격] " << "범위 밖! ";
			}
		
		}
		
		if (M.card->GetType() == ATTACK)
		{
			monsterAttackDamage = (float)sys.AttackToCharacter(M, P);
			if (monsterAttackDamage > 0)
			{
				std::cout << "[M 공격] " << "데미지 :" << monsterAttackDamage;
				if (P.card->GetType() == SHIELD)
				{
					sys.ShieldToCharacter(P, M, monsterAttackDamage);
				}
				P.chr->HitDamager(monsterAttackDamage);

			
			}
			else
			{
				std::cout << "[M 공격] " << "범위 밖! ";
			}
		}



	}

	std::cout << "\n테스트 종료\n";
	return 0;
}
