#pragma once

#include "../SceneInterface.h"

class GameScene : public iScene
{
public:
	GameScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
};

