#pragma once
#include "../SceneInterface.h"

#include <vector>

using namespace std;

class Image;

struct FramePoint
{
	int x;
	int y;
};

class GameOverScene : public iScene
{
private:
	Image* pic;

	string origin[15];
	string image[15];
	vector<FramePoint> points;

	int posX;
	int posY;

	int currentFrame;

	int frameDelayCount;
	int frameCount;

	bool isDelayStart;
	float delayTime;
	float delayCurrentTime;
	bool isShowImage;

	int animFrameDelayCount;
	int animFrameCount;
	int currentAnimIndex;
	vector<Image*> anim;

public:
	GameOverScene(string _sceneName) : iScene(_sceneName), pic(nullptr), frameDelayCount(2), frameCount(0) { };

	void AddToVector(int _x, int _y);
	void Shuffle();

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;
};

