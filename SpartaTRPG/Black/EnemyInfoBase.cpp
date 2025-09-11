#include "EnemyInfoBase.h"
#include "CommonFuncs.h"

const string ENEMY_NAME_BY_LEVEL[10] = {
	"이게 왜 돼지",
	"오타 슬라임",
	"세미콜론 은신술사",
	"괄호 도둑 고블린",
	"오프바이원 스켈레톤",
	"하드코딩 트롤",
	"들여쓰기 도깨비",
	"무한루프 사이클롭스",
	"주석의 사신",
	"팀장 개발자"
}; 

static std::set<int> BuildEnemyDeckByLevel(int lv)
{
	lv = Clamp(lv, 1, 10);
	std::set<int> d;

	auto add = [&](int id) {
		if (CardDB::Get(id)) d.insert(id);
		};

	// 공통 기본: 상/하/좌/우 이동 + 방어 + 스태미나 회복 + 공격 3
	add(101); add(102); add(103); add(104);   // 이동(상/하/좌/우)
	add(201);                                  // 방어(기본 가드)
	add(302);                                  // 스태미나 회복
	add(401); add(411); add(408);              // 공격 3종

	// 레벨별 확장
	if (lv >= 2) { add(402); add(105); add(106); }                         // 회전베기, 대각 이동(↖↗)
	if (lv >= 3) { add(405); add(107); add(108); add(202); }               // 가로 일자, 대각(↘↙), 가드 업
	if (lv >= 4) { add(111); add(112); add(113); add(114); add(406); }     // 2칸 이동(↑↓←→), 광역 십자
	if (lv >= 5) { add(407); add(303); }                                   // 대각선 베기, 보급(HP/SP)
	if (lv >= 6) { add(408); add(409); }                                   // 원형, 부채꼴(상)
	if (lv >= 7) { add(410); add(411); }                                   // 부채꼴(하/좌)
	if (lv >= 8) { add(412); add(203); }                                   // 부채꼴(우), 전면 강방
	if (lv >= 9) { add(413); add(304); }                                   // 충격파(광역), 큰 회복
	if (lv >= 10) { add(414); }                                            // 고배율 단일/강타

	return d;
}

void SpawnEnemyByLevel(EnemyInfoBase& _enemy, int _playerLevel)
{

	int lv = Clamp(1, 10, _playerLevel);
	int steps = lv - 1;

	float hp = 70.0f + steps * 20.0f;
	float sp = 60.0f + steps * 10.0f;
	float atk = 8.0f + steps * 3.0f;


	float criP = 6.0f + steps * 1.0f;
	float criD = 1.40f + steps * 0.05f;
	float dodge = 3.0f + steps * 0.6f;
	float cnt = 1.0f + steps * 0.4f;

	int   expR = lv * 100;


	_enemy.Init(hp, sp, atk, criP, criD, dodge, cnt, expR);


	_enemy.SetName(ENEMY_NAME_BY_LEVEL[lv - 1]);
	_enemy.SetDeck(BuildEnemyDeckByLevel(lv));
}

void SpawnEnemyBoss(EnemyInfoBase& _enemy, int _playerlevel)
{
		_enemy.Init(300, 300, 50, 50, 50, 50, 15, 0);
		_enemy.SetName("이다경 곤듀");

	_enemy.SetIsBoss(true);
	_enemy.SetDeck(BuildEnemyDeckByLevel(_playerlevel));
	
}




