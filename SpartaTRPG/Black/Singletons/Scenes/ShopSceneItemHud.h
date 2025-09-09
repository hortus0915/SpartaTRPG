#pragma once

#include <sstream>

using namespace std;

#include "../../BasicInterfaces.h"
#include "../../TextColors.h"

#include "../../../Red/Item.h"

#define TITLE	image[0]
#define COST	image[1]
#define TYPE	image[2]

class ShopSceneItemHud : public IRenderable
{
private:
	int posX;
	int posY;

	static string upper;
	static string lower;

	string image[3];
	string attackRange[9];
	ItemType type;
	ItemValueType vType;

	Item* currentItem;

	stringstream sStream;

public:
	ShopSceneItemHud(string _sn) : IRenderable(_sn), posX(0), posY(0), currentItem(nullptr){}

	void Init(int _posX, int _posY);
	void Release();

	// IRenderable을(를) 통해 상속됨
	void Render() override;

	void SetItem(Item* _item, int _cost);
};

