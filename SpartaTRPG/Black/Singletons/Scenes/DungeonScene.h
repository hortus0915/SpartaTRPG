#pragma once

#include "../SceneInterface.h"

class MapMovePlayer;
class MapData;

class DungeonScene : public iScene
{
private:
	MapMovePlayer* player;
	MapData* map;

public:
	DungeonScene(string _sceneName);

	// iScene��(��) ���� ��ӵ�
	int Init() override;
	void Release() override;

	void Update(float _deltaTime) override;
	void Render() override;
};

