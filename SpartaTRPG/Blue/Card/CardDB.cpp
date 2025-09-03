#include "CardDB.h"
#include <set>
#include <iostream>
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

	void InitDefaults()
	{
		Clear();

		// ===== 이동 (101~) — 한 방향 1칸,  =====
		AddCard(Card(101, "한칸이동", MOVE, DIR_R, 1));   // 동(→)
		AddCard(Card(102, "한칸이동", MOVE, DIR_L, 1));   // 서(←)
		AddCard(Card(103, "한칸이동", MOVE, DIR_U, 1));   // 북(↑)
		AddCard(Card(104, "한칸이동", MOVE, DIR_D, 1));   // 남(↓)
		AddCard(Card(105, "한칸이동", MOVE, DIR_UL, 1));  // 북서(↖)
		AddCard(Card(106, "한칸이동", MOVE, DIR_UR, 1));  // 북동(↗)
		AddCard(Card(107, "한칸이동", MOVE, DIR_DR, 1));  // 남동(↘)
		AddCard(Card(108, "한칸이동", MOVE, DIR_DL, 1));  // 남서(↙)
		AddCard(Card(101, "두칸이동", MOVE, DIR_R, 2));   // 동(→)
		AddCard(Card(102, "두칸이동", MOVE, DIR_L, 2));   // 서(←)
		AddCard(Card(103, "두칸이동", MOVE, DIR_U, 2));   // 북(↑)
		AddCard(Card(104, "두칸이동", MOVE, DIR_D, 2));   // 남(↓)
		AddCard(Card(105, "두칸이동", MOVE, DIR_UL, 2));  // 북서(↖)
		AddCard(Card(106, "두칸이동", MOVE, DIR_UR, 2));  // 북동(↗)
		AddCard(Card(107, "두칸이동", MOVE, DIR_DR, 2));  // 남동(↘)
		AddCard(Card(108, "두칸이동", MOVE, DIR_DL, 2));  // 남서(↙)

		// ===== 가드 (201~) =====
		AddCard(Card(201, "막기", SHIELD, 0, 0.5f, 10));
		AddCard(Card(202, "가드 업", SHIELD, 0, 0.7f, 15));
		AddCard(Card(203, "전면 방어", SHIELD, 0, 1.0f, 20));

		// ===== 회복 (301~) =====  
		AddCard(Card(301, "응급 처치", HEAL, 0, 20.0f, 20.0f));
		AddCard(Card(302, "기합", HEAL, 0, 0.0f, -20));
		AddCard(Card(303, "보급", HEAL, 0, 15.0f, -20));

		// ===== 공격 (401~) =====
		AddCard(Card(401, "찌르기", ATTACK, (DIR_L | DIR_C | DIR_R), 1.2f, 10));
		AddCard(Card(402, "회전 베기", ATTACK, (DIR_UL | DIR_U | DIR_UR | DIR_L | DIR_R | DIR_DL | DIR_D | DIR_DR), 1.0f, 12));
		AddCard(Card(403, "십자 베기", ATTACK, (DIR_U | DIR_L | DIR_R | DIR_D), 1.1f, 8));
	}
}
