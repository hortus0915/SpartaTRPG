#include "QuizScene.h"
#include "../../../Yellow/QuizData.h"
#include <random>
#include "../CommonManagers.h"
#include "../../CommonFuncs.h"
#include "../../MainGame.h"
#include "../../BlinkCursor.h"

#include "../EffectType.h"



void QuizScene::Update(float deltaTime)
{
	__super::Update(deltaTime);

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
            if (cursorIndex > 0) {
                cursorIndex--;
            }
            else {
                cursorIndex = 3;
            }
            if (cursor)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                cursor->SetPos(__CURSOR_X__, cursorIndex * 2 + __CURSOR_Y__);
            }
        }

        if (KEYMANAGER->IsOnceKeyDown(VK_DOWN)) {
            if (cursorIndex < 3) {
                cursorIndex++;
            }
            else {
                cursorIndex = 0;
            }
            if (cursor)
            {
                SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
                cursor->SetPos(__CURSOR_X__, cursorIndex * 2 + __CURSOR_Y__);
            }
        }


        if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
        {
            if (cursorIndex == question.getAnswer())
            {
                // 정답일경우
            }
            else
            {
                // 오답일경우
            }
        }
    }
}

int QuizScene::Init()
{
    auto _quizData = LoadQuizData();
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<int> dist(0, _quizData.size() - 1); 

    int r = dist(gen);
    question.setQuestion(_quizData[r]);
	if (!cursor)
		cursor = new BlinkCursor("QuizScene");

	cursor->SetPos(7, cursorIndex * 2 + 17);
	return 0;
}

void QuizScene::Release()
{
	SAFE_DELETE(cursor);
}

void QuizScene::Render()
{
	__super::Render();
	cursor->Render();
    SCENEMANAGER->RenderToBackbuffer(__CURSOR_X__, __CURSOR_Y__ -__QUESTION_Y__, __TEXT_WIDTH__, __TEXT__HEIGHT__, question.getQuestion(), 1);
    for (int i = 0; i < 4; ++i) {
        std::string optLine = std::to_string(i + 1) + ". " + question.getOpt(i);
        SCENEMANAGER->RenderToBackbuffer(__CURSOR_X__+__OPT_X__, __CURSOR_Y__ + i*__CURSOR_DIFF__, __TEXT_WIDTH__, __TEXT__HEIGHT__, optLine, 1);
    }

}
