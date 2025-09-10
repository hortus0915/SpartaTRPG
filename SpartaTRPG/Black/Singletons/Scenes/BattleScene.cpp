#include "BattleScene.h"

#include "../CommonManagers.h"

#include "../../PlayerInfo.h"
#include "../../EnemyInfoBase.h"

#include "../../MainGame.h"
#include "../../CommonFuncs.h"

#include "BattleSceneHud.h"
#include "BattleSceneCardHud.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"

#include <vector>
#include <functional>
#include <cmath>
#include "DungeonScene.h"

//       4       11      19      27
//   * * * * * * * * * * * * * * * * *
//   *       *       *       *       *
//  2*       *       *       *       *
//   *       *       *       *       *
//   * * * * * * * * * * * * * * * * *
//   *       *       *       *       *
//  6*       *       *       *       *
//   *       *       *       *       *
//   * * * * * * * * * * * * * * * * *
//   *       *       *       *       *
// 10*       *       *       *       *
//   *       *       *       *       *
//   * * * * * * * * * * * * * * * * *
//
//   [V] 한칸이동 → [ ] 한칸이동 ← [ ] 한칸이동 ↑ [ ] 한칸이동 ↓
//   
//   [ ] 두칸이동 → [ ] 두칸이동 ← [ ] 막기       [ ] 응급처치
//   
//   [ ] 찌르기     [ ] 십자 베기  [ ] 원형 베기


bool BattleScene::sTutorialShown = false;

void BattleScene::ShowBattleTutorialOnce()
{
	if (sTutorialShown) return;

	auto* lines = new std::vector<std::string>;

	lines->push_back("	■ 전투 튜토리얼");
	lines->push_back(" - Enter 키 선택, BackSpace 키 선택 취소 입니다.");
	lines->push_back(" - 카드 3장을 고르면 한 라운드가 시작됩니다.");
	lines->push_back(" - 우선순위: 이동 → 방어 → 회복 → 공격 ");
	lines->push_back(" - 같은 타입이면 플레이어가 먼저 실행됩니다. ");
	lines->push_back(" - 공격 범위는 플레이어 중앙 기준으로 X 의 위치입니다");
	lines->push_back(" - 카운터: 방어에 성공하면 반격 피해가 발생할 수 있습니다.");
	lines->push_back(" - 라운드 종료 시 SP+15 회복합니다.");
	
	POPUPMANAGER->InitPopup<BattleScene, nullptr>(
		PopupType::RESULTPOPUP, nullptr, lines, 8, 0, 4, 0);

	sTutorialShown = true; 
}

