#pragma once

#include "../SceneInterface.h"

class MapMovePlayer;
class MapData;


class MinigameScene : public iScene
{
private:
	MapMovePlayer* player;
	MapData* map;

public:
	MinigameScene(string _sceneName) : iScene(_sceneName){}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;

	void Update(float _deltaTime) override;
	void Render() override;
};

