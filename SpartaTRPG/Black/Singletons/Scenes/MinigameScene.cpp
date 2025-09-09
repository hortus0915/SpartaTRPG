#include "MinigameScene.h"
#include "../../../Yellow/QuizData.h"
#include <random>
#include <string>


#include "../CommonManagers.h"
#include "../../CommonFuncs.h"
#include "../../MainGame.h"
#include "../../MinigamePlayer.h"

#include "../EffectType.h"


void MinigameScene::Update(float deltaTime)
{
    __super::Update(deltaTime);


    if (elapsedTime < duration)
    {
        elapsedTime += deltaTime;
        if (KEYMANAGER->IsOnceKeyDown(VK_SPACE) ||
            KEYMANAGER->IsOnceKeyDown(VK_ESCAPE) ||
            KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            elapsedTime = duration;
        }
    }
    else
    {
        if (KEYMANAGER->IsOnceKeyDown(VK_UP)) {
           
            if (player)
            {

                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerCols > 0) {
                    player->SetPos(player->GetPosX(), player->GetPosY() - __INTERVAL_Y_);
                    playerCols--;
                }
               
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_DOWN)) {
            
            if (player)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerCols < __MAP_SIZE__ - 1) {
                    player->SetPos(player->GetPosX(), player->GetPosY() + __INTERVAL_Y_);
                    playerCols++;
                }
                
               
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT)) {

            if (player)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerRows < __MAP_SIZE__ * 2) {
                    player->SetPos(player->GetPosX() + __INTERVAL_X_, player->GetPosY());
                    playerRows++;
                }
                
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_LEFT)) {

            if (player)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerRows > -1) {
                    player->SetPos(player->GetPosX() - __INTERVAL_X_, player->GetPosY());
                    playerRows--;
                }
                
            }
        }

        if (playerRows >= 0 && playerCols >= 0) {
            if (map->m_map.at(playerRows, playerCols) == '*') {
                ResetPlayerPos();
            }
            else if(map->m_map.at(playerRows,playerCols)=='G') {
                vector<string>* initString = new vector<string>();
                initString->push_back("탈출 성공했습니다!");
               
                POPUPMANAGER->InitPopup<MinigameScene, nullptr>(
                    PopupType::RESULTPOPUP,
                    nullptr,
                    initString,
                    15,
                    0,
                    5,
                    0
                );
                USERMANAGER->GetKey();
                is_end = true;

                if (!POPUPMANAGER->CheckPopupActive() && is_end) {
                    //SCENEMANAGER->ChangeChild("DungeonScene");
                    ResetPlayerPos();
                }
            }
        }
    

       
    }
}

int MinigameScene::Init()
{
    playerDefPosX = __DEFAULT_PLAYER_X__;
    playerDefPosY = __DEFAULT_PLAYER_Y__ + __INTERVAL_Y_ * __MAP_SIZE__ / 2;
    if (!map) {
        map = new MinigameMap(__MAP_SIZE__, 12222u,500);
    }
    else {
        SAFE_DELETE(map);
        map = new MinigameMap(__MAP_SIZE__, 12345u, 500);
    }
    map->generate();

    if (!player) {
        player = new MinigamePlayer("MinigameScene");
    }
    else {
        SAFE_DELETE(player);
        player = new MinigamePlayer("MinigameScene");
    }
    ResetPlayerPos();
    return 0;
}

void MinigameScene::Release()
{
    SAFE_DELETE(player);
}

void MinigameScene::Render()
{
    __super::Render();


    for (int c = 0; c < map->m_map.rows; ++c) {
        SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + c * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__-__INTERVAL_Y_, 1, 1, "====", 1);
        SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + c * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + __MAP_SIZE__*__INTERVAL_Y_, 1, 1, "====", 1);

    }
    

    for (int r = 0; r < map->m_map.rows; ++r) {
        for (int c = 0; c < map->m_map.cols; ++c) {
            std::string charToString(1, map->m_map.at(r, c));
            SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_+__DEFAULT_PLAYER_X__ + r*(__INTERVAL_X_),+__DEFAULT_PLAYER_Y__ +c*(__INTERVAL_Y_), 1, 1, charToString, 1);
       }
    }

    player->Render();
}

void MinigameScene::ResetPlayerPos()
{
    playerRows = -1;
    playerCols = __MAP_SIZE__ / 2;
    player->SetPos(playerDefPosX, playerDefPosY);
}

