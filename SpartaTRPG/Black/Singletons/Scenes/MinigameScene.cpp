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

    if (!POPUPMANAGER->CheckPopupActive() && is_end) {
        SCENEMANAGER->ChangeChild("DungeonScene");

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
    }
    else
    {
        if (KEYMANAGER->IsOnceKeyDown(VK_UP)) {
           
            if (player && !POPUPMANAGER->CheckPopupActive())
            {

                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerCols > 0) {
                    player->SetPos(player->GetPosX(), player->GetPosY() - __INTERVAL_Y_);
                    playerCols--;
                }
               
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_DOWN)) {
            
            if (player && !POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerCols < __MAP_SIZE__ + gameLevel - 1) {
                    player->SetPos(player->GetPosX(), player->GetPosY() + __INTERVAL_Y_);
                    playerCols++;
                }
                
               
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT)) {

            if (player && !POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerRows < (__MAP_SIZE__ + gameLevel) * 3) {
                    player->SetPos(player->GetPosX() + __INTERVAL_X_, player->GetPosY());
                    playerRows++;
                }
                
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_LEFT)) {

            if (player && !POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (playerRows > -1) {
                    player->SetPos(player->GetPosX() - __INTERVAL_X_, player->GetPosY());
                    playerRows--;
                }
                
            }
        }

        if (playerRows >= 0 && playerCols >= 0) {
            if (map->m_map.at(playerRows, playerCols) == 'X') {
                ResetPlayerPos();
                SOUNDMANAGER->PlaySfx(Text("Explosion.wav"));
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
                USERMANAGER->GetRandomItem(RandomItemType::MiniGame);
                is_end = true;
                ResetPlayerPos();
                
            }
        }
    

       
    }
}

int MinigameScene::Init()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    gameLevel = USERMANAGER->GetStage();
    deathNum = -1;

    playerDefPosX = __DEFAULT_PLAYER_X__;
    playerDefPosY = __DEFAULT_PLAYER_Y__;
    if (!map) {
        map = new MinigameMap(__MAP_SIZE__ + gameLevel, dist(gen), 500);
    }
    else {
        SAFE_DELETE(map);
        map = new MinigameMap(__MAP_SIZE__ + gameLevel, dist(gen), 500);
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

    vector<string>* initString = new vector<string>();
    initString->push_back("맵 군데군데 숨겨진 지뢰를 피해서");
    initString->push_back("오른쪽 끝으로 탈출하세요.");

    POPUPMANAGER->InitPopup<MinigameScene, nullptr>(
        PopupType::RESULTPOPUP,
        nullptr,
        initString,
        15,
        0,
        5,
        0
    );
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
        SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + c * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__-__INTERVAL_Y_, 1, 1, "====", 2,2);
        SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + c * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + (__MAP_SIZE__ + gameLevel)*__INTERVAL_Y_, 1, 1, "====", 2,2);

    }
    
    SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__, +__DEFAULT_PLAYER_Y__ - 2*__INTERVAL_Y_, 1, 1, "죽은 횟수:", 1,7);
    string stDeathNum = to_string(deathNum);
    SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__ + 10, +__DEFAULT_PLAYER_Y__ - 2 * __INTERVAL_Y_, 1, 1, stDeathNum, 4);
    for (int r = 0; r < map->m_map.rows; ++r) {
        for (int c = 0; c < map->m_map.cols; ++c) {
            std::string charToString(1, map->m_map.at(r, c));
            SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + r * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + c * (__INTERVAL_Y_), 1, 1," ", 1, 7);
            if (deathNum > 15 && r < map->m_map.rows && charToString == "X") {
                SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__, +__DEFAULT_PLAYER_Y__ - 3 * __INTERVAL_Y_, 1, 1, "천재적인 멍청이...", 1, 4);
                SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + r * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + c * (__INTERVAL_Y_), 1, 1, charToString, 1,0);

            }else if (deathNum > 10 && r < map->m_map.rows*2/3 && charToString == "X") {
                SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__, +__DEFAULT_PLAYER_Y__ - 3 * __INTERVAL_Y_, 1, 1, "조금 모자란 친구.", 1, 4);
                SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + r * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + c * (__INTERVAL_Y_), 1, 1, charToString, 1, 0);

            }else if (deathNum > 5 && r < map->m_map.rows/3 && charToString == "X") {
                SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__, +__DEFAULT_PLAYER_Y__ - 3 * __INTERVAL_Y_, 1, 1, "평범한 모험가", 1, 4);
                SCENEMANAGER->RenderToBackbuffer(__INTERVAL_X_ + __DEFAULT_PLAYER_X__ + r * (__INTERVAL_X_), +__DEFAULT_PLAYER_Y__ + c * (__INTERVAL_Y_), 1, 1, charToString, 1, 0);

            }
            else if (deathNum < 5) {
                SCENEMANAGER->RenderToBackbuffer(__DEFAULT_PLAYER_X__, +__DEFAULT_PLAYER_Y__ - 3 * __INTERVAL_Y_, 1, 1, "천재적인 모험가!", 1, 4);

            }
       }
    }

    player->Render();
}

void MinigameScene::ResetPlayerPos()
{
    deathNum++;
    playerRows = -1;
    playerCols = 0;
    player->SetPos(playerDefPosX, playerDefPosY);
}

