#include "TitleScene.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"
#include "../../MainGame.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"

// OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO 
// O       O  O       O  O   O   O  O          O       O
// O       O  O       O  O   O   O  O          O       O
// OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO 
// O          O       O   O O O O   O          O     O
// O          O       O   O O O O   O          O      O
// O           OOOOOOO     O   O    OOOOOOOOO  O       O
// 
//  OOO  OOOO    OO  
// O     O   O  O  O 
//  OOO  OOOO   OOOO 
//     O O     O    O
//  OOO  O     O    O
// 
// OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO 
// O       O   O     O   O O      O  O       O  O          O       O
// O       O   O     O   O  O     O  O          O          O       O
// OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO 
// O     O    O       O  O     O  O  O       O  O          O     O
// O      O   O       O  O      O O  O       O  O          O      O
// O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O


// ¦£                 ¦¤
// ¦¢ V  Game Start   ¦¢
// ¦¢                 ¦¢
// ¦¢      Quit       ¦¢
// ¦¦                 ¦¥
   
int TitleScene::Init()
{
    /*screen[0]  = "****************************************************************************************************";
    screen[1]  = "*                                                                                                  *";
    screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
    screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
    screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
    screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
    screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
    screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
    screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
    screen[9]  = "*                                      O     O   O  O O                                            *";
    screen[10] = "*                                       OOO  OOOO   OOO                                            *";
    screen[11] = "*                                          O O     O   O                                           *";
    screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
    screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
    screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
    screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
    screen[16] = "*    ¦£                 ¦¤         O     O    O       O  O     O  O  O       O  O          O     O   *";
    screen[17] = "*    ¦¢ V  Game Start   ¦¢         O      O   O       O  O      O O  O       O  O          O      O  *";
    screen[18] = "*    ¦¢                 ¦¢         O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
    screen[19] = "*    ¦¢      Quit       ¦¢                                                                           *";
    screen[20] = "*    ¦¦                 ¦¥                                                                           *";
    screen[21] = "*                                                                                                  *";
    screen[22] = "*                                                                                                  *";
    screen[23] = "*                                                                                                  *";
    screen[24] = "****************************************************************************************************";*/
    
    screen[0]  = "****************************************************************************************************";
    screen[1]  = "*                                                                                                  *";
    screen[2]  = "*                                                                                                  *";
    screen[3]  = "*                                                                                                  *";
    screen[4]  = "*                                                                                                  *";
    screen[5]  = "*                                                                                                  *";
    screen[6]  = "*                                                                                                  *";
    screen[7]  = "*                                                                                                  *";
    screen[8]  = "*                                                                                                  *";
    screen[9]  = "*                                                                                                  *";
    screen[10] = "*                                                                                                  *";
    screen[11] = "*                                                                                                  *";
    screen[12] = "*                                                                                                  *";
    screen[13] = "*                                                                                                  *";
    screen[14] = "*                                                                                                  *";
    screen[15] = "*                                                                                                  *";
    screen[16] = "*                                                                                                  *";
    screen[17] = "*                                                                                                  *";
    screen[18] = "*                                                                                                  *";
    screen[19] = "*                                                                                                  *";
    screen[20] = "*                                                                                                  *";
    screen[21] = "*                                                                                                  *";
    screen[22] = "*                                                                                                  *";
    screen[23] = "*                                                                                                  *";
    screen[24] = "****************************************************************************************************";

    if (!cursor)
        cursor = new BlinkCursor("TitleScene");

    cursor->SetPos(7, cursorIndex * 2 + 17);

    SOUNDMANAGER->PlayBGM(Text("TitleSceneBGM.mp3"), 100);

    return 0;
}

