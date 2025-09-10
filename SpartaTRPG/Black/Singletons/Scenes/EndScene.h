#pragma once

#include "../SceneInterface.h"

#include "../../CommonMacros.h"

#include <vector>

using namespace std;

class Image;
class BlinkCursor;

class EndScene : public iScene
{
private:
	string screen[MAX_SCREEN_HEIGTH];

	float duration;
	float elapsedTime;

	int cursorIndex;

	int effectCount;

	bool isDelayStart;
	float delayTime;
	float delayCurrentTime;

	Image* pic;

	bool isShowImage;

	int animFrameDelayCount;
	int animFrameCount;
	int currentAnimIndex;
	vector<Image*> black;
	vector<Image*> red;
	vector<Image*> blue;
	vector<Image*> yellow;

	int pinkTeleportDelayCount;
	int pinkTeleportCount;
	int currentPinkIndex;
	vector<Image*> pink;
	int pinkPosX;
	int pinkPosY;

public:
	EndScene(string _sceneName) : iScene(_sceneName), duration(4.0f), elapsedTime(0.0f), cursorIndex(0), effectCount(0){}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render() override;
};

