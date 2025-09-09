#include "BattleSceneHud.h"

#include "../../PlayerInfo.h";
#include "../../EnemyInfoBase.h";
#include "../EffectType.h"

#include "../CommonManagers.h"

string BattleSceneHud::upperOpen = "#*";
string BattleSceneHud::upperClose = "*#";
string BattleSceneHud::lowerOpen = "#*";
string BattleSceneHud::lowerClose = "*#";

int BattleSceneHud::Init(PlayerInfo* _player, EnemyInfoBase* _enemy, int _posX, int _posY)
{
	player = _player;
	enemy = _enemy;

	posX = _posX;
	posY = _posY;

	if (!player || !enemy)
		return -1;

	return 0;
}

void BattleSceneHud::Release()
{
	sStream.clear();
}

void BattleSceneHud::Update(float _deltaTime)
{
	int count = 2;
	float ratio;

	ratio = player->GetCurHP() / player->GetMaxHP() * 100.0f;
	playerHP = "";
	playerHP.append(((int)(ratio / 10)) * count, ' ');
	BgColorSetting(ratio / 100.0f, playerHPBgColor);
	
	float pCurForUi = previewPlayer_ ? player->vSPCost : player->GetCurSP();
	ratio = pCurForUi / player->GetMaxSP() * 100.0f;
	playerSP = "";
	playerSP.append(((int)(ratio / 10)) * count, ' ');

	ratio = enemy->GetCurHP() / enemy->GetMaxHP() * 100.0f;
	enemyHP = "";
	enemyHP.append(((int)(ratio / 10)) * count, ' ');
	BgColorSetting(ratio / 100.0f, enemyHPBgColor);

	ratio = enemy->GetCurSP() / enemy->GetMaxSP() * 100.0f;
	enemySP = "";
	enemySP.append(((int)(ratio / 10)) * count, ' ');

	if (KEYMANAGER->IsOnceKeyDown('A'))
	{
		player->HitDamager(5);
		int curHP = player->GetCurHP();
		int a;
	}
}

void BattleSceneHud::BgColorSetting(const float& ratio, Color& targetBg)
{
	if (ratio <= 0.3f)
		targetBg = DARKRED;
	else if (ratio <= 0.5f)
		targetBg = DARKYELLOW;
	else
		targetBg = DARKGREEN;
}

void BattleSceneHud::Render()
{
	int count = 2;

	int offsetY = 0;
	string temp;
	float ratio;
	string title = "";

	sStream.str("");
	sStream << "Player : ";
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	sStream.str("");
	sStream << "HP : " << player->GetCurHP() << " / " << player->GetMaxHP();
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	sStream.str("");
	if (previewPlayer_) {
		sStream << "SP : " << player->vSPCost << " / " << player->GetMaxSP();
	}
	else {
		sStream << "SP : " << player->GetCurSP() << " / " << player->GetMaxSP();
	}
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	ratio = player->GetCurHP() / player->GetMaxHP() * 100.0f;
	temp = "";
	temp.append((10 - (int)(ratio / 10)) * count, ' ');
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upperOpen.size(), 1, upperOpen);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size(), posY + offsetY, playerHP.size(), 1, playerHP, WHITE, playerHPBgColor);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + playerHP.size(), posY + offsetY, temp.size(), 1, temp, WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + playerHP.size() + temp.size(), posY + offsetY, upperClose.size(), 1, upperClose);

	++offsetY;

	ratio = player->GetCurSP() / player->GetMaxSP() * 100.0f;
	temp = "";
	temp.append((10 - (int)(ratio / 10)) * count, ' ');
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upperOpen.size(), 1, upperOpen);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size(), posY + offsetY, playerSP.size(), 1, playerSP, WHITE, CYAN);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + playerSP.size(), posY + offsetY, temp.size(), 1, temp, WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + playerSP.size() + temp.size(), posY + offsetY, upperClose.size(), 1, upperClose);


	++offsetY;
	++offsetY;
	sStream.str("");
	sStream << "V S";
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);
	++offsetY;
	++offsetY;


	sStream.str("");
	sStream << "Enemy : ";
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	sStream.str("");
	sStream << "HP : " << enemy->GetCurHP() << " / " << enemy->GetMaxHP();
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	sStream.str("");
	sStream << "SP : " << enemy->GetCurSP() << " / " << enemy->GetMaxSP();
	title = sStream.str();
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, title.size(), 1, title);

	++offsetY;

	ratio = enemy->GetCurHP() / enemy->GetMaxHP() * 100.0f;
	temp = "";
	temp.append((10 - (int)(ratio / 10)) * count, ' ');
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upperOpen.size(), 1, upperOpen);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size(), posY + offsetY, enemyHP.size(), 1, enemyHP, WHITE, enemyHPBgColor);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + enemyHP.size(), posY + offsetY, temp.size(), 1, temp, WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + enemyHP.size() + temp.size(), posY + offsetY, upperClose.size(), 1, upperClose);

	++offsetY;

	ratio = enemy->GetCurSP() / enemy->GetMaxSP() * 100.0f;
	temp = "";
	temp.append((10 - (int)(ratio / 10)) * count, ' ');
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upperOpen.size(), 1, upperOpen);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size(), posY + offsetY, enemySP.size(), 1, enemySP, WHITE, CYAN);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + enemySP.size(), posY + offsetY, temp.size(), 1, temp, WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + upperOpen.size() + enemySP.size() + temp.size(), posY + offsetY, upperClose.size(), 1, upperClose);
}
