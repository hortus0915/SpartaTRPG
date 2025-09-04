#pragma once

#include "../SceneInterface.h"

class DungeonScene : public iScene
{
public:
	DungeonScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
};

