#include "BattleScene.h"

#include "../CommonManagers.h"

#include "../../PlayerInfo.h"
#include "../../EnemyInfoBase.h"

#include "../../MainGame.h"
#include "../../CommonFuncs.h"

#include "../../DevBlack.h"

#include "BattleSceneHud.h"
#include "BattleSceneCardHud.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"

#include <vector>
#include <functional>
#include <cmath>

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
#else

    player = new PlayerInfo;
    enemy = new EnemyInfoBase;

    player->Init(100, 1000, 10, 50, 1.5f, 50, 50, 0);
    enemy->Init(80, 1000, 10, 50, 1.3f, 50, 50, 0);

#endif
    
    board[0]  = "* * * * * * * * * * * * * * * * *";
    board[1]  = "*       *       *       *       *";
    board[2]  = "*       *       *       *       *";
    board[3]  = "*       *       *       *       *";
    board[4]  = "* * * * * * * * * * * * * * * * *";
    board[5]  = "*       *       *       *       *";
    board[6]  = "*       *       *       *       *";
    board[7]  = "*       *       *       *       *";
    board[8]  = "* * * * * * * * * * * * * * * * *";
    board[9]  = "*       *       *       *       *";
    board[10] = "*       *       *       *       *";
    board[11] = "*       *       *       *       *";
    board[12] = "* * * * * * * * * * * * * * * * *";

    currentSequence = (BattleSequence)(None + 1);

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

    CardDB::InitDefaults();

    pPos = { 0, 1 };
    mPos = { 3, 1 };

    CalcRealPos(pPos, pRealPos);
    CalcRealPos(mPos, mRealPos);

#ifndef DEV_BLACK

    pdeck = player->GetDeck();
    mdeck = enemy->GetDeck();

#else

    pdeck = { 101,102,103,104,111,112,201,301,401, 402 ,403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414 };
    mdeck = { 101,102,103,104,201,202,203,301,401,402,404 };

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

    return 0;
}

void BattleScene::Release()
{
    SAFE_RELEASE_DELETE(battleUi);
    for (int i = 0; i < cardSelectCount; ++i)
        SAFE_RELEASE_DELETE(cardUi[i]);
    SAFE_DELETE(cursor);

    sStream.clear();
}

