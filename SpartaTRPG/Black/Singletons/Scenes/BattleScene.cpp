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

#include <vector>
#include <functional>
#include <cmath>

#define DEV_BLACK 0

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

    player->Init(100, 10, 10, 50, 1.5f, 50, 50, 0);
    enemy->Init(80, 10, 10, 50, 1.3f, 50, 50, 0);

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

    playerCardUseDuration = enemyCardUseDuration = DEFAULT_TRUN_TIME;
    if (!battleUi)
        battleUi = new BattleSceneHud("BattleScene");
    if (!cardUi)
        cardUi = new BattleSceneCardHud("BattleScene");
    if (!cursor)
        cursor = new BlinkCursor("BattleScene");

    int uiOffsetX = 3;
    battleUi->Init(player, enemy, board[0].size() + uiOffsetX, 0);
    cardUi->Init(0, BOARD_HEIGHT + 2);

    CardDB::InitDefaults();

    pPos = { 0, 1 };
    mPos = { 3, 1 };

    CalcRealPos(pPos, pRealPos);
    CalcRealPos(mPos, mRealPos);

    pdeck = { 101,102,103,104,111,112,201,301,401 ,403,408 };
    mdeck = { 101,102,103,104,201,202,203,301,401,402,404 };

    P = { player, &pdeck, &pPos };
    M = { enemy, &mdeck, &mPos };

    damage = 0;
    isGameOver = false;
    playerCardIdx = 0;
    cardsCountInRow = 4;

    playerImage[0] = "ooo";
    playerImage[1] = "oPo";
    playerImage[2] = "ooo";

    enemyImage[0] = "xxx";
    enemyImage[1] = "xEx";
    enemyImage[2] = "xxx";

    CalcRealPos(pPos, pRealPos);
    CalcRealPos(mPos, mRealPos);

    return 0;
}

void BattleScene::Release()
{
    SAFE_RELEASE_DELETE(battleUi);
    SAFE_RELEASE_DELETE(cardUi);
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
            sequenceStr = "카드를 골라주세요.";

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
            cardUi->SetCard(playerCards[playerCardIdx]);

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
                currentSequence = CardUse;

                chosen = playerCards[playerCardIdx];
                P.card = chosen;
                mChosen = monsterCards[GetIntRange(0, monsterCards.size() - 1)];
                M.card = mChosen;

                playerCardUseCurrentTime = 0.0f;
                enemyCardUseCurrentTime = 0.0f;

                pActionDone = false;
                mActionDone = false;
            }
        }
        break;

        case CardUse:
        {
            if (playerCardUseCurrentTime < playerCardUseDuration)
            {
                sequenceStr = "플레이어 턴 : ";

                playerCardUseCurrentTime += _deltaTime;

                float ratio = playerCardUseCurrentTime / playerCardUseDuration;
                switch (P.card->GetType())
                {
                    case MOVE:
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
                        if (!pActionDone)
                        {
                            sStream.str("");
                            sys.HealToCharacter(P, sStream);

                            pActionDone = true;
                        }

                        sequenceStr += sStream.str();
                    break;

                    case ATTACK:
                        if (!pActionDone)
                        {
                            //playerAttackDamage = (float)sys.AttackToCharacter(P, M);
                            //if (playerAttackDamage > 0)
                            //{
                            //    if (M.card->GetType() == SHIELD)
                            //    {
                            //        sys.ShieldToCharacter(M, P, playerAttackDamage, playerAttackDamage, enemyAttackDamage);
                            //    }
                            //    
                            //    if (M.chr->HitDamager(playerAttackDamage))
                            //    {
                            //        battleUi->UpdateUI();
                            //    }
                            //}

                            pActionDone = true;
                        }

                        sequenceStr += "플레이어 " + P.card->GetName() + " 공격!" + "(";

                        if (playerAttackDamage > 0) sequenceStr += "데미지 : " + to_string(floor(playerAttackDamage)) + ")";
                        else sequenceStr += "빗나감!)";
                    break;
                }
            }
            else
            {
                if (enemyCardUseCurrentTime < enemyCardUseDuration)
                {
                    enemyCardUseCurrentTime += _deltaTime;

                    float ratio = enemyCardUseCurrentTime / enemyCardUseDuration;
                    ratio = Clamp(0.0f, 1.0f, ratio);
                    switch (M.card->GetType())
                    {
                        case MOVE:
                            if (!mActionDone)
                            {
                                CalcRealPos((*M.pos), mMoveStartPos);
                                sys.MovoToCharacter(M);
                                CalcRealPos((*M.pos), mMoveEndPos);

                                mActionDone = true;
                            }

                            mRealPos.x = Lerp(mMoveStartPos.x, mMoveEndPos.x, ratio);
                            mRealPos.y = Lerp(mMoveStartPos.y, mMoveEndPos.y, ratio);
                        break;

                        case HEAL:
                            if (!mActionDone)
                            {
                                sStream.str("");
                                sys.HealToCharacter(M, sStream);

                                mActionDone = true;
                            }
                        break;

                        case ATTACK:
                            if (!mActionDone)
                            {
                                //enemyAttackDamage = (float)sys.AttackToCharacter(M, P);
                                //if (enemyAttackDamage > 0)
                                //{
                                //    if (M.card->GetType() == SHIELD)
                                //    {
                                //        sys.ShieldToCharacter(P, M, enemyAttackDamage, enemyAttackDamage, playerAttackDamage);
                                //    }

                                //    if (P.chr->HitDamager(enemyAttackDamage))
                                //    {
                                //        battleUi->UpdateUI();
                                //    }
                                //}

                                mActionDone = true;
                            }

                            sequenceStr += "적 " + M.card->GetName() + " 공격!" + "(";

                            if (enemyAttackDamage > 0) sequenceStr += "데미지 : " + to_string(floor(enemyAttackDamage)) + ")";
                            else sequenceStr += "빗나감!)";
                        break;
                    }
                }
                else
                {
                    if (P.chr->GetCurHP() != 0 && M.chr->GetCurHP() != 0)
                    {
                        currentSequence = CardSelect;
                    }
                    else
                    {
                        currentSequence = BattleEnd;
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

    for (int i = 0; i < 3; ++i)
    {
        SCENEMANAGER->RenderToBackbuffer(pRealPos.x - 1, pRealPos.y - 1 + i, playerImage[i].size(), 1, playerImage[i], WHITE, DARKGREEN);
        SCENEMANAGER->RenderToBackbuffer(mRealPos.x - 1, mRealPos.y - 1 + i, enemyImage[i].size(), 1, enemyImage[i], WHITE, DARKRED);
    }

    int originCardSelectPosX = 0;
    int originCardSelectPosY = BOARD_HEIGHT + 14;
    for (int i = 0; i < 3; ++i)
    {
        SCENEMANAGER->RenderToBackbuffer(originCardSelectPosX, originCardSelectPosY + 2 * i, cardSelect[i].size(), 1, cardSelect[i]);
    }

    SCENEMANAGER->RenderToBackbuffer(0, BOARD_HEIGHT + 1, sequenceStr.size(), 1, sequenceStr);

    if (cursor)
        cursor->Render();
}

void BattleScene::CalcRealPos(const Board::Pos& pos, Board::Pos& realPos)
{
    realPos.x = pos.x * 8 + 4;
    //if (pos.x == 0) --realPos.x;
    realPos.y = pos.y * 4 + 2;
}
