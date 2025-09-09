#pragma once
#include "Popup.h"

class NPCDialoguePopup : public Popup
{
private:
	int posX;
	int posY;
	int width;
	int height;

public:
	NPCDialoguePopup() : Popup() {}

	inline void SetPosWH(int _posX, int _posY, int _width, int _height)
	{
		posX = _posX;
		posY = _posY;
		width = _width;
		height = _height;
	}

	virtual void RenderingCustomString() override;

	virtual void Render() override;
	virtual void Init() override;
};