int BattleScene::Init()
{
	
	SOUNDMANAGER->ChangeBGM(Text("BattleSceneBGM.mp3"), 100);

#ifndef DEV_BLACK
	if (!player || !enemy)
	{
		string message = "배틀씬 초기화 오류!!!!";
		SCENEMANAGER->RenderToBackbuffer(0, MAX_SCREEN_HEIGTH, message.size(), 1, message);
		MainGame::Quit();
	}

	currentSelectCount = 0;
	currentActionCount = 0;
	pActionDone = mActionDone = false;
	pShieldUp = mShieldUp = false;

	for (int i = 0; i < cardSelectCount; ++i) {
		playerSelectedIdx[i] = -1;
		playerSelectedCard[i] = nullptr;   
		enemySelectedCard[i] = nullptr;   
		if (cardUi[i]) cardUi[i]->SetCard(nullptr);
	}

#else

	player = new PlayerInfo;
	enemy = new EnemyInfoBase;

	player->Init(100, 100, 10, 10, 1.5f, 50, 50, 0);
	enemy->Init(10, 100, 10, 10, 1.3f, 10, 50, 0);


#endif

	board[0] = "* * * * * * * * * * * * * * * * *";
	board[1] = "*       *       *       *       *";
	board[2] = "*       *       *       *       *";
	board[3] = "*       *       *       *       *";
	board[4] = "* * * * * * * * * * * * * * * * *";
	board[5] = "*       *       *       *       *";
	board[6] = "*       *       *       *       *";
	board[7] = "*       *       *       *       *";
	board[8] = "* * * * * * * * * * * * * * * * *";
	board[9] = "*       *       *       *       *";
	board[10]= "*       *       *       *       *";
	board[11]= "*       *       *       *       *";
	board[12]= "* * * * * * * * * * * * * * * * *";

	currentSequence = !sTutorialShown ? tutorial : (BattleSequence)(None + 2);

	cardSelectCount = 3;
	playerSelectedCard.resize(cardSelectCount);
	playerSelectedIdx.resize(cardSelectCount);
	enemySelectedCard.resize(cardSelectCount);

	currentSelectCount = 0;
	currentActionCount = 0;

	playerCardUseDuration = DEFAULT_TRUN_TIME;
	if (!battleUi)
		battleUi = new BattleSceneHud("BattleScene");

	for (int i = 0; i < cardSelectCount; ++i)
	{
		if (!cardUi[i])
			cardUi[i] = new BattleSceneCardHud("BattleScene");
		cardUi[i]->Init(16 * i, BOARD_HEIGHT + 2);

		playerSelectedIdx[i] = -1;
	}
	if (!cursor)
		cursor = new BlinkCursor("BattleScene");

	int uiOffsetX = 3;
	battleUi->Init(player, enemy, board[0].size() + uiOffsetX, 0);

	player->SetCurSP(player->GetMaxSP());
	CardDB::InitDefaults();

	pPos = { 0, 1 };
	mPos = { 3, 1 };

	CalcRealPos(pPos, pRealPos);
	CalcRealPos(mPos, mRealPos);

#ifndef DEV_BLACK

	pdeck = player->GetDeck();
	mdeck = enemy->GetDeck();

#else

	pdeck = { 101,102,103,104,111,112,201,301,302,401, 402 ,403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414 };
	mdeck = { 101,102,103,104 };

#endif

	P = { player, &pdeck, &pPos };
	M = { enemy, &mdeck, &mPos };

	player->SetCurSP(player->GetMaxSP());
	enemy->SetCurSP(enemy->GetMaxSP());

	damage = 0;
	isGameOver = false;
	playerCardIdx = 0;
	cardsCountInRow = 4;

	playerImage[0] = "   ";
	playerImage[1] = " P ";
	playerImage[2] = "   ";

	enemyImage[0] = "   ";
	enemyImage[1] = " E ";
	enemyImage[2] = "   ";

	CalcRealPos(pPos, pRealPos);
	CalcRealPos(mPos, mRealPos);

	sys.BeginVSP(P);
	sys.BeginVSP(M);

	cardsNum = pdeck.size() / cardsCountInRow + 1;
	if (!cardSelect)
		cardSelect = new string[cardsNum];

	return 0;
}

void BattleScene::Release()
{
	SAFE_RELEASE_DELETE(battleUi);
	for (int i = 0; i < cardSelectCount; ++i)
		SAFE_RELEASE_DELETE(cardUi[i]);
	SAFE_DELETE(cursor);

	SAFE_DELETE_ARR(cardSelect);

	sStream.clear();
}

void BattleScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	if (currentSequence == CardSelect || currentSequence == CardUse)
		sequenceStr.clear();

	switch (currentSequence)
	{
	case tutorial:
	{
		ShowBattleTutorialOnce();

		if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			currentSequence = CardSelect;
		}
	}break;
	case CardSelect:
	{
		battleUi->SetPreviewPlayer(true);
		sequenceStr = "카드를 3장 골라주세요 : Enter 선택 / 백스페이스 취소 ";

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

		if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
		{
			SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
			playerCardIdx = (playerCardIdx - 1 + playerCards.size()) % playerCards.size();
		}
		if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
		{
			SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
			playerCardIdx = (playerCardIdx + 1) % playerCards.size();
		}
		if (KEYMANAGER->IsOnceKeyDown(VK_UP))
		{
			if ((playerCardIdx - cardsCountInRow) >= 0)
			{
				SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
				playerCardIdx = (playerCardIdx - cardsCountInRow + playerCards.size()) % playerCards.size();
			}
		}
		if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
		{
			if ((playerCardIdx + cardsCountInRow) < playerCards.size())
			{
				SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
				playerCardIdx = (playerCardIdx + cardsCountInRow) % playerCards.size();
			}
		}
		for (int i = 0; i < cardSelectCount; ++i)
		{
			if (i == currentSelectCount)
				cardUi[i]->SetCard(playerCards[playerCardIdx]);
			else
			{
				if (playerSelectedIdx[i] == -1)
					cardUi[i]->SetCard(nullptr);
				else
					cardUi[i]->SetCard(playerCards[playerSelectedIdx[i]]);
			}
		}

		int defaultCardLength = 25;
		int idxOffset = 0;
		for (int i = 0; i < cardsNum; ++i)
		{
			sStream.str("");
			for (int j = 0; j < cardsCountInRow; ++j)
			{
				if (j + idxOffset >= playerCards.size()) break;

				string name = playerCards[j + idxOffset]->GetName();
				sStream << "[ ] " << name;
				string nullStr = "";
				nullStr.append(defaultCardLength - (name.size() + 4), ' ');
				sStream << nullStr;
			}
			idxOffset += cardsCountInRow;

			cardSelect[i] = sStream.str();
		}

		int originCardSelectPosX = 0;
		int originCardSelectPosY = BOARD_HEIGHT + 14;
		int cursorPosX = playerCardIdx % cardsCountInRow * defaultCardLength + 1;
		int cursorPosY = (playerCardIdx / cardsCountInRow) * 2;
		cursor->SetPos(originCardSelectPosX + cursorPosX, originCardSelectPosY + cursorPosY);

		if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
		{
			bool isCanSelect = true;
			for (int i = 0; i < currentSelectCount; ++i)
			{
				if (playerSelectedCard[i] == playerCards[playerCardIdx])
				{
					isCanSelect = false;
					break;
				}
			}

			if (isCanSelect && sys.TryPickWithVSP(P, playerCards[playerCardIdx]))
			{
				playerSelectedCard[currentSelectCount] = playerCards[playerCardIdx];
				playerSelectedIdx[currentSelectCount] = playerCardIdx;

				++currentSelectCount;
				if (currentSelectCount >= cardSelectCount)
				{
					currentSequence = CardUse;

					isFirstActionThisRound = false;

					sys.BeginVSP(M);
					int enemySelect = 0;
					for (int i = 0; i < cardSelectCount; ++i)
					{
						int rnd = GetIntRange(0, monsterCards.size() - 1);

						bool isCanSelect = true;
						for (int i = 0; i < enemySelect; ++i)
						{
							if (enemySelectedCard[i] == monsterCards[rnd])
							{
								isCanSelect = false;
								break;
							}
						}

						if (isCanSelect && sys.TryPickWithVSP(M, monsterCards[rnd]))
						{
							enemySelectedCard[i] = monsterCards[rnd];
							++enemySelect;
						}
						else --i;
					}

					playerCardUseCurrentTime = 0.0f;

					currentActionCount = 0;

					pActionDone = false;
					mActionDone = false;

					/* SortCards(playerSelectedCard);
					 SortCards(enemySelectedCard);*/
				}
			}
		}
		// Remove Selected Card
		if (KEYMANAGER->IsOnceKeyDown(VK_BACK))
		{
			const Card* last = playerSelectedCard[currentSelectCount - 1];
			if (last) player->TryApplyVSPCost(-last->GetStaminaCost());
			--currentSelectCount;
			if (currentSelectCount < 0) currentSelectCount = 0;
			playerSelectedIdx[currentSelectCount] = -1;
		}
	}
	break;

	case CardUse:
	{
		battleUi->SetPreviewPlayer(false);

		if (currentActionCount < cardSelectCount)
		{

			static int lastIdx = -1;
			if (lastIdx != currentActionCount) {

				chosen = playerSelectedCard[currentActionCount]; 
				P.card = chosen;
				mChosen = enemySelectedCard[currentActionCount];
				M.card = mChosen;

				playerFirstThisSubturn = (P.card->GetType() <= M.card->GetType());
				subPhase = SubPhase::First;

				pShieldUp = mShieldUp = false;
				pActionDone = mActionDone = false;
				playerCardUseCurrentTime = 0.0f;
				waitingToStartAction = true;
				actionStartTimer = 0.0f;

				lastIdx = currentActionCount;
			}

			if (waitingToStartAction) {
				actionStartTimer += _deltaTime;
				sequenceStr = std::to_string(currentActionCount + 1) + "번째 턴";

				if (actionStartTimer < actionStartGap) break;
				waitingToStartAction = false;
				playerCardUseCurrentTime = 0.0f;
			}


			playerCardUseCurrentTime += _deltaTime;


			auto& A = (playerFirstThisSubturn ? (subPhase == SubPhase::First ? P : M)
				: (subPhase == SubPhase::First ? M : P));
			auto& B = (&A == &P ? M : P);

			if (((A.chr == player) ? pActionDone : mActionDone) && A.card->GetType() == ATTACK)
				sequenceStr = lastActionStr;
			else
				sequenceStr = std::to_string(currentActionCount + 1) + "번째 턴 : ";

			DoAction(A, B, sequenceStr);


			const bool aIsPlayer = (A.chr == player);
			const CardType aType = A.card->GetType();

			bool aFinished = false;
			aFinished = (playerCardUseCurrentTime >= playerCardUseDuration);

			if (aType == MOVE) {

				if (aFinished) {

					if (aIsPlayer)  pRealPos = pMoveEndPos;
					else            mRealPos = mMoveEndPos;
				}
			}

			if (aFinished)
			{
				if (subPhase == SubPhase::First) {
					waitingToStartAction = true;
					actionStartTimer = 0.0f;

					subPhase = SubPhase::Second;
					playerCardUseCurrentTime = 0.0f;
				}
				else {
					const bool playerDead = player->IsDie();
					const bool enemyDead = enemy->IsDie();

					if (playerDead || enemyDead) {
						if (enemyDead && !playerDead) {
							int gain = 0;

							gain = player->GetLevel() * 100;
							player->GainExp(gain);
							currentSequence = PopupSequence;
							vector<string>* temp = new vector<string>();
							temp->push_back(enemy->GetName() + " 처치!");
							temp->push_back("");
							temp->push_back("플레이어 승리! 경험치 +" + std::to_string(gain));
							lastActionStr = sequenceStr;
							LOGMANAGER->AddLog(enemy->GetName() + " 처치!");
							POPUPMANAGER->InitPopup<BattleScene, &BattleScene::ResultVictoryPopupActive>(PopupType::RESULTPOPUP, this, temp, 8, 0, 4, 0);
						}
						else if (playerDead && !enemyDead) {
							currentSequence = PopupSequence;
							vector<string>* temp = new vector<string>();
							temp->push_back("패배... 마을로 돌아갑니다");
							lastActionStr = sequenceStr;
							POPUPMANAGER->InitPopup<BattleScene, &BattleScene::ResultDefeatPopupActive>(PopupType::RESULTPOPUP, this, temp, 8, 0, 4, 0);
						}
						else {
							currentSequence = PopupSequence;
							vector<string>* temp = new vector<string>();
							temp->push_back("무승부");
							temp->push_back("");
							temp->push_back("좋은 승부였지만 더 이상 움직일 힘은 없는 듯 하다.");
							temp->push_back("마을로 돌아갑니다");
							lastActionStr = sequenceStr;
							POPUPMANAGER->InitPopup<BattleScene, &BattleScene::ResultDrawPopupActive>(PopupType::RESULTPOPUP, this, temp, 8, 0, 4, 0);
						}

						waitingToStartAction = false;
						actionStartTimer = 0.0f;
						playerCardUseCurrentTime = 0.0f;

						return;
					}

					++currentActionCount;

					pActionDone = mActionDone = false;
					playerCardUseCurrentTime = 0.0f;

					waitingToStartAction = true;
					actionStartTimer = 0.0f;

					if (currentActionCount >= cardSelectCount)
					{
						currentSelectCount = 0;
						for (int i = 0; i < cardSelectCount; ++i) {
							playerSelectedIdx[i] = -1;
							cardUi[i]->SetCard(nullptr);
						}

						player->AddSP(15);
						enemy->AddSP(15);

						sys.BeginVSP(P);
						sys.BeginVSP(M);
						currentSequence = CardSelect;
					}
					else {
						lastIdx = -1;
					}
				}
			}
		}
	}
	break;
	case Victory:
	{
		if (enemy->GatIsBoss() && isBossStroryPopup == false)
		{
			isBossStroryPopup = true;
			vector<string>* temp = new vector<string>();
			temp->push_back("보스가 쓰러지고, 거대한 방은 고요 속에 잠겼다.");
			temp->push_back("긴 전투의 흔적만이 이곳에 남아 있었다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("플레이어의 이름은 이제 전설이 되었다.");
			temp->push_back("그동안 조롱하던 탈주닌자 핑크조차, 고개를 숙이며 그 용기를 인정했다.");
			temp->push_back("");
			temp->push_back("세상은 다시 평화를 되찾았다.");
			temp->push_back("무너졌던 마을은 활기를 되찾고, 길 위에는 다시 노랫소리가 울려 퍼졌다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("이 승리는 혼자가 아닌, 함께였기에 가능했다. ");
			temp->push_back("곁을 지켜준 동료가 있었고, 그 믿음이 마지막 디버깅의 힘이 되었다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("그리고 이제...");
			temp->push_back("모험은 끝났지만, 진짜 여정은 시작된다");
			temp->push_back("더 깊은 도전, 더 큰 세계, 그리고 ‘언리얼’이라는 새로운 전투가 기다린다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("지금까지의 시간은 모두 준비였다. ");
			temp->push_back("이제는 진짜 언리얼 무대를 향해 나아가라. ");
			lastActionStr = sequenceStr;

			POPUPMANAGER->InitPopup<BattleScene, &BattleScene::GameEnd>(PopupType::RESULTPOPUP, this, temp, 8, 0, 4, 0);
		}
		else
		{
			auto dungeon = (DungeonScene*)SCENEMANAGER->FindChild("GameScene", "DungeonScene");
			SCENEMANAGER->ChangeChild("DungeonScene");
			dungeon->SetVictory();
			SCENEMANAGER->CurrentSceneInit();
		}
	}
	break;
	case Defeat:
	case Draw:
	{
		if (enemy->GatIsBoss() && isBossStroryPopup == false)
		{
			isBossStroryPopup = true;
			LOGMANAGER->AddLog("플레이어 사망");
			vector<string>* temp = new vector<string>();
			temp->push_back("보스의 일격에 쓰러지고 말았다...");
			temp->push_back("차갑고 무거운 기운이 온몸을 짓눌렀다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("보스: 하찮구나... 아직 나와 맞설 힘조차 없구나.");
			temp->push_back("더 강해져서 돌아와라. 그렇지 않다면, 이 문턱조차 넘지 못하리라.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("어디선가 나타난 핑크가 쓰러진 레인져를 부축해준다");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("탈주닌자 핑크: …봐라. 이게 현실이다.");
			temp->push_back("하지만 쓰러졌다고 끝난 건 아니다.");
			temp->push_back("언젠가 반드시 다시 일어서라. 그게 진짜 레인저다.");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("");
			temp->push_back("시스템: 보스전에서 패배했습니다.");
			temp->push_back("시스템: 마을로 귀환합니다.");
			lastActionStr = sequenceStr;
			POPUPMANAGER->InitPopup<BattleScene, &BattleScene::BossFail>(PopupType::RESULTPOPUP, this, temp, 8, 0, 4, 0);
		}
		else
		{
			LOGMANAGER->AddLog("플레이어 사망");

			sequenceStr = lastActionStr;
			auto dungeon = (DungeonScene*)SCENEMANAGER->FindChild("GameScene", "DungeonScene");
			SCENEMANAGER->ChangeChild("DungeonScene");
			dungeon->SetDefeat();
			SCENEMANAGER->CurrentSceneInit();
		}
	}
	break;
	case BattleEnd:
	{
		
	}break;
	}
}

void BattleScene::GameEnd(int _selected)
{
	isBossStroryPopup = false;
	SCENEMANAGER->ChangeScene("EndScene");
	SCENEMANAGER->CurrentSceneInit();
}

void BattleScene::BossFail(int _selected)
{
	isBossStroryPopup = false;
	LOGMANAGER->AddLog("플레이어 사망");
	sequenceStr = lastActionStr;
	auto dungeon = (DungeonScene*)SCENEMANAGER->FindChild("GameScene", "DungeonScene");
	SCENEMANAGER->ChangeChild("DungeonScene");
	dungeon->SetDefeat();
	SCENEMANAGER->CurrentSceneInit();
}

void BattleScene::Render()
{
	__super::Render();

	for (int i = 0; i < BOARD_HEIGHT; ++i)
	{
		SCENEMANAGER->RenderToBackbuffer(0, i, board[i].size(), 1, board[i]);
	}

	if (mRealPos.x == pRealPos.x &&
		mRealPos.y == pRealPos.y)
	{
		playerImage[0] = "   ";
		playerImage[1] = "P E";
		playerImage[2] = "   ";

		for (int i = 0; i < 3; ++i)
		{
			SCENEMANAGER->RenderToBackbuffer(pRealPos.x - 1, pRealPos.y - 1 + i, playerImage[i].size(), 1, playerImage[i], WHITE, DARKYELLOW);
		}
	}
	else
	{
		playerImage[0] = "   ";
		playerImage[1] = " P ";
		playerImage[2] = "   ";

		for (int i = 0; i < 3; ++i)
		{
			SCENEMANAGER->RenderToBackbuffer(pRealPos.x - 1, pRealPos.y - 1 + i, playerImage[i].size(), 1, playerImage[i], WHITE, DARKGREEN);
			SCENEMANAGER->RenderToBackbuffer(mRealPos.x - 1, mRealPos.y - 1 + i, enemyImage[i].size(), 1, enemyImage[i], WHITE, DARKRED);
		}
	}

	int originCardSelectPosX = 0;
	int originCardSelectPosY = BOARD_HEIGHT + 14;
	for (int i = 0; i < cardsNum; ++i)
	{
		SCENEMANAGER->RenderToBackbuffer(originCardSelectPosX, originCardSelectPosY + 2 * i, cardSelect[i].size(), 1, cardSelect[i]);
	}

	SCENEMANAGER->RenderToBackbuffer(0, BOARD_HEIGHT + 1, sequenceStr.size(), 1, sequenceStr);

	string selected = "V";
	for (int i = 0; i < cardSelectCount; ++i)
	{
		if (playerSelectedIdx[i] == -1) continue;

		int defaultCardLength = 25;
		int originCardSelectPosX = 0;
		int originCardSelectPosY = BOARD_HEIGHT + 14;
		int cursorPosX = playerSelectedIdx[i] % cardsCountInRow * defaultCardLength + 1;
		int cursorPosY = (playerSelectedIdx[i] / cardsCountInRow) * 2;

		SCENEMANAGER->RenderToBackbuffer(originCardSelectPosX + cursorPosX, originCardSelectPosY + cursorPosY, selected.size(), 1, selected);
	}

	if (cursor)
		cursor->Render();

}

void BattleScene::CalcRealPos(const Board::Pos& pos, Board::Pos& realPos)
{
	realPos.x = pos.x * 8 + 4;
	//if (pos.x == 0) --realPos.x;
	realPos.y = pos.y * 4 + 2;
}

void BattleScene::SortCards(vector<const Card*>& selected)
{
	set<const Card*> du;
	for (int i = 0; i < cardSelectCount; ++i)
	{
		if (selected[i]->GetType() == ATTACK)
		{
			if (du.find(selected[i]) == du.end())
			{
				const Card* temp = selected[i];
				selected.erase(selected.begin() + i);
				selected.push_back(temp);
				du.insert(temp);
				--i;
			}
		}
	}
}

void BattleScene::CreateEffect(const int& cardId, const vector<Board::Pos>& pos, const Board::Pos& originPos)
{
	if (cardId == 401 ||
		cardId == 405)
	{
		int min = pos[0].x, max = pos[0].x;
		for (int i = 1; i < pos.size(); ++i)
		{
			if (pos[i].x > max)
				max = pos[i].x;
			if (pos[i].x < min)
				min = pos[i].x;
		}

		Board::Pos startPos = { min, pos[0].y };
		Board::Pos startRealPos;
		Board::Pos endPos = { max, pos[0].y };
		Board::Pos endRealPos;

		CalcRealPos(startPos, startRealPos);
		CalcRealPos(endPos, endRealPos);

		EFFECTMANAGER->StartEffect(Slash, startRealPos.x, startRealPos.y, endRealPos.x, endRealPos.y);
	}
	else if (cardId == 402 ||
		cardId == 403 ||
		cardId == 406 ||
		cardId == 407)
	{
		for (int i = 0; i < pos.size(); ++i)
		{
			Board::Pos real;
			CalcRealPos(pos[i], real);

			EFFECTMANAGER->StartEffect(Tail_Slash, real.x, real.y, real.x, real.y);
		}
	}
	else if (cardId == 404)
	{
		int min = pos[0].y, max = pos[0].y;
		for (int i = 1; i < pos.size(); ++i)
		{
			if (pos[i].y > max)
				max = pos[i].y;
			if (pos[i].y < min)
				min = pos[i].y;
		}

		Board::Pos startPos = { pos[0].x, min };
		Board::Pos startRealPos;
		Board::Pos endPos = { pos[0].x, max };
		Board::Pos endRealPos;

		CalcRealPos(startPos, startRealPos);
		CalcRealPos(endPos, endRealPos);

		EFFECTMANAGER->StartEffect(Slash, startRealPos.x, startRealPos.y, endRealPos.x, endRealPos.y);
	}
	else if (cardId == 408)
	{
		for (int i = 0; i < pos.size(); ++i)
		{
			Board::Pos real;
			CalcRealPos(pos[i], real);

			EFFECTMANAGER->StartEffect(Tail_Explosion, originPos.x, originPos.y, real.x, real.y);
		}
	}
	else if (cardId == 409 ||
		cardId == 410 ||
		cardId == 411 ||
		cardId == 412)
	{
		for (int i = 0; i < pos.size(); ++i)
		{
			Board::Pos real;
			CalcRealPos(pos[i], real);

			EFFECTMANAGER->StartEffect(Slash, originPos.x, originPos.y, real.x, real.y);
		}
	}
	else if (cardId == 413 ||
		cardId == 414)
	{
		for (int i = 0; i < pos.size(); ++i)
		{
			Board::Pos real;
			CalcRealPos(pos[i], real);

			EFFECTMANAGER->StartEffect(Explosion, real.x - 2, real.y - 2);
		}
	}
}

void BattleScene::DoAction(BattleSystem::Side& _actor, BattleSystem::Side& _target, std::string& _outStr)
{
	switch (_actor.card->GetType())
	{
	case SHIELD:
	{
		CalcRealPos((*_actor.pos), (_actor.chr == player ? pRealPos : mRealPos));
		if (_actor.chr == player) pShieldUp = true;
		else                      mShieldUp = true;

		string actorName = _actor.chr->GetName();
		if (actorName.empty()) actorName = (_actor.chr == player ? "플레이어" : "적");

		_outStr += actorName + " : " + _actor.card->GetName();
	} break;

	case MOVE:
	{
		float ratio = Clamp(0.0f, 1.0f, (playerCardUseCurrentTime / playerCardUseDuration) * 2.5f);

		if (_actor.chr == player)
		{
			if (!pActionDone)
			{
				CalcRealPos((*_actor.pos), pMoveStartPos);
				sys.MovoToCharacter(_actor);
				CalcRealPos((*_actor.pos), pMoveEndPos);
				pActionDone = true;
			}

			pRealPos.x = Lerp(pMoveStartPos.x, pMoveEndPos.x, ratio);
			pRealPos.y = Lerp(pMoveStartPos.y, pMoveEndPos.y, ratio);

		}
		else
		{
			if (!mActionDone)
			{
				CalcRealPos((*_actor.pos), mMoveStartPos);
				sys.MovoToCharacter(_actor);
				CalcRealPos((*_actor.pos), mMoveEndPos);
				mActionDone = true;
			}

			mRealPos.x = Lerp(mMoveStartPos.x, mMoveEndPos.x, ratio);
			mRealPos.y = Lerp(mMoveStartPos.y, mMoveEndPos.y, ratio);

		}

		string actorName = _actor.chr->GetName();
		if (actorName.empty()) actorName = (_actor.chr == player ? "플레이어" : "적");
		_outStr += actorName + " : " + _actor.card->GetName();
	} break;

	case HEAL:
	{
		CalcRealPos((*_actor.pos), (_actor.chr == player ? pRealPos : mRealPos));
		if ((_actor.chr == player && !pActionDone) || (_actor.chr != player && !mActionDone))
		{
			sStream.str("");
			sys.HealToCharacter(_actor, sStream);
			if (_actor.chr == player) pActionDone = true;
			else                      mActionDone = true;
		}
		string actorName = _actor.chr->GetName();
		if (actorName.empty()) actorName = (_actor.chr == player ? "플레이어" : "적");

		_outStr += actorName + " : " + _actor.card->GetName() + " " + sStream.str();
	
	} break;

	case ATTACK:
	{
		CalcRealPos((*_actor.pos), (_actor.chr == player ? pRealPos : mRealPos));

		float raw = 0.0f, real = 0.0f;
		float counter = 0.0f;

		bool usedShield = (_target.chr == player ? pShieldUp : mShieldUp);
		bool isMiss = false;
		bool isDodge = false;
		bool fullBlocked = false;
		bool shieldReduce = false;
		bool isCrit = false;

		if ((_actor.chr == player && !pActionDone) || (_actor.chr != player && !mActionDone))
		{
			std::vector<Board::Pos> effectPos;
			raw = (float)sys.AttackToCharacter(_actor, _target, effectPos, &isCrit);


			if (raw <= 0.0f) {

				isMiss = true;
			}
			else {

				float finalAtk = raw;
				if (usedShield) {
					sys.ShieldToCharacter(_target, _actor, raw, finalAtk, counter);
				}

				real = _target.chr->HitDamager(finalAtk);
				if (counter > 0.0f)
				{
					_actor.chr->HitDamager(counter);
				}

				if (real <= 0.0f)
				{
					fullBlocked = usedShield; isDodge = !usedShield;
				}
				else
				{
					if (usedShield) shieldReduce = true;
				}
			}

			CreateEffect(_actor.card->GetIdx(), effectPos, (_actor.chr == player ? pRealPos : mRealPos));

			string actorName = _actor.chr->GetName();
			if (actorName.empty()) actorName = (_actor.chr == player ? "플레이어" : "적");

			std::string defenderName = _target.chr->GetName();
			if (defenderName.empty()) defenderName = (_target.chr == player ? "플레이어" : "적");

			_outStr += actorName + " : " + _actor.card->GetName() + " 공격!(";


			if (isMiss) {
				_outStr += "빗나감)";
			}
			else if (isDodge) {
				_outStr += "적 회피!)";
			}
			else {
				if (real <= 0.0f && usedShield) {
					_outStr += "방어로 막힘!";
				}
				else {
					_outStr += "데미지 : " + std::to_string((int)std::floor(real));
				}

				if (isCrit)        _outStr += " / 치명!";
				if (shieldReduce && real > 0.0f) _outStr += " / 방어로 감소";
				if (counter > 0.0f)
					_outStr += " / " + defenderName + "의 반격! " + actorName + " -" + std::to_string((int)std::floor(counter));

				_outStr += ")";
			}

			lastActionStr = _outStr;

			if (_actor.chr == player) pActionDone = true;
			else                      mActionDone = true;


		}
		

	
	} break;
	}
}

void BattleScene::ResultVictoryPopupActive(int selected)
{
	currentSequence = Victory;
}

void BattleScene::ResultDrawPopupActive(int selected)
{
	currentSequence = Draw;
}

void BattleScene::ResultDefeatPopupActive(int selected)
{
	currentSequence = Defeat;
}


