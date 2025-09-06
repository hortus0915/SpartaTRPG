
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
#include "Black/CommonFuncs.h"

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

	PlayerInfo player;  player.Init(100, 10, 10,50, 1.5f, 50,50, 0);
	iCharacter monster; monster.Init(80, 10, 10,50, 1.3f, 50, 50, 0);

	Board::Pos pPos{ 0, 1 };
	Board::Pos mPos{ 3, 1 };

	std::set<int> pdeck = { 101,102,103,104,111,112,201,301,401 ,403,408};
	std::set<int> mdeck = { 101,102,103,104,201,202,203,301,401,402,404 };

	BattleSystem sys;
	BattleSystem::Side P{ &player, &pdeck, &pPos };
	BattleSystem::Side M{ &monster, &mdeck, &mPos };

	int damage = 0;
	bool isGameOver = false;

	while (!isGameOver) {
		std::system("cls");
		std::cout << "\n=== 테스트 ===\n";
		std::cout << "[P] (" << pPos.x << "," << pPos.y << ")   [M] (" << mPos.x << "," << mPos.y << ")\n";
		std::cout << "P 체력: " << player.GetCurHP() << " / " 
			<< player.GetMaxHP() << "   M 체력: "
			<< monster.GetCurHP() << " / " << monster.GetMaxHP() << "\n";

		PrintBoard(pPos, mPos);

		std::vector<const Card*> playerCards;
		for (int idx : pdeck) {
			const Card* c = CardDB::Get(idx);
			if (!c) continue;
			playerCards.push_back(c);
		}

		std::vector<const Card*> monsterCards;
		for (int idx : mdeck) {
			const Card* c = CardDB::Get(idx);
			if (!c) continue;
			monsterCards.push_back(c);
		}

		std::cout << "\n카드 목록:\n";
		for (size_t i = 0; i < playerCards.size(); ++i) {
			const Card* c = playerCards[i];
			cout << "  " << (i + 1) << ") ";
			c->PrintInfo();

		}

		int sel = 0;
		if (!(std::cin >> sel)) return 0;
		if (sel <= 0 || sel > (playerCards.size())) break;

		const Card* chosen = playerCards[sel - 1];
		P.card = chosen;
		const Card* mChosen = monsterCards[GetIntRange(0, monsterCards.size()-1)];
		M.card = mChosen;

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
			cout << "[P 공격 : " << P.card->GetName()<<"] \n";
			playerAttackDamage = (float)sys.AttackToCharacter(P, M);
			if (playerAttackDamage > 0)
			{
				std::cout << "데미지 :" << playerAttackDamage;
				if (M.card->GetType() == SHIELD)
				{
					sys.ShieldToCharacter(M, P, playerAttackDamage, playerAttackDamage,monsterAttackDamage);
				}
			}
			else
			{
				std::cout  << "범위 밖! \n";
			}
		
		}
		
		if (M.card->GetType() == ATTACK)
		{
			cout << "[M 공격 : " << M.card->GetName() << "] \n";
			monsterAttackDamage = (float)sys.AttackToCharacter(M, P);
			if (monsterAttackDamage > 0)
			{
				std::cout << "[M 공격] " << "데미지 :" << monsterAttackDamage;
				if (P.card->GetType() == SHIELD)
				{
					sys.ShieldToCharacter(P, M, monsterAttackDamage,monsterAttackDamage,playerAttackDamage);
				}
				
			}
			else
			{
				std::cout << "[M 공격] " << "범위 밖!  \n";
			}
		}

		if (playerAttackDamage > 0)
		{
			if(M.chr->HitDamager(playerAttackDamage))
			{
				std::cout << "M의 공격으로 인한 P 현재 체력" << P.chr->GetCurHP() << "\n";
			}
			
		}

		if (monsterAttackDamage > 0)
		{
			if (P.chr->HitDamager(monsterAttackDamage))
			{
			std::cout << "M의 공격으로 인한 P 현재 체력" << P.chr->GetCurHP() << "\n";
			}

		}

		if (P.chr->GetCurHP() == 0 && M.chr->GetCurHP() == 0)
		{
			std::cout << "무승부!\n";
			isGameOver = false;
		}
		else if (P.chr->GetCurHP() == 0)
		{
			std::cout << "패배!\n";
			isGameOver = false;
		}
		else if (M.chr->GetCurHP() == 0)
		{
			std::cout << "승리!\n";
			isGameOver = false;
		}

		std::cout << "아무키나 눌러서 계속.." << std::endl;
		system("pause");


	}

	std::cout << "\n테스트 종료\n";
	return 0;
}
