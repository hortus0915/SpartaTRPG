#pragma once
#include <string>
#include <iostream>
#include <cstdint>


using u16 = std::uint16_t;

/*

 비트 마스크 맵핑

[0][1][2]
[3][4][5]
[6][7][8]

[1u<<0][1u<<1][1u<<2]
[1u<<3][1u<<4][1u<<5]
[1u<<6][1u<<7][1u<<8]

[0b000000001][0b000000010][0b000000100]
[0b000001000][0b000010000][0b000100000]
[0b001000000][0b010000000][0b100000000]

*/

constexpr u16 DIR_UL = 1u << 0; // ↖
constexpr u16 DIR_U = 1u << 1; // ↑
constexpr u16 DIR_UR = 1u << 2; // ↗
constexpr u16 DIR_L = 1u << 3; // ←
constexpr u16 DIR_C = 1u << 4; // 중앙
constexpr u16 DIR_R = 1u << 5; // →
constexpr u16 DIR_DL = 1u << 6; // ↙
constexpr u16 DIR_D = 1u << 7; // ↓
constexpr u16 DIR_DR = 1u << 8; // ↘

// ===== 편의 조합 =====
constexpr u16 NONE = 0;
constexpr u16 CENTER_ONLY = DIR_C;

// 직선 3칸
constexpr u16 LINE_H3 = (DIR_L | DIR_C | DIR_R);   // 가로 중앙줄
constexpr u16 LINE_V3 = (DIR_U | DIR_C | DIR_D);   // 세로 중앙줄

// 행/열
constexpr u16 ROW_TOP = (DIR_UL | DIR_U | DIR_UR);
constexpr u16 ROW_MID = LINE_H3;
constexpr u16 ROW_BOT = (DIR_DL | DIR_D | DIR_DR);

constexpr u16 COL_LEFT = (DIR_UL | DIR_L | DIR_DL);
constexpr u16 COL_MID = LINE_V3;
constexpr u16 COL_RIGHT = (DIR_UR | DIR_R | DIR_DR);

// 대각/십자/외곽/전체
constexpr u16 DIAGONAL4 = (DIR_UL | DIR_UR | DIR_DL | DIR_DR);
constexpr u16 DIAG_MAIN = (DIR_UL | DIR_C | DIR_DR); // '\'
constexpr u16 DIAG_ANTI = (DIR_UR | DIR_C | DIR_DL); // '/'
constexpr u16 CROSS = (DIR_U | DIR_L | DIR_R | DIR_D);
constexpr u16 CROSS_C = (CROSS | DIR_C);
constexpr u16 PERIMETER8 = (CROSS | DIAGONAL4);
constexpr u16 ALL9 = (PERIMETER8 | DIR_C);

// 콘(부채꼴) 3칸
constexpr u16 CONE_U_3 = (DIR_U | DIR_UL | DIR_UR);
constexpr u16 CONE_D_3 = (DIR_D | DIR_DL | DIR_DR);
constexpr u16 CONE_L_3 = (DIR_L | DIR_UL | DIR_DL);
constexpr u16 CONE_R_3 = (DIR_R | DIR_UR | DIR_DR);

// T 모양(중앙 포함)
constexpr u16 T_U = (DIR_U | DIR_L | DIR_R | DIR_C);
constexpr u16 T_D = (DIR_D | DIR_L | DIR_R | DIR_C);
constexpr u16 T_L = (DIR_L | DIR_U | DIR_D | DIR_C);
constexpr u16 T_R = (DIR_R | DIR_U | DIR_D | DIR_C);

// 모서리/엣지
constexpr u16 CORNERS4 = (DIR_UL | DIR_UR | DIR_DL | DIR_DR);
constexpr u16 EDGES4 = (DIR_U | DIR_L | DIR_R | DIR_D);

enum CardType
{
	MOVE,     // 이동
	ATTACK,   // 공격
	SHIELD,   // 방어/쉴드
	HEAL      // 회복
};

class Card
{
private:
	int idx;              // 카드 번호
	std::string name;		  // 카드 이름
	CardType type;        // 카드 타입
	u16 range;   // 공격 범위 (비트마스크)
	float damageRate;    // 데미지 배율   HEAL일 때: 체력 회복량으로 사용 (+N) SHIELD일 때: 피해 감소율로 사용 (0.0~1.0)
	int staminaCost;      // 소모 마나 HEAL일 때: 체력 회복량으로 사용 (+N)

public:
	Card(int _idx, const std::string& _name, CardType _type, u16 _range = 0,
		float _damageRate = 0.0f, int _staminaCost = 0);

	// Getter
	int  GetIdx() const { return idx; }
	std::string  GetName() const { return name; }
	CardType  GetType() const { return type; }
	float  GetDamageRate() const { return damageRate; }
	int  GetStaminaCost() const { return staminaCost; }
	u16  GetRange() const { return range; }

	// 출력
	void PrintInfo() const;
	void PrintRange() const;
	void PrintMoveRange() const;
	void PrintHealInfo() const;
};


/*

예시)
	std::vector<Card> deck;

	deck.emplace_back(1, "이동", MOVE, DIR_R,1.0f); // 이동
	deck.emplace_back(2, "찌르기", ATTACK, 0b000111000, 1.2,10); // 공격
	deck.emplace_back(3, "방패 막기", SHIELD, 0, 10, 30); // 방어
	deck.emplace_back(4, "체력 회복", HEAL, 0, 30, 10); // 회복
	deck.emplace_back(5, "스테미나 회복", HEAL, 0, 0, -20); //스테미나 회복
	deck.emplace_back(5, "스테미나 회복", HEAL, 0, 10, -20); //체력+스테미나 회복
	for (auto& card : deck)
	{
		card.PrintInfo();
	}

*/