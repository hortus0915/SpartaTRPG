#pragma once

#include "../SceneInterface.h"
#include "../../CommonMacros.h"
#include "../../../Yellow/MinigameMap.h"

#define __DEFAULT_PLAYER_X__ 10
#define __DEFAULT_PLAYER_Y__ 10
#define __MAP_SIZE__ 3
#define __INTERVAL_X_ 4
#define __INTERVAL_Y_ 2


class MinigamePlayer;


class MinigameScene : public iScene {
private:
	float duration;
	float elapsedTime;

	int effectCount;

	bool correct;

	bool is_end;

	MinigamePlayer* player;
	MinigameMap* map;

	int playerDefPosX;
	int playerDefPosY;

	int playerRows;
	int playerCols;



public:
	MinigameScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	void Update(float deltaTime) override;
	int Init() override;
	void Release() override;
	void Render() override;

	void ResetPlayerPos();
};

