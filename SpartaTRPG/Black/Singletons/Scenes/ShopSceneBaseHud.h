#pragma once

#include "../../BasicInterfaces.h"
#include "../../TextColors.h"

class ShopSceneNPC;

class ShopSceneBaseHud : public IRenderable
{
private:
	int posX;
	int posY;

	ShopSceneNPC* npc;

	string image[20];

public:
	ShopSceneBaseHud(string _sn) : IRenderable(_sn), npc(nullptr) { }

	void Init(int _posX, int _posY);
	void Release();

	// IRenderable을(를) 통해 상속됨
	void Render() override;

	void DelightTrigger();
};

