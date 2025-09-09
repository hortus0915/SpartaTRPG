#include "EndScene.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"
#include "../../MainGame.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"


//  OOOOOOO     OOOOO      O   O    OOOOOOOOO 
// O       O   O     O    O O O O   O         
// O           O     O    O O O O   O         
// O   OOOOO   OOOOOOO    O O O O   OOOOOOOOO 
// O       O  O       O  O   O   O  O         
// O       O  O       O  O   O   O  O         
//  OOOOOOO   O       O  O   O   O  OOOOOOOOO 
//                         
//                       
//   OOOOOOO     OOOOO     O    O   OOOOOOOOO  OOOOOOOO                  
//  O       O   O     O    O    O   O          O       O                 
//  O       O   O     O    O    O   O          O       O                 
//  O       O   OOOOOOO     O  O    OOOOOOOOO  OOOOOOOO                  
//  O       O  O       O    O  O    O          O     O                   
//  O       O  O       O    O  O    O          O      O                  
//   OOOOOOO   O       O     O      OOOOOOOOO  O       O                 
// 
//                                                            
//   OOOOOOO   O            OOOOOOOOO    OOOOO    OOOOOOOO                              
//  O          O            O           O     O   O       O                             
//  O          O            O           O     O   O       O                             
//  O          O            OOOOOOOOO   OOOOOOO   OOOOOOOO                              
//  O          O            O          O       O  O     O                               
//  O          O            O          O       O  O      O                              
//   OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O       O                                       



   
int EndScene::Init()
{
    /*screen[0]  = "****************************************************************************************************";
    screen[1]  = "*                                                                                                  *";
    screen[2]  = "*     OOOOOOO     OOOOO      O   O    OOOOOOOOO                                                    *";
    screen[3]  = "*    O       O   O     O    O O O O   O                                                            *";
    screen[4]  = "*    O           O     O    O O O O   O                                                            *";
    screen[5]  = "*    O   OOOOO   OOOOOOO    O O O O   OOOOOOOOO                                                    *";
    screen[6]  = "*    O       O  O       O  O   O   O  O                                                            *";
    screen[7]  = "*    O       O  O       O  O   O   O  O                                                            *";
    screen[8]  = "*     OOOOOOO   O       O  O   O   O  OOOOOOOOO                                                    *";
    screen[9]  = "*                                                                                                  *";
    screen[10] = "*                                                                                                  *";
    screen[11] = "*                                                                                                  *";
    screen[12] = "*                                                                                                  *";
    screen[13] = "*                                                                                                  *";
    screen[14] = "*                                                                                                  *";
    screen[15] = "*                                         OOOOOOO     OOOOO     O    O   OOOOOOOOO  OOOOOOOO       *";
    screen[16] = "*                                        O       O   O     O    O    O   O          O       O      *";
    screen[17] = "*                                        O       O   O     O    O    O   O          O       O      *";
    screen[18] = "*                                        O       O   OOOOOOO     O  O    OOOOOOOOO  OOOOOOOO       *";
    screen[19] = "*                                        O       O  O       O    O  O    O          O     O        *";
    screen[20] = "*                                        O       O  O       O    O  O    O          O      O       *";
    screen[21] = "*                                         OOOOOOO   O       O     O      OOOOOOOOO  O       O      *";
    screen[22] = "*                                                                                                  *";
    screen[23] = "*                                                                                                  *";
    screen[24] = "****************************************************************************************************";*/

    /*screen[0]  = "****************************************************************************************************";
    screen[1]  = "*                                                                                                  *";
    screen[2]  = "*     OOOOOOO     OOOOO      O   O    OOOOOOOOO                                                    *";
    screen[3]  = "*    O       O   O     O    O O O O   O                                                            *";
    screen[4]  = "*    O           O     O    O O O O   O                                                            *";
    screen[5]  = "*    O   OOOOO   OOOOOOO    O O O O   OOOOOOOOO                                                    *";
    screen[6]  = "*    O       O  O       O  O   O   O  O                                                            *";
    screen[7]  = "*    O       O  O       O  O   O   O  O                                                            *";
    screen[8]  = "*     OOOOOOO   O       O  O   O   O  OOOOOOOOO                                                    *";
    screen[9]  = "*                                                                                                  *";
    screen[10] = "*                                                                                                  *";
    screen[11] = "*                                                                                                  *";
    screen[12] = "*                                                                                                  *";
    screen[13] = "*                                                                                                  *";
    screen[14] = "*                                                                                                  *";
    screen[15] = "*                                       OOOOOOO   O            OOOOOOOOO    OOOOO    OOOOOOOO      *";
    screen[16] = "*                                      O          O            O           O     O   O       O     *";
    screen[17] = "*                                      O          O            O           O     O   O       O     *";
    screen[18] = "*                                      O          O            OOOOOOOOO   OOOOOOO   OOOOOOOO      *";
    screen[19] = "*                                      O          O            O          O       O  O     O       *";
    screen[20] = "*                                      O          O            O          O       O  O      O      *";
    screen[21] = "*                                       OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O       O     *";
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
        cursor = new BlinkCursor("EndScene");

    cursor->SetPos(7, cursorIndex * 2 + 17);

    SOUNDMANAGER->PlayBGM(Text("EndSceneBGM.mp3"), 100);

    return 0;
}

void EndScene::Update(float deltaTime)
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
            screen[2]  = "*O                                                                                                 *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*O                                                                                                 *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*O                                                                                                 *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                                  *";
            screen[16] = "*                                                                                                 O*";
            screen[17] = "*                                                                                                 O*";
            screen[18] = "*                                                                                                 O*";
            screen[19] = "*                                                                                                 O*";
            screen[20] = "*                                                                                                 O*";
            screen[21] = "*                                                                                                  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 2)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOO                                                                                               *";
            screen[3]  = "*                                                                                                  *";
            screen[4]  = "*                                                                                                  *";
            screen[5]  = "*OOO                                                                                               *";
            screen[6]  = "*                                                                                                  *";
            screen[7]  = "*                                                                                                  *";
            screen[8]  = "*OOO                                                                                               *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                             OOOO *";
            screen[16] = "*                                                                                            O     *";
            screen[17] = "*                                                                                            O     *";
            screen[18] = "*                                                                                            O     *";
            screen[19] = "*                                                                                            O     *";
            screen[20] = "*                                                                                            O     *";
            screen[21] = "*                                                                                             OOOO *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 3)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOOOOOOOO                                                                                         *";
            screen[3]  = "*O                                                                                                 *";
            screen[4]  = "*O                                                                                                 *";
            screen[5]  = "*OOOOOOOOO                                                                                         *";
            screen[6]  = "*O                                                                                                 *";
            screen[7]  = "*O                                                                                                 *";
            screen[8]  = "*OOOOOOOOO                                                                                         *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                           OOOOOOO*";
            screen[16] = "*                                                                                          O       *";
            screen[17] = "*                                                                                          O       *";
            screen[18] = "*                                                                                          O       *";
            screen[19] = "*                                                                                          O       *";
            screen[20] = "*                                                                                          O       *";
            screen[21] = "*                                                                                           OOOOOOO*";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 4)
        {
            screen[0]  = "*****************************************************************************************************";
            screen[1]  = "*                                                                                                   *";
            screen[2]  = "*   OOOOOOOOO                                                                                       *";
            screen[3]  = "*   O                                                                                               *";
            screen[4]  = "*   O                                                                                               *";
            screen[5]  = "*   OOOOOOOOO                                                                                       *";
            screen[6]  = "*O  O                                                                                               *";
            screen[7]  = "*O  O                                                                                               *";
            screen[8]  = "*O  OOOOOOOOO                                                                                       *";
            screen[9]  = "*                                                                                                   *";
            screen[10] = "*                                                                                                   *";
            screen[11] = "*                                                                                                   *";
            screen[12] = "*                                                                                                   *";
            screen[13] = "*                                                                                                   *";
            screen[14] = "*                                                                                                   *";
            screen[15] = "*                                                                                         OOOOOOO   O*";
            screen[16] = "*                                                                                        O          O*";
            screen[17] = "*                                                                                        O          O*";
            screen[18] = "*                                                                                        O          O*";
            screen[19] = "*                                                                                        O          O*";
            screen[20] = "*                                                                                        O          O*";
            screen[21] = "*                                                                                         OOOOOOO   O*";
            screen[22] = "*                                                                                                   *";
            screen[23] = "*                                                                                                   *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 5)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*  O    OOOOOOOOO                                                                                  *";
            screen[3]  = "* O O   O                                                                                          *";
            screen[4]  = "* O O   O                                                                                          *";
            screen[5]  = "* O O   OOOOOOOOO                                                                                  *";
            screen[6]  = "*O   O  O                                                                                          *";
            screen[7]  = "*O   O  O                                                                                          *";
            screen[8]  = "*O   O  OOOOOOOOO                                                                                  *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                                     OOOOOOO   O  *";
            screen[16] = "*                                                                                    O          O  *";
            screen[17] = "*                                                                                    O          O  *";
            screen[18] = "*                                                                                    O          O  *";
            screen[19] = "*                                                                                    O          O  *";
            screen[20] = "*                                                                                    O          O  *";
            screen[21] = "*                                                                                     OOOOOOO   OO0*";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 6)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                   *";
            screen[2]  = "*O   O    OOOOOOOOO                                                                                 *";
            screen[3]  = "* O O O   O                                                                                         *";
            screen[4]  = "* O O O   O                                                                                         *";
            screen[5]  = "* O O O   OOOOOOOOO                                                                                 *";
            screen[6]  = "*  O   O  O                                                                                         *";
            screen[7]  = "*  O   O  O                                                                                         *";
            screen[8]  = "*  O   O  OOOOOOOOO                                                                                 *";
            screen[9]  = "*                                                                                                   *";
            screen[10] = "*                                                                                                   *";
            screen[11] = "*                                                                                                   *";
            screen[12] = "*                                                                                                   *";
            screen[13] = "*                                                                                                   *";
            screen[14] = "*                                                                                                   *";
            screen[15] = "*                                                                                   OOOOOOO   O     *";
            screen[16] = "*                                                                                  O          O     *";
            screen[17] = "*                                                                                  O          O     *";
            screen[18] = "*                                                                                  O          O     *";
            screen[19] = "*                                                                                  O          O     *";
            screen[20] = "*                                                                                  O          O     *";
            screen[21] = "*                                                                                   OOOOOOO   OO0000*";
            screen[22] = "*                                                                                                   *";
            screen[23] = "*                                                                                                   *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 7)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*  O   O    OOOOOOOOO                                                                              *";
            screen[3]  = "* O O O O   O                                                                                      *";
            screen[4]  = "* O O O O   O                                                                                      *";
            screen[5]  = "* O O O O   OOOOOOOOO                                                                              *";
            screen[6]  = "*O   O   O  O                                                                                      *";
            screen[7]  = "*O   O   O  O                                                                                      *";
            screen[8]  = "*O   O   O  OOOOOOOOO                                                                              *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                            OOOOOOO   O           *";
            screen[16] = "*                                                                           O          O           *";
            screen[17] = "*                                                                           O          O           *";
            screen[18] = "*                                                                           O          O           *";
            screen[19] = "*                                                                           O          O           *";
            screen[20] = "*                                                                           O          O           *";
            screen[21] = "*                                                                            OOOOOOO   OO0000000OO *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 8)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                   *";
            screen[2]  = "*     O   O    OOOOOOOOO                                                                            *";
            screen[3]  = "*    O O O O   O                                                                                    *";
            screen[4]  = "*    O O O O   O                                                                                    *";
            screen[5]  = "*    O O O O   OOOOOOOOO                                                                            *";
            screen[6]  = "*O  O   O   O  O                                                                                    *";
            screen[7]  = "*O  O   O   O  O                                                                                    *";
            screen[8]  = "*O  O   O   O  OOOOOOOOO                                                                            *";
            screen[9]  = "*                                                                                                   *";
            screen[10] = "*                                                                                                   *";
            screen[11] = "*                                                                                                   *";
            screen[12] = "*                                                                                                   *";
            screen[13] = "*                                                                                                   *";
            screen[14] = "*                                                                                                   *";
            screen[15] = "*                                                                        OOOOOOO   O            OOOO*";
            screen[16] = "*                                                                       O          O            O   *";
            screen[17] = "*                                                                       O          O            O   *";
            screen[18] = "*                                                                       O          O            OOOO*";
            screen[19] = "*                                                                       O          O            O   *";
            screen[20] = "*                                                                       O          O            O   *";
            screen[21] = "*                                                                        OOOOOOO   OO0000000OO  OOOO*";
            screen[22] = "*                                                                                                   *";
            screen[23] = "*                                                                                                   *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < delim * 9)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*O      O   O    OOOOOOOOO                                                                         *";
            screen[3]  = "* O    O O O O   O                                                                                 *";
            screen[4]  = "* O    O O O O   O                                                                                 *";
            screen[5]  = "*OO    O O O O   OOOOOOOOO                                                                         *";
            screen[6]  = "*  O  O   O   O  O                                                                                 *";
            screen[7]  = "*  O  O   O   O  O                                                                                 *";
            screen[8]  = "*  O  O   O   O  OOOOOOOOO                                                                         *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                                   OOOOOOO   O            OOOOOOOO*";
            screen[16] = "*                                                                  O          O            O       *";
            screen[17] = "*                                                                  O          O            O       *";
            screen[18] = "*                                                                  O          O            OOOOOOOO*";
            screen[19] = "*                                                                  O          O            O       *";
            screen[20] = "*                                                                  O          O            O       *";
            screen[21] = "*                                                                   OOOOOOO   OO0000000OO  OOOOOOOO*";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 6)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOO      O   O    OOOOOOOOO                                                                       *";
            screen[3]  = "*   O    O O O O   O                                                                               *";
            screen[4]  = "*   O    O O O O   O                                                                               *";
            screen[5]  = "*OOOO    O O O O   OOOOOOOOO                                                                       *";
            screen[6]  = "*    O  O   O   O  O                                                                               *";
            screen[7]  = "*    O  O   O   O  O                                                                               *";
            screen[8]  = "*    O  O   O   O  OOOOOOOOO                                                                       *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                               OOOOOOO   O            OOOOOOOOO   *";
            screen[16] = "*                                                              O          O            O           *";
            screen[17] = "*                                                              O          O            O           *";
            screen[18] = "*                                                              O          O            OOOOOOOOO   *";
            screen[19] = "*                                                              O          O            O          O*";
            screen[20] = "*                                                              O          O            O          O*";
            screen[21] = "*                                                               OOOOOOO   OO0000000OO  OOOOOOOOO  O*";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 5.9)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOOOO      O   O    OOOOOOOOO                                                                     *";
            screen[3]  = "*     O    O O O O   O                                                                             *";
            screen[4]  = "*     O    O O O O   O                                                                             *";
            screen[5]  = "*OOOOOO    O O O O   OOOOOOOOO                                                                     *";
            screen[6]  = "*      O  O   O   O  O                                                                             *";
            screen[7]  = "*      O  O   O   O  O                                                                             *";
            screen[8]  = "*      O  O   O   O  OOOOOOOOO                                                                     *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                             OOOOOOO   O            OOOOOOOOO    O*";
            screen[16] = "*                                                            O          O            O           O *";
            screen[17] = "*                                                            O          O            O           O *";
            screen[18] = "*                                                            O          O            OOOOOOOOO   OO*";
            screen[19] = "*                                                            O          O            O          O  *";
            screen[20] = "*                                                            O          O            O          O  *";
            screen[21] = "*                                                             OOOOOOO   OO0000000OO  OOOOOOOOO  O  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 5)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                   *";
            screen[2]  = "*  OOOOO      O   O    OOOOOOOOO                                                                    *";
            screen[3]  = "* O     O    O O O O   O                                                                            *";
            screen[4]  = "* O     O    O O O O   O                                                                            *";
            screen[5]  = "* OOOOOOO    O O O O   OOOOOOOOO                                                                    *";
            screen[6]  = "*O       O  O   O   O  O                                                                            *";
            screen[7]  = "*O       O  O   O   O  O                                                                            *";
            screen[8]  = "*O       O  O   O   O  OOOOOOOOO                                                                    *";
            screen[9]  = "*                                                                                                   *";
            screen[10] = "*                                                                                                   *";
            screen[11] = "*                                                                                                   *";
            screen[12] = "*                                                                                                   *";
            screen[13] = "*                                                                                                   *";
            screen[14] = "*                                                                                                   *";
            screen[15] = "*                                                           OOOOOOO   O            OOOOOOOOO    OOOO*";
            screen[16] = "*                                                          O          O            O           O    *";
            screen[17] = "*                                                          O          O            O           O    *";
            screen[18] = "*                                                          O          O            OOOOOOOOO   OOOOO*";
            screen[19] = "*                                                          O          O            O          O     *";
            screen[20] = "*                                                          O          O            O          O     *";
            screen[21] = "*                                                           OOOOOOO   OO0000000OO  OOOOOOOOO  O     *";
            screen[22] = "*                                                                                                   *";
            screen[23] = "*                                                                                                   *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 4)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*O     OOOOO      O   O    OOOOOOOOO                                                               *";
            screen[3]  = "* O   O     O    O O O O   O                                                                       *";
            screen[4]  = "*     O     O    O O O O   O                                                                       *";
            screen[5]  = "*OO   OOOOOOO    O O O O   OOOOOOOOO                                                               *";
            screen[6]  = "* O  O       O  O   O   O  O                                                                       *";
            screen[7]  = "* O  O       O  O   O   O  O                                                                       *";
            screen[8]  = "*O   O       O  O   O   O  OOOOOOOOO                                                               *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                     OOOOOOO   O            OOOOOOOOO    OOOOO    *";
            screen[16] = "*                                                    O          O            O           O     O   *";
            screen[17] = "*                                                    O          O            O           O     O   *";
            screen[18] = "*                                                    O          O            OOOOOOOOO   OOOOOOO   *";
            screen[19] = "*                                                    O          O            O          O       O  *";
            screen[20] = "*                                                    O          O            O          O       O  *";
            screen[21] = "*                                                     OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 3)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOO     OOOOO      O   O    OOOOOOOOO                                                             *";
            screen[3]  = "*   O   O     O    O O O O   O                                                                     *";
            screen[4]  = "*       O     O    O O O O   O                                                                     *";
            screen[5]  = "*OOOO   OOOOOOO    O O O O   OOOOOOOOO                                                             *";
            screen[6]  = "*   O  O       O  O   O   O  O                                                                     *";
            screen[7]  = "*   O  O       O  O   O   O  O                                                                     *";
            screen[8]  = "*OOO   O       O  O   O   O  OOOOOOOOO                                                             *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                                   OOOOOOO   O            OOOOOOOOO    OOOOO    OO*";
            screen[16] = "*                                                  O          O            O           O     O   O *";
            screen[17] = "*                                                  O          O            O           O     O   O *";
            screen[18] = "*                                                  O          O            OOOOOOOOO   OOOOOOO   OO*";
            screen[19] = "*                                                  O          O            O          O       O  O *";
            screen[20] = "*                                                  O          O            O          O       O  O *";
            screen[21] = "*                                                   OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 2)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "*OOOOOO     OOOOO      O   O    OOOOOOOOO                                                          *";
            screen[3]  = "*      O   O     O    O O O O   O                                                                  *";
            screen[4]  = "*          O     O    O O O O   O                                                                  *";
            screen[5]  = "*  OOOOO   OOOOOOO    O O O O   OOOOOOOOO                                                          *";
            screen[6]  = "*      O  O       O  O   O   O  O                                                                  *";
            screen[7]  = "*      O  O       O  O   O   O  O                                                                  *";
            screen[8]  = "*OOOOOO   O       O  O   O   O  OOOOOOOOO                                                          *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                              OOOOOOO   O            OOOOOOOOO    OOOOO    OOOOOOO*";
            screen[16] = "*                                             O          O            O           O     O   O      *";
            screen[17] = "*                                             O          O            O           O     O   O      *";
            screen[18] = "*                                             O          O            OOOOOOOOO   OOOOOOO   OOOOOOO*";
            screen[19] = "*                                             O          O            O          O       O  O     O*";
            screen[20] = "*                                             O          O            O          O       O  O      *";
            screen[21] = "*                                              OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O      *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else if (ratio < 1.0f - delim / 2.0f * 1)
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                  *";
            screen[2]  = "* OOOOOOO     OOOOO      O   O    OOOOOOOOO                                                        *";
            screen[3]  = "*O       O   O     O    O O O O   O                                                                *";
            screen[4]  = "*O           O     O    O O O O   O                                                                *";
            screen[5]  = "*O   OOOOO   OOOOOOO    O O O O   OOOOOOOOO                                                        *";
            screen[6]  = "*O       O  O       O  O   O   O  O                                                                *";
            screen[7]  = "*O       O  O       O  O   O   O  O                                                                *";
            screen[8]  = "* OOOOOOO   O       O  O   O   O  OOOOOOOOO                                                        *";
            screen[9]  = "*                                                                                                  *";
            screen[10] = "*                                                                                                  *";
            screen[11] = "*                                                                                                  *";
            screen[12] = "*                                                                                                  *";
            screen[13] = "*                                                                                                  *";
            screen[14] = "*                                                                                                  *";
            screen[15] = "*                                           OOOOOOO   O            OOOOOOOOO    OOOOO    OOOOOOOO  *";
            screen[16] = "*                                          O          O            O           O     O   O       O *";
            screen[17] = "*                                          O          O            O           O     O   O       O *";
            screen[18] = "*                                          O          O            OOOOOOOOO   OOOOOOO   OOOOOOOO  *";
            screen[19] = "*                                          O          O            O          O       O  O     O   *";
            screen[20] = "*                                          O          O            O          O       O  O      O  *";
            screen[21] = "*                                           OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O       O *";
            screen[22] = "*                                                                                                  *";
            screen[23] = "*                                                                                                  *";
            screen[24] = "****************************************************************************************************";
        }
        else
        {
            screen[0]  = "****************************************************************************************************";
            screen[1]  = "*                                                                                                *";
            screen[2]  = "*    OOOOOOO     OOOOO      O   O    OOOOOOOOO                                                   *";
            screen[3]  = "*   O       O   O     O    O O O O   O                                                           *";
            screen[4]  = "*   O           O     O    O O O O   O                                                           *";
            screen[5]  = "*   O   OOOOO   OOOOOOO    O O O O   OOOOOOOOO                                                   *";
            screen[6]  = "*   O       O  O       O  O   O   O  O                                                           *";
            screen[7]  = "*   O       O  O       O  O   O   O  O                                                           *";
            screen[8]  = "*    OOOOOOO   O       O  O   O   O  OOOOOOOOO                                                   *";
            screen[9]  = "*                                                                                                *";
            screen[10] = "*                                                                                                *";
            screen[11] = "*                                                                                                *";
            screen[12] = "*                                                                                                *";
            screen[13] = "*                                                                                                *";
            screen[14] = "*                                                                                                *";
            screen[15] = "*                                      OOOOOOO   O            OOOOOOOOO    OOOOO    OOOOOOOO     *";
            screen[16] = "*                                     O          O            O           O     O   O       O    *";
            screen[17] = "*                                     O          O            O           O     O   O       O    *";
            screen[18] = "*                                     O          O            OOOOOOOOO   OOOOOOO   OOOOOOOO     *";
            screen[19] = "*                                     O          O            O          O       O  O     O      *";
            screen[20] = "*                                     O          O            O          O       O  O      O     *";
            screen[21] = "*                                      OOOOOOO   OO0000000OO  OOOOOOOOO  O       O  O       O    *";
            screen[22] = "*                                                                                                *";
            screen[23] = "*                                                                                                *";
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

void EndScene::Release()
{
    SAFE_DELETE(cursor);
}

void EndScene::Render()
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
