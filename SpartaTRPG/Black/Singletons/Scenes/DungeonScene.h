#pragma once

#include "../SceneInterface.h"

class DungeonScene : public iScene
{
public:
	DungeonScene(string _sceneName) : iScene(_sceneName) {}

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;
};

