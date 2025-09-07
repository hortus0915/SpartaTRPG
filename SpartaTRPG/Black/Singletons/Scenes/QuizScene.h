#pragma once

#include "../SceneInterface.h"
#include "../../CommonMacros.h"
#include "../../../Yellow/Quiz.h"

class BlinkCursor;


class QuizScene : public iScene {
private:
	int cursorIndex;
	Quiz question;

	BlinkCursor* cursor;


public:
	QuizScene(string _sceneName) : iScene(_sceneName){}

	// iScene을(를) 통해 상속됨
	void Update(float deltaTime) override;
	int Init() override;
	void Release() override;
	void Render() override;
};