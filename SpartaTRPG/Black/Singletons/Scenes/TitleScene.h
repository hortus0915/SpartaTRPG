#pragma once

#include "../SceneInterface.h"

#include "../../CommonMacros.h"

class BlinkCursor;

class TitleScene : public iScene
{
private:
	string screen[MAX_SCREEN_HEIGTH];

	float duration;
	float elapsedTime;

	int cursorIndex;

	int effectCount;

	BlinkCursor* cursor;

public:
	TitleScene(string _sceneName) : iScene(_sceneName), duration(4.0f), elapsedTime(0.0f), cursorIndex(0), cursor(nullptr), effectCount(0){}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render() override;
};