void BattleScene::Update(float _deltaTime)
{
    __super::Update(_deltaTime);

    sequenceStr = "";
    switch (currentSequence)
    {
        case CardSelect:
        {
            sequenceStr = "카드를 3장 골라주세요 : Enter 선택 / 백스페이스 취소  ※ 공격은 먼저 골라도 후순위로 사용됩니다.";

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
                playerCardIdx = (playerCardIdx - 1 + playerCards.size()) % playerCards.size();
            }
            if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
            {
                playerCardIdx = (playerCardIdx + 1) % playerCards.size();
            }
            if (KEYMANAGER->IsOnceKeyDown(VK_UP))
            {
                if ((playerCardIdx - cardsCountInRow) >= 0)
                    playerCardIdx = (playerCardIdx - cardsCountInRow + playerCards.size()) % playerCards.size();
            }
            if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
            {
                if ((playerCardIdx + cardsCountInRow) < playerCards.size())
                    playerCardIdx = (playerCardIdx + cardsCountInRow) % playerCards.size();
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
            
            int defaultCardLength = 20;
            int idxOffset = 0;
            for (int i = 0; i < 3; ++i)
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

                        SortCards(playerSelectedCard);
                        SortCards(enemySelectedCard);
                    }
                }
            }
            // Remove Selected Card
            if (KEYMANAGER->IsOnceKeyDown(VK_BACK))
            {
                player->TryApplyVSPCost(-playerCards[currentSelectCount]->GetStaminaCost());
                --currentSelectCount;
                if (currentSelectCount < 0)
                    currentSelectCount = 0;

                playerSelectedIdx[currentSelectCount] = -1;
            }
        }
        break;

        case CardUse:
        {
            if (currentActionCount < cardSelectCount)
            {
                if (playerCardUseCurrentTime < playerCardUseDuration)
                {
                    sequenceStr = to_string(currentActionCount) + "번째 턴 : ";

                    playerCardUseCurrentTime += _deltaTime;

                    chosen = playerSelectedCard[currentActionCount];
                    P.card = chosen;
                    mChosen = enemySelectedCard[currentActionCount];
                    M.card = mChosen;

                    float ratio = playerCardUseCurrentTime / playerCardUseDuration;
                    switch (P.card->GetType())
                    {
                        case SHIELD:

                            CalcRealPos((*P.pos), pRealPos);

                            sequenceStr += "플레이어 " + P.card->GetName();
                        break;

                        case MOVE:
                            ratio = Clamp(0.0f, 1.0f, ratio);
                            if (!pActionDone)
                            {
                                CalcRealPos((*P.pos), pMoveStartPos);
                                sys.MovoToCharacter(P);
                                CalcRealPos((*P.pos), pMoveEndPos);

                                pActionDone = true;
                            }

                            pRealPos.x = Lerp(pMoveStartPos.x, pMoveEndPos.x, ratio);
                            pRealPos.y = Lerp(pMoveStartPos.y, pMoveEndPos.y, ratio);

                            sequenceStr += "플레이어 " + P.card->GetName();
                        break;

                        case HEAL:

                            CalcRealPos((*P.pos), pRealPos);

                            if (!pActionDone)
                            {
                                sStream.str("");
                                sys.HealToCharacter(P, sStream);

                                pActionDone = true;
                            }

                            sequenceStr += sStream.str();
                        break;

                        case ATTACK:

                            CalcRealPos((*P.pos), pRealPos);

                            if (!pActionDone)
                            {
                                vector<Board::Pos> effectPos;
                                playerAttackDamage = (float)sys.AttackToCharacter(P, M, effectPos);
                                if (playerAttackDamage > 0)
                                {
                                    if (M.card->GetType() == SHIELD)
                                    {
                                        sys.ShieldToCharacter(M, P, playerAttackDamage, playerAttackDamage, enemyAttackDamage);
                                    }
                                
                                    playerAttackRealDamage = M.chr->HitDamager(playerAttackDamage);
                                }

                                CreateEffect(P.card->GetIdx(), effectPos, pRealPos);

                                pActionDone = true;
                            }

                            sequenceStr += "플레이어 " + P.card->GetName() + " 공격!" + "(";

                            if (playerAttackRealDamage > 0)
                                sequenceStr += "데미지 : " + to_string(floor(playerAttackRealDamage)) + (M.card->GetType() == SHIELD ? "/ 적 " + M.card->GetName() : "") + ")";
                            else
                            {
                                if (playerAttackDamage > 0 && playerAttackRealDamage <= 0)
                                    sequenceStr += "적 회피!)";
                                else if (playerAttackDamage <= 0)
                                    sequenceStr += "빗나감!)";
                            }
                        break;
                    }

                    sequenceStr += " / ";

                    ratio = playerCardUseCurrentTime / playerCardUseDuration;
                    switch (M.card->GetType())
                    {
                        case SHIELD:

                            CalcRealPos((*M.pos), mRealPos);

                        break;

                        case MOVE:
                            ratio = Clamp(0.0f, 1.0f, ratio);
                            if (!mActionDone)
                            {
                                CalcRealPos((*M.pos), mMoveStartPos);
                                sys.MovoToCharacter(M);
                                CalcRealPos((*M.pos), mMoveEndPos);

                                mActionDone = true;
                            }

                            mRealPos.x = Lerp(mMoveStartPos.x, mMoveEndPos.x, ratio);
                            mRealPos.y = Lerp(mMoveStartPos.y, mMoveEndPos.y, ratio);

                            sequenceStr += "적 " + M.card->GetName();
                        break;

                        case HEAL:

                            CalcRealPos((*M.pos), mRealPos);

                            if (!mActionDone)
                            {
                                sStream.str("");
                                sys.HealToCharacter(M, sStream);

                                mActionDone = true;
                            }

                            sequenceStr += sStream.str();
                        break;

                        case ATTACK:

                            CalcRealPos((*M.pos), mRealPos);

                            if (!mActionDone)
                            {
                                vector<Board::Pos> effectPos;
                                enemyAttackDamage = (float)sys.AttackToCharacter(M, P, effectPos);
                                if (enemyAttackDamage > 0)
                                {
                                    if (M.card->GetType() == SHIELD)
                                    {
                                        sys.ShieldToCharacter(P, M, enemyAttackDamage, enemyAttackDamage, playerAttackDamage);
                                    }

                                    enemyAttackRealDamage = P.chr->HitDamager(enemyAttackDamage);
                                }

                                CreateEffect(P.card->GetIdx(), effectPos, mRealPos);

                                mActionDone = true;
                            }

                            sequenceStr += "적 " + M.card->GetName() + " 공격!" + "(";

                            if (enemyAttackRealDamage > 0)
                                sequenceStr += "데미지 : " + to_string(floor(enemyAttackRealDamage)) + (P.card->GetType() == SHIELD ? "/ 플레이어 " + P.card->GetName() : "") + ")";
                            else
                            {
                                if (enemyAttackDamage > 0 && enemyAttackRealDamage <= 0)
                                    sequenceStr += "적 회피!)";
                                else if (enemyAttackDamage <= 0)
                                    sequenceStr += "빗나감!)";
                            }
                        break;
                    }

                    if (playerCardUseCurrentTime >= playerCardUseDuration)
                    {
                        playerCardUseCurrentTime = 0.0f;
                        ++currentActionCount;

                        pActionDone = false;
                        mActionDone = false;

                        if (currentActionCount >= cardSelectCount)
                        {
                            currentSelectCount = 0;

                            for (int i = 0; i < cardSelectCount; ++i)
                            {
                                playerSelectedIdx[i] = -1;
                            }

                            for (int i = 0; i < cardSelectCount; ++i)
                            {
                                cardUi[i]->SetCard(nullptr);
                            }

                            if (player->IsDie() || enemy->IsDie())
                                currentSequence = BattleEnd;
                            else
                            {
                                sys.BeginVSP(P);
                                sys.BeginVSP(M);

                                currentSequence = CardSelect;
                            }
                        }
                    }
                }
            }
        }
        break;

        case BattleEnd:
        {

        }
        break;
    }
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
    for (int i = 0; i < 3; ++i)
    {
        SCENEMANAGER->RenderToBackbuffer(originCardSelectPosX, originCardSelectPosY + 2 * i, cardSelect[i].size(), 1, cardSelect[i]);
    }

    SCENEMANAGER->RenderToBackbuffer(0, BOARD_HEIGHT + 1, sequenceStr.size(), 1, sequenceStr);

    string selected = "V";
    for (int i = 0; i < cardSelectCount; ++i)
    {
        if (playerSelectedIdx[i] == -1) continue;

        int defaultCardLength = 20;
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
