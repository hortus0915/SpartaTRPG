#pragma once

#include "BasicInterfaces.h"

#include "TextColors.h"

class MinigamePlayer : public IUpdatable
{
private:
	int posX;
	int posY;

	int PlayerCount;
	bool isCursorOff;
	string Player;

	Color fontColor;

public:
	MinigamePlayer(string _sceneName) : IUpdatable(_sceneName), isCursorOff(false), Player("V"), PlayerCount(0), fontColor(ORIGINCOLOR) {}

	// IUpdatable을(를) 통해 상속됨
	void Update(float deltaTime) override;
	void Render();

	int GetPosX();
	int GetPosY();
	void SetPos(const int& x, const int& y);
};