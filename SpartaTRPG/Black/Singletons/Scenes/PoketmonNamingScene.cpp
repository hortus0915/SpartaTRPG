#include "PoketmonNamingScene.h"
#include "../CommonManagers.h"

#include <string>
#include <iostream>

string PoketmonNamingScene::GetLetters()
{
	return composed_name;
}


void PoketmonNamingScene::InputLetters(char32_t c)
{
	buffer.push_back(c);
}

void PoketmonNamingScene::DeleteLetters()
{
	buffer.pop_back();
}

void PoketmonNamingScene::Update(float deltaTime)
{

    if (is_end && !POPUPMANAGER->CheckPopupActive()) {
        //씬 넘기기
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
        if (KEYMANAGER->IsOnceKeyDown(VK_LEFT)) {

            if (!POPUPMANAGER->CheckPopupActive())
            {

                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (cursor_index % 10 > 0) {
                    cursor_index--;

                }
            }
        }
        if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT)) {

            if (!POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (cursor_index % 10 < 9 && cursor_index < TOTAL_COUNT - 1) {
                    cursor_index++;
                }


            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_UP)) {

            if (!POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (cursor_index - 9 > 0) {
                    cursor_index -= 10;
                }

            }
        }


        if (KEYMANAGER->IsOnceKeyDown(VK_DOWN)) {

            if (!POPUPMANAGER->CheckPopupActive())
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                if (cursor_index + 10 < TOTAL_COUNT) {
                    cursor_index +=10;
                }

            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_RETURN)) {
            if (cursor_index < PoketmonNaming::LETTER_COUNT) {
                InputLetters(PoketmonNaming::LETTERS[cursor_index]);
                composed_name = PoketmonNaming::Compose(buffer);
            }
            else if (cursor_index == ERASE_INDEX) {
                DeleteLetters();
                composed_name = PoketmonNaming::Compose(buffer);
            }
            else if (cursor_index == DONE_INDEX) {

                //완료 되었을때 행동
                vector<string>* initString = new vector<string>();
                string s = "당신의 이름은: " + composed_name;
                initString->push_back(s);
                //이름 유저매니저로 넘기기

                POPUPMANAGER->InitPopup<PoketmonNamingScene, nullptr>(
                    PopupType::RESULTPOPUP,
                    nullptr,
                    initString,
                    15,
                    0,
                    5,
                    0
                );
                is_end = true;


            }
        }

    }
}


int PoketmonNamingScene::Init()
{
    screen[0] = "****************************************************************************************************";
    screen[1] = "*                                                                                                  *";
    screen[2] = "*                                                                                                  *";
    screen[3] = "*                                                                                                  *";
    screen[4] = "*                                                                                                  *";
    screen[5] = "*                                                                                                  *";
    screen[6] = "*                                                                                                  *";
    screen[7] = "*                                                                                                  *";
    screen[8] = "*                                                                                                  *";
    screen[9] = "*                                                                                                  *";
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

    is_end = false;
	cursor_index = 0;
	buffer.clear();
	return 0;
}

void PoketmonNamingScene::Release()
{
}

void PoketmonNamingScene::Render()
{

    for (int i = 0; i < MAX_SCREEN_HEIGTH; ++i)
        SCENEMANAGER->RenderToBackbuffer(0, i, screen[i].size(), 1, screen[i]);


	
	string content;
	for (int i = 0; i < TOTAL_COUNT; i++) {
		int x = (i % 10) * 5 + __TOTAL_X__;
		int y = (i / 10) * 4 + __TOTAL_Y__;
		if (i < PoketmonNaming::LETTER_COUNT) {
			content = PoketmonNaming::LETTERS_UTF8[i];
		}
		else if (i == ERASE_INDEX) {
			content = "[지우기]";
		}
		else {
			content = "[완료]";
			x = x + 5;
		}
		if (i == cursor_index) {
			SCENEMANAGER->RenderToBackbuffer(x, y, 2, 1, content, 7, 1);
		}
		else {
			SCENEMANAGER->RenderToBackbuffer(x, y, 2, 1, content, 1, 7);
		}
		
	}
	SCENEMANAGER->RenderToBackbuffer(__TOTAL_X__, __TOTAL_Y__ - 5, 1, 1, "이름: ", 7, 0);
	SCENEMANAGER->RenderToBackbuffer(__TOTAL_X__ + 5, __TOTAL_Y__ - 5, 1, 1, composed_name, 7, 0);


}
