#pragma once

#include "../SceneInterface.h"

class GameScene : public iScene
{
public:
	GameScene(string _sceneName) : iScene(_sceneName) {}

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;
};

