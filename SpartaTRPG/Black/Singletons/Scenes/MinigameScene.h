#pragma once

#include "../SceneInterface.h"

class MinigameScene : public iScene
{
public:
	MinigameScene(string _sceneName) : iScene(_sceneName) {}

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;
};

