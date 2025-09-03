#include "Blue/Card/CardData.h"
#include <vector>

int main()
{
	std::vector<Card> deck;

	deck.emplace_back(1, "이동", MOVE, DIR_R,1.0f); // 이동
	deck.emplace_back(2, "찌르기", ATTACK, 0b000111000, 1.2,10); // 공격
	deck.emplace_back(3, "방패 막기", SHIELD, 0, 0.5f, 30); // 방어
	deck.emplace_back(4, "체력 회복", HEAL, 0, 30, 10); // 회복
	deck.emplace_back(5, "마나 회복", HEAL, 0, 0, -20); //스테미나 회복
	

	deck.emplace_back(5, "체력마나 회복", HEAL, 0, 10, -20); //스테미나 회복
	for (auto& card : deck)
	{
		card.PrintInfo();
	}

	return 0;
}
