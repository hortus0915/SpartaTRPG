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

void SpawnEnemyByLevel(EnemyInfoBase& enemy, int playerLevel)
{

	int lv = Clamp(playerLevel, 1, 10);
	int steps = lv - 1;

	float hp = 70.0f + steps * 20.0f;
	float sp = 60.0f + steps * 10.0f;
	float atk = 8.0f + steps * 3.0f;


	float criP = 6.0f + steps * 1.0f;
	float criD = 1.40f + steps * 0.05f;
	float dodge = 3.0f + steps * 0.6f;
	float cnt = 1.0f + steps * 0.4f;

	int   expR = lv * 100;


	enemy.Init(hp, sp, atk, criP, criD, dodge, cnt, expR);


	enemy.SetName(ENEMY_NAME_BY_LEVEL[lv - 1]);
}


