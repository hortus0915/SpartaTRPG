#include "BattleSceneCardHud.h"

// --------------
// 이동
// Cost : 10
// 타입 : 이동
// Desc
// --------------

#include "../CommonManagers.h"
#include "../../../Blue/Card/CardDB.h"
#include "../../PlayerInfo.h"

string BattleSceneCardHud::upper = "--------------";
string BattleSceneCardHud::lower = "--------------";

void BattleSceneCardHud::Init(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;
}

void BattleSceneCardHud::Release()
{
	sStream.clear();
}

void BattleSceneCardHud::Render()
{
	if (!currentCard) return;

	int offsetY = 0;
	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upper.size(), 1, upper);
	++offsetY;
	switch (currentCard->GetType())
	{
		case MOVE:
		{
			const char* arrows[9] =
			{
				 "↖","↑","↗",
				 "←"," ","→",
				 "↙","↓","↘"
			};

			int dirIdx = 4;
			for (int i = 0; i < 9; ++i) {
				if (currentCard->GetRange() & (1u << i)) { dirIdx = i; break; }
			}

			TITLE = currentCard->GetName();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TITLE.size(), 1, TITLE);
			++offsetY;

			sStream.str("");
			sStream << "코스트 : " << currentCard->GetStaminaCost();
			COST = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, COST.size(), 1, COST);
			++offsetY;

			TYPE = "타입 : 이동";
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TYPE.size(), 1, TYPE);
			++offsetY;

			DESC = string(arrows[dirIdx]) + " " + to_string((int)currentCard->GetDamageRate()) + "칸";
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
			++offsetY;

			for (int i = 0; i < 4; ++i)
				++offsetY;
		}
		break;

		case ATTACK:
		{
			TITLE = currentCard->GetName();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TITLE.size(), 1, TITLE);
			++offsetY;
			
			sStream.str("");
			sStream << "코스트 : " << currentCard->GetStaminaCost();
			COST = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, COST.size(), 1, COST);
			++offsetY;

			TYPE = "타입 : 공격";
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TYPE.size(), 1, TYPE);
			++offsetY;

			float playerAtk = 0.0f;
			if (auto* pl = USERMANAGER->GetPlayer()) {
	
				playerAtk = pl->GetBaseDamage();
			}
			int shownDamage = (int)std::round(playerAtk * currentCard->GetDamageRate());

			sStream.str("");
			sStream << "공격력 : " << shownDamage;
			DESC = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
			++offsetY;

			sStream.str("");
			sStream << "공격범위";
			DESC = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
			++offsetY;

			for (int i = 0; i < 9; i++)
			{
				if (currentCard->GetRange() & (1u << i))
					attackRange[i] = "[X]";
				else
					attackRange[i] = "[ ]";
			}

			for (int i = 0; i < 3; ++i)
			{
				DESC = attackRange[0 + i * 3] + attackRange[1 + i * 3] + attackRange[2 + i * 3];
				SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
				++offsetY;
			}
		}
		break;

		case SHIELD:
		{
			TITLE = currentCard->GetName();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TITLE.size(), 1, TITLE);
			++offsetY;

			sStream.str("");
			sStream << "코스트 : " << currentCard->GetStaminaCost();
			COST = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, COST.size(), 1, COST);
			++offsetY;

			TYPE = "타입 : 방어";
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TYPE.size(), 1, TYPE);
			++offsetY;

			sStream.str("");
			sStream << "방어 : " << (int)(currentCard->GetDamageRate() * 100) << "%";
			DESC = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
			++offsetY;

			for (int i = 0; i < 4; ++i)
				++offsetY;
		}
		break;

		case HEAL:
		{
			int count = 5;
			TITLE = currentCard->GetName();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TITLE.size(), 1, TITLE);
			++offsetY;

			sStream.str("");
			sStream << "코스트 : " << ((currentCard->GetStaminaCost() > 0) ? currentCard->GetStaminaCost() : 0);
			COST = sStream.str();
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, COST.size(), 1, COST);
			++offsetY;

			TYPE = "타입 : 힐";
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TYPE.size(), 1, TYPE);
			++offsetY;

			bool hpHeal = (currentCard->GetDamageRate() > 0.0f);
			bool spHeal = (currentCard->GetStaminaCost() < 0);
			if (hpHeal)
			{
				sStream.str("");
				sStream << "체력 + " << (int)currentCard->GetDamageRate();
				DESC = sStream.str();
				SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, DESC.size(), 1, DESC);
				++offsetY;
				--count;
			}
			if (spHeal)
			{
				sStream.str("");
				sStream << "마나 + " << ((int)-currentCard->GetStaminaCost());
				attackRange[0] = sStream.str();
				SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, attackRange[0].size(), 1, attackRange[0]);
				++offsetY;
				--count;
			}

			for (int i = 0; i < count; ++i)
				++offsetY;
		}
		break;
	}

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, lower.size(), 1, lower);

}
