#pragma once

#include "../SceneInterface.h"

class MapMovePlayer;
class MapData;

class BattleScene : public iScene
{
private:
public:
	BattleScene(string _sceneName);

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;

	void Update(float _deltaTime) override;
	void Render() override;
};

