#pragma once

#include "Singletons/SceneInterface.h"

class MapMovePlayer;
class MapData;

class TestScene : public iScene
{
private:
	MapMovePlayer* player;
	MapData* map;

public:
	TestScene(string _sn) : iScene(_sn) {}

	// iScene��(��) ���� ��ӵ�
	int  Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;
};

