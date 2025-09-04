#pragma once

#include "BasicInterfaces.h"

#include "TextColors.h"

class BlinkCursor : public IUpdatable
{
private:
	int posX;
	int posY;

	int blinkCount;
	bool isCursorOff;
	string cursor;

	Color fontColor;

public:
	BlinkCursor(string _sceneName) : IUpdatable(_sceneName), isCursorOff(false), cursor("V"), blinkCount(0), fontColor(ORIGINCOLOR) {}

	// IUpdatable��(��) ���� ��ӵ�
	void Update(float deltaTime) override;
	void Render();

	void SetPos(const int& x, const int& y);
};

