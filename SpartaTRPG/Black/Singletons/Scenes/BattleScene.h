#pragma once

#include "../SceneInterface.h"

class BattleScene : public iScene
{
public:
	BattleScene(string _sceneName) : iScene(_sceneName) {}

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;
};

