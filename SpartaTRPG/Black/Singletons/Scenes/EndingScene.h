#pragma once

#include "../SceneInterface.h"

class EndingScene : public iScene
{
public:
	EndingScene(string _sceneName) : iScene(_sceneName) {}

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;
};

