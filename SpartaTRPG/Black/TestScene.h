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

	// iScene을(를) 통해 상속됨
	int  Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;
};

