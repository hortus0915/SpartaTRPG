#include "CardDB.h"
#include <iostream>
#include <unordered_set>

using namespace std;
namespace {
	map<int, Card> g_catalog;
}

namespace CardDB
{
	void Clear() { g_catalog.clear(); }

	void AddCard(const Card& _card)
	{
		int idx = _card.GetIdx();
		g_catalog.emplace(idx, _card);
	}

	const Card* CardDB::Get(int idx) {
		auto it = g_catalog.find(idx);
		if (it == g_catalog.end()) return nullptr;
		return &it->second;
	}

	int RandomNotOwnedIndex(const std::set<int>& _ownedSet)
	{
		std::vector<int> candidates;
		candidates.reserve(g_catalog.size());

		for (auto& kv : g_catalog) {
			if (_ownedSet.find(kv.first) == _ownedSet.end()) {
				candidates.push_back(kv.first);
			}
		}

		if (candidates.empty()) return -1; // 모든 카드 소유 시

		int pick = rand() % candidates.size();
		return candidates[pick];
	}

	void InitDefaults()
	{
		Clear();

		// ===== 이동 (101~) — 한 방향 1칸,  =====
		AddCard(Card(101, "한칸이동", MOVE, DIR_R, 1));   // 동(→)
		AddCard(Card(102, "한칸이동", MOVE, DIR_L, 1));   // 서(←)
		AddCard(Card(103, "한칸이동", MOVE, DIR_U, 1));   // 북(↑)
		AddCard(Card(104, "한칸이동", MOVE, DIR_D, 1));   // 남(↓)
		AddCard(Card(105, "한칸이동", MOVE, DIR_UL, 1, 10));  // 북서(↖)
		AddCard(Card(106, "한칸이동", MOVE, DIR_UR, 1, 10));  // 북동(↗)
		AddCard(Card(107, "한칸이동", MOVE, DIR_DR, 1, 10));  // 남동(↘)
		AddCard(Card(108, "한칸이동", MOVE, DIR_DL, 1, 10));  // 남서(↙)
		AddCard(Card(111, "두칸이동", MOVE, DIR_R, 2, 10));   // 동(→)
		AddCard(Card(112, "두칸이동", MOVE, DIR_L, 2, 10));   // 서(←)
		AddCard(Card(113, "두칸이동", MOVE, DIR_U, 2, 10));   // 북(↑)
		AddCard(Card(114, "두칸이동", MOVE, DIR_D, 2, 10));   // 남(↓)


		// ===== 가드 (201~) =====
		AddCard(Card(201, "막기", SHIELD, 0, 0.5f, 20));
		AddCard(Card(202, "가드 업", SHIELD, 0, 0.7f, 30));
		AddCard(Card(203, "전면 방어", SHIELD, 0, 1.0f, 50));

		// ===== 회복 (301~) =====  
		AddCard(Card(301, "응급 처치", HEAL, 0, 20.0f, 20));
		AddCard(Card(302, "기합", HEAL, 0, 0.0f, -20));
		AddCard(Card(303, "보급", HEAL, 0, 15.0f, -20));
		AddCard(Card(304, "회복", HEAL, 0, 50.0f, 50));

		// ===== 공격 (401~) =====
		AddCard(Card(401, "찌르기", ATTACK, (DIR_L | DIR_C | DIR_R), 1.5f, 30));
		AddCard(Card(402, "회전 베기", ATTACK, (DIR_UL | DIR_U | DIR_UR | DIR_L | DIR_R | DIR_DL | DIR_D | DIR_DR), 1.3f, 20));
		AddCard(Card(403, "십자 베기", ATTACK, (DIR_U | DIR_L | DIR_R | DIR_D), 1.1f, 20));
		AddCard(Card(404, "전방 일자 베기", ATTACK, LINE_V3, 1.0f, 20));
		AddCard(Card(405, "가로 일자 베기", ATTACK, LINE_H3, 1.0f, 20));
		AddCard(Card(406, "광역 십자 베기", ATTACK, CROSS, 1.05f, 30));
		AddCard(Card(407, "대각선 베기", ATTACK, DIAGONAL4, 1.1f, 40));
		AddCard(Card(408, "원형 일격", ATTACK, PERIMETER8, 1.0f, 50));

		AddCard(Card(409, "부채꼴 찌르기(상)", ATTACK, CONE_U_3, 1.15f, 30));
		AddCard(Card(410, "부채꼴 베기(하)", ATTACK, CONE_D_3, 1.15f, 30));
		AddCard(Card(411, "부채꼴 베기(좌)", ATTACK, CONE_L_3, 1.15f, 30));
		AddCard(Card(412, "부채꼴 베기(우)", ATTACK, CONE_R_3, 1.15f, 30));

		AddCard(Card(413, "충격파", ATTACK, ALL9, 0.65f, 50));

		AddCard(Card(414, "제자리 강타", ATTACK, CENTER_ONLY, 3.0f, 50));
	}



}
