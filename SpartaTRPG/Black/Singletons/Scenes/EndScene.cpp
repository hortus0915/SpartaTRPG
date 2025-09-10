#include "EndScene.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"
#include "../../MainGame.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"
#include "../../Image.h"


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


    SOUNDMANAGER->PlayBGM(Text("EndSceneBGM.mp3"), 100);


    HWND hWnd = GetConsoleWindow();
    RECT rc;
    GetClientRect(hWnd, &rc);
    int screenWidth = rc.right - rc.left;
    int screenHeight = rc.bottom - rc.top;

    pic = new Image;
    pic->Init(TEXT("Image.bmp"), screenWidth / 2 - 293 / 2 - 71, screenHeight / 2 - 231 / 2 - 170);

    isDelayStart = false;
    delayTime = 2.0f;
    delayCurrentTime = 0.0f;
    isShowImage = false;



    black.resize(4);
    black[0] = new Image;
    black[0]->Init(TEXT("black_0.bmp"), screenWidth - 50 - 52, 250);
    black[1] = new Image;
    black[1]->Init(TEXT("black_1.bmp"), screenWidth - 50 - 52, 250);
    black[2] = new Image;
    black[2]->Init(TEXT("black_2.bmp"), screenWidth - 50 - 52, 250);
    black[3] = new Image;
    black[3]->Init(TEXT("black_3.bmp"), screenWidth - 50 - 52, 250);

    red.resize(4);
    red[0] = new Image;
    red[0]->Init(TEXT("red_0.bmp"), screenWidth - 50 - 52, 50);
    red[1] = new Image;
    red[1]->Init(TEXT("red_1.bmp"), screenWidth - 50 - 52, 50);
    red[2] = new Image;
    red[2]->Init(TEXT("red_2.bmp"), screenWidth - 50 - 52, 50);
    red[3] = new Image;
    red[3]->Init(TEXT("red_3.bmp"), screenWidth - 50 - 52, 50);

    blue.resize(4);
    blue[0] = new Image;
    blue[0]->Init(TEXT("blue_0.bmp"), 50, 50);
    blue[1] = new Image;
    blue[1]->Init(TEXT("blue_1.bmp"), 50, 50);
    blue[2] = new Image;
    blue[2]->Init(TEXT("blue_2.bmp"), 50, 50);
    blue[3] = new Image;
    blue[3]->Init(TEXT("blue_3.bmp"), 50, 50);

    yellow.resize(4);
    yellow[0] = new Image;
    yellow[0]->Init(TEXT("yellow_0.bmp"), 50, 250);
    yellow[1] = new Image;
    yellow[1]->Init(TEXT("yellow_1.bmp"), 50, 250);
    yellow[2] = new Image;
    yellow[2]->Init(TEXT("yellow_2.bmp"), 50, 250);
    yellow[3] = new Image;
    yellow[3]->Init(TEXT("yellow_3.bmp"), 50, 250);




    animFrameDelayCount = 5;
    animFrameCount = 0;
    currentAnimIndex = 0;

    pinkPosX = GetIntRange(100, 500);
    pinkPosY = GetIntRange(300, 500);
    pinkTeleportDelayCount = 100;
    pinkTeleportCount = 0;
    currentPinkIndex = 0;

    pink.resize(8);
    pink[0] = new Image;
    pink[0]->Init(TEXT("pink_0.bmp"), pinkPosX, pinkPosY);
    pink[1] = new Image;
    pink[1]->Init(TEXT("pink_1.bmp"), pinkPosX, pinkPosY);
    pink[2] = new Image;
    pink[2]->Init(TEXT("pink_2.bmp"), pinkPosX, pinkPosY);
    pink[3] = new Image;
    pink[3]->Init(TEXT("pink_3.bmp"), pinkPosX, pinkPosY);
    pink[4] = new Image;
    pink[4]->Init(TEXT("pink_4.bmp"), pinkPosX, pinkPosY);
    pink[5] = new Image;
    pink[5]->Init(TEXT("pink_5.bmp"), pinkPosX, pinkPosY);
    pink[6] = new Image;
    pink[6]->Init(TEXT("pink_6.bmp"), pinkPosX, pinkPosY);
    pink[7] = new Image;
    pink[7]->Init(TEXT("pink_7.bmp"), pinkPosX, pinkPosY);


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

    if (elapsedTime < duration && !isDelayStart)
    {
        elapsedTime += deltaTime;
        if (KEYMANAGER->IsOnceKeyDown(VK_SPACE) ||
            KEYMANAGER->IsOnceKeyDown(VK_ESCAPE) ||
            KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            elapsedTime = duration;
            isDelayStart = true;
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

        if (elapsedTime >= duration)
        {
            isDelayStart = true;
        }

#pragma endregion
    }
    
    if (isDelayStart && !isShowImage)
    {
        delayCurrentTime += deltaTime;
        if (delayCurrentTime >= delayTime)
        {
            SCENEMANAGER->GetMainGame()->ClearBuffer();
            isShowImage = true;
            SCENEMANAGER->GetMainGame()->BufferFlip();
        }
    }

    if (isShowImage)
    {
        ++animFrameCount;
        if (animFrameCount % animFrameDelayCount == 0)
        {
            animFrameCount = 0;

            currentAnimIndex = (currentAnimIndex + 1) % black.size();
            currentPinkIndex = (currentPinkIndex + 1) % pink.size();
        }

        ++pinkTeleportCount;
        if (pinkTeleportCount % pinkTeleportDelayCount == 0)
        {
            SCENEMANAGER->GetMainGame()->ClearBuffer();

            pinkPosX = GetIntRange(100, 500);
            pinkPosY = GetIntRange(300, 500);

            for (int i = 0; i < pink.size(); ++i)
                pink[i]->SetPos(pinkPosX, pinkPosY);

            SCENEMANAGER->GetMainGame()->BufferFlip();
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
            {
                MainGame::Quit();
            }
        }
    }



}

void EndScene::Release()
{
}

void EndScene::Render()
{
    __super::Render();

    if (!isShowImage)
    {
        for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
            SCENEMANAGER->RenderToBackbuffer(0, i, screen[i].size(), 1, screen[i]);
    }
    else
    {
        pic->Render();

        black[currentAnimIndex]->Render();
        red[currentAnimIndex]->Render();
        blue[currentAnimIndex]->Render();
        yellow[currentAnimIndex]->Render();
        pink[currentPinkIndex]->Render();
    }
}
