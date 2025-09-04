#pragma once

#include "../SceneInterface.h"

#include "../../CommonMacros.h"

class TitleScene : public iScene
{
private:
	string screen[MAX_SCREEN_HEIGTH];

	float duration;
	float elapsedTime;

	int cursorIndex;

public:
	TitleScene(string _sceneName) : iScene(_sceneName), duration(5.0f), elapsedTime(0.0f), cursorIndex(0) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Update(float deltaTime) override;
	void Release() override;
};