void TitleScene::Update(float deltaTime)
{
    __super::Update(deltaTime);

    ++effectCount;
    if (effectCount % 30 == 0)
    {
        effectCount = 0;
        for (int i = 0; i < 3; ++i)
        {
            EFFECTMANAGER->StartEffect(Slash, GetIntRange(1, MAX_SCREEN_WIDTH - 1), GetIntRange(1, MAX_SCREEN_HEIGTH - 2), GetIntRange(1, MAX_SCREEN_WIDTH - 1), GetIntRange(1, MAX_SCREEN_HEIGTH - 2));
            EFFECTMANAGER->StartEffect(Explosion, GetIntRange(1, MAX_SCREEN_WIDTH - 1), GetIntRange(1, MAX_SCREEN_HEIGTH - 2));
        }
    }

    if (elapsedTime < duration)
    {
        elapsedTime += deltaTime;
        if (KEYMANAGER->IsOnceKeyDown(VK_SPACE) ||
            KEYMANAGER->IsOnceKeyDown(VK_ESCAPE) ||
            KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            elapsedTime = duration;
        }

#pragma region Animation ³ë°¡´Ù

        float ratio = elapsedTime / duration;
        float delim = 0.03f;

        if (ratio < delim * 1)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                                  *";
            screen[16] = "*                                                                                                  *";
            screen[17] = "*                                                                                                  *";
            screen[18] = "*                                                                                                  *";
            screen[19] = "*                                                                                                  *";
            screen[20] = "*                                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                          OOOO  OOO                                               *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 2)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                                  *";
            screen[16] = "*                                                                                                  *";
            screen[17] = "*                                                                                                  *";
            screen[18] = "*                                                                                                  *";
            screen[19] = "*                                                                                                  *";
            screen[20] = "*                                     OOOOOOOOO  OOOOOOOO                                          *";
            screen[21] = "*                                     O          O       O                                         *";
            screen[22] = "*                                     O          O       O                                         *";
            screen[23] = "*                                     OOOOOOOOO  OOOOOOOO                                          *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 3)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                                  *";
            screen[16] = "*                                  O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[17] = "*                                  O  O          O       O                                         *";
            screen[18] = "*                                  O  O          O       O                                         *";
            screen[19] = "*                                 O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[20] = "*                                 O   O          O     O                                           *";
            screen[21] = "*                                 O   O          O      O                                          *";
            screen[22] = "*                                O      OOO  OOOO    O   O                                         *";
            screen[23] = "*                                      O     O   O  O O                                            *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 4)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                              O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[15] = "*                              O   O  O          O       O                                         *";
            screen[16] = "*                              O   O  O          O       O                                         *";
            screen[17] = "*                             O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[18] = "*                             O O O   O          O     O                                           *";
            screen[19] = "*                             O O O   O          O      O                                          *";
            screen[20] = "*                            O   O      OOO  OOOO    O   O                                         *";
            screen[21] = "*                                      O     O   O  O O                                            *";
            screen[22] = "*                                       OOO  OOOO   OOO                                            *";
            screen[23] = "*                                          O O     O   O                                           *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 5)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                          O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[13] = "*                       O  O   O   O  O          O       O                                         *";
            screen[14] = "*                       O  O   O   O  O          O       O                                         *";
            screen[15] = "*                       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[16] = "*                       O   O O O O   O          O     O                                           *";
            screen[17] = "*                       O   O O O O   O          O      O                                          *";
            screen[18] = "*                            O   O      OOO  OOOO    O   O                                         *";
            screen[19] = "*                                      O     O   O  O O                                            *";
            screen[20] = "*                                       OOO  OOOO   OOO                                            *";
            screen[21] = "*                                          O O     O   O                                           *";
            screen[22] = "*                                OOOOOOOO     OOOOO    OO       O   OOO                            *";
            screen[23] = "*                                O       O   O     O   O O      O  O                               *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 6)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*                                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                 OOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                           *";
            screen[11] = "*                      O  O   O   O  O          O       O                                          *";
            screen[12] = "*                      O  O   O   O  O          O       O                                          *";
            screen[13] = "*                      O   O O O O   OOOOOOOOO  OOOOOOOO                                           *";
            screen[14] = "*                      O   O O O O   O          O     O                                            *";
            screen[15] = "*                      O   O O O O   O          O      O                                           *";
            screen[16] = "*                 OOOOO     O   O      OOO  OOOO    O   O                                          *";
            screen[17] = "*                                     O     O   O  O O                                             *";
            screen[18] = "*                                      OOO  OOOO   OOO                                             *";
            screen[19] = "*                                         O O     O   O                                            *";
            screen[20] = "*                               OOOOOOOO     OOOOO    OO       O   OOOOOOO                         *";
            screen[21] = "*                               O       O   O     O   O O      O  O       O                        *";
            screen[22] = "*                               O       O   O     O   O  O     O  O                                *";
            screen[23] = "*                               OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO                        *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 7)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*                                                                                                  *";
            screen[6]  = "*               OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                           *";
            screen[7]  = "*              O       O  O   O   O  O          O       O                                          *";
            screen[8]  = "*              O       O  O   O   O  O          O       O                                          *";
            screen[9]  = "*              O       O   O O O O   OOOOOOOOO  OOOOOOOO                                           *";
            screen[10] = "*              O       O   O O O O   O          O     O                                            *";
            screen[11] = "*              O       O   O O O O   O          O      O                                           *";
            screen[12] = "*               OOOOOOO     O   O      OOO  OOOO    O   O                                          *";
            screen[13] = "*                                     O     O   O  O O                                             *";
            screen[14] = "*                                      OOO  OOOO   OOO                                             *";
            screen[15] = "*                                         O O     O   O                                            *";
            screen[16] = "*                               OOOOOOOO     OOOOO    OO       O   OOOOOOO   OO                    *";
            screen[17] = "*                               O       O   O     O   O O      O  O       O  O                     *";
            screen[18] = "*                               O       O   O     O   O  O     O  O          O                     *";
            screen[19] = "*                               OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OO                    *";
            screen[20] = "*                               O     O    O       O  O     O  O  O       O  O                     *";
            screen[21] = "*                               O      O   O       O  O      O O  O       O  O                     *";
            screen[22] = "*                               O       O  O       O  O       OO   OOOOOOO   OO                    *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 8)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*          OO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[5]  = "*            O  O       O  O   O   O  O          O       O                                         *";
            screen[6]  = "*            O  O       O  O   O   O  O          O       O                                         *";
            screen[7]  = "*          OO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[8]  = "*               O       O   O O O O   O          O     O                                           *";
            screen[9]  = "*               O       O   O O O O   O          O      O                                          *";
            screen[10] = "*                OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[11] = "*                                      O     O   O  O O                                            *";
            screen[12] = "*                                       OOO  OOOO   OOO                                            *";
            screen[13] = "*                                          O O     O   O                                           *";
            screen[14] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOO               *";
            screen[15] = "*                                O       O   O     O   O O      O  O       O  O                    *";
            screen[16] = "*                                O       O   O     O   O  O     O  O          O                    *";
            screen[17] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOO               *";
            screen[18] = "*                                O     O    O       O  O     O  O  O       O  O                    *";
            screen[19] = "*                                O      O   O       O  O      O O  O       O  O                    *";
            screen[20] = "*                                O       O  O       O  O       OO   OOOOOOO   OOOOOO               *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 9)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*                                                                                                  *";
            screen[3]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[6]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[7]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[8]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[9]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[10] = "*                                      O     O   O  O O                                            *";
            screen[11] = "*                                       OOO  OOOO   OOO                                            *";
            screen[12] = "*                                          O O     O   O                                           *";
            screen[13] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[14] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[15] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[16] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[17] = "*                                O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[18] = "*                                O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[19] = "*                                O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[20] = "*                                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 6)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*                                O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*                                O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*                                O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*                                                                                                  *";
            screen[20] = "*                                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 5.9)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*                                O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*                                O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*             ¦¢                  O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*                                                                                                  *";
            screen[20] = "*                                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 5)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*                                O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*             ¦¢                  O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*             ¦¢                  O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*             ¦¢                                                                                    *";
            screen[20] = "*                                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 4)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*             ¦¢                  O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*             ¦¢                  O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*             ¦¢                  O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*             ¦¢                                                                                    *";
            screen[20] = "*             ¦¢                                                                                    *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 3)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*           ¦£   ¦¤                O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*           ¦¢e S¦¢                O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*           ¦¢   ¦¢                O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*           ¦¢uit¦¢                                                                                  *";
            screen[20] = "*           ¦¦   ¦¥                                                                                  *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 2)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*         ¦£       ¦¤              O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*         ¦¢ame Sta¦¢              O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*         ¦¢       ¦¢              O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*         ¦¢ Quit  ¦¢                                                                                *";
            screen[20] = "*         ¦¦       ¦¥                                                                                *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 1)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*       ¦£           ¦¤            O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*       ¦¢ Game Start¦¢            O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*       ¦¢           ¦¢            O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*       ¦¢   Quit    ¦¢                                                                              *";
            screen[20] = "*       ¦¦           ¦¥                                                                              *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*    OOOOOOOO    OOOOOOO   O   O   O  OOOOOOOOO  OOOOOOOO                                          *";
            screen[3]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[4]  = "*    O       O  O       O  O   O   O  O          O       O                                         *";
            screen[5]  = "*    OOOOOOOO   O       O   O O O O   OOOOOOOOO  OOOOOOOO                                          *";
            screen[6]  = "*    O          O       O   O O O O   O          O     O                                           *";
            screen[7]  = "*    O          O       O   O O O O   O          O      O                                          *";
            screen[8]  = "*    O           OOOOOOO     O   O      OOO  OOOO    O   O                                         *";
            screen[9]  = "*                                      O     O   O  O O                                            *";
            screen[10] = "*                                       OOO  OOOO   OOO                                            *";
            screen[11] = "*                                          O O     O   O                                           *";
            screen[12] = "*                                OOOOOOOO     OOOOO    OO       O   OOOOOOO   OOOOOOOOO  OOOOOOOO  *";
            screen[13] = "*                                O       O   O     O   O O      O  O       O  O          O       O *";
            screen[14] = "*                                O       O   O     O   O  O     O  O          O          O       O *";
            screen[15] = "*                                OOOOOOOO    OOOOOOO   O   O    O  O   OOOOO  OOOOOOOOO  OOOOOOOO  *";
            screen[16] = "*    ¦£                 ¦¤         O     O    O       O  O     O  O  O       O  O          O     O   *";
            screen[17] = "*    ¦¢    Game Start   ¦¢         O      O   O       O  O      O O  O       O  O          O      O  *";
            screen[18] = "*    ¦¢                 ¦¢         O       O  O       O  O       OO   OOOOOOO   OOOOOOOOO  O       O *";
            screen[19] = "*    ¦¢      Quit       ¦¢                                                                           *";
            screen[20] = "*    ¦¦                 ¦¥                                                                           *";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }

#pragma endregion
    }
    else
    {
        if (KEYMANAGER->IsOnceKeyDown(VK_UP) ||
            KEYMANAGER->IsOnceKeyDown(VK_DOWN))
        {
            cursorIndex = (cursorIndex + 1) % 2;

            if (cursor)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                cursor->SetPos(7, cursorIndex * 2 + 17);
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            if (cursorIndex == 0)
            {
                SOUNDMANAGER->PlaySfx(Text("GameStartSfx.wav"));

                SCENEMANAGER->ChangeScene("GameScene");
                SCENEMANAGER->ChangeChild("DungeonScene");
                SCENEMANAGER->CurrentSceneInit();
            }
            else if (cursorIndex == 1)
            {
                MainGame::Quit();
            }
        }
    }
}

void TitleScene::Release()
{
    SAFE_DELETE(cursor);
}

void TitleScene::Render()
{
    __super::Render();

    for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
        SCENEMANAGER->RenderToBackbuffer(0, i, screen[i].size(), 1, screen[i]);

    if (elapsedTime >= duration)
    {
        if (cursor)
        {
            cursor->Render();
        }
    }
}
