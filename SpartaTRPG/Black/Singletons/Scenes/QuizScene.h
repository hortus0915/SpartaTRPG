#pragma once

#include "../SceneInterface.h"
#include "../../CommonMacros.h"
#include "../../../Yellow/Quiz.h"

#define __CURSOR_X__ 20
#define __CURSOR_Y__ 22
#define __TEXT_WIDTH__ 60
#define __TEXT__HEIGHT__ 1
#define __QUESTION_Y__ 2
#define __OPT_X__ 2
#define __CURSOR_DIFF__ 2

#define __TOTAL_X__ -5
#define __TOTAL_Y__ -18
class BlinkCursor;


class QuizScene : public iScene {
private:
	string screen[MAX_SCREEN_HEIGTH];

	Quiz question;
	float duration;
	float elapsedTime;

	int cursorIndex;

	int effectCount;

	bool correct;

	bool is_end;

	BlinkCursor* cursor;



public:
	QuizScene(string _sceneName) : iScene(_sceneName){}

	// iScene을(를) 통해 상속됨
	void Update(float deltaTime) override;
	int Init() override;
	void Release() override;
	void Render() override;
};