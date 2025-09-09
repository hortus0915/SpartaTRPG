#include "ShopSceneItemHud.h"

#include "../CommonManagers.h"
#include "../../../Blue/Card/CardDB.h"


#include <sstream>

// --------------
// 이동
// Cost : 10
// 타입 : 이동
// Desc
// --------------

string ShopSceneItemHud::upper = "------------------------- I N F O ----------------------------";
string ShopSceneItemHud::lower = "--------------------------------------------------------------";

void ShopSceneItemHud::Init(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;

	TITLE = "";
	COST = "";
	TYPE = "";
}

void ShopSceneItemHud::Release()
{
	sStream.clear();
}

void ShopSceneItemHud::Render()
{
	int offsetY = 0;

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, upper.size(), 1, upper);
	++offsetY;

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TITLE.size(), 1, TITLE);
	++offsetY;

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, TYPE.size(), 1, TYPE);
	++offsetY;

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, COST.size(), 1, COST);
	++offsetY;

	if (type == ItemType::Card &&
		vType == ItemValueType::CardUID_ATTACK)
	{
		for (int i = 0; i < 3; ++i)
		{
			string desc = attackRange[0 + i * 3] + attackRange[1 + i * 3] + attackRange[2 + i * 3];
			SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, desc.size(), 1, desc);
			++offsetY;
		}
	}
	else
	{
		++offsetY;
		++offsetY;
		++offsetY;
	}

	SCENEMANAGER->RenderToBackbuffer(posX, posY + offsetY, lower.size(), 1, lower);
	++offsetY;
}

void ShopSceneItemHud::SetItem(Item* _item, int _cost)
{
	stringstream sStream;

	int uid = _item->GetItemUID();

	sStream.str("");
	sStream << _item->GetName();

	if (_item->GetItemCount() > 1)
		sStream << " X " << _item->GetItemCount();

	TITLE = sStream.str();

	sStream.str("");
	sStream << "Cost : " << _cost << "G";
	COST = sStream.str();

	TYPE = "타입 : ";
	if (Item::GetItemType(uid) == ItemType::Eequipment)
	{
		TYPE += "장비";
	}
	else if (Item::GetItemType(uid) == ItemType::Card)
	{
		TYPE += "카드";
	}
	else if (Item::GetItemType(uid) == ItemType::Potion)
	{
		TYPE += "포션";
	}

	type = _item->GetItemType(uid);
	vType = _item->GetItemValueType(uid);

	if (type == ItemType::Card &&
		vType == ItemValueType::CardUID_ATTACK)
	{
		int idx = Item::GetCardIDX(uid);
		const Card* currentCard = CardDB::Get(idx);
		for (int i = 0; i < 9; i++)
		{
			if (currentCard->GetRange() & (1u << i))
				attackRange[i] = "[X]";
			else
				attackRange[i] = "[ ]";
		}
	}
}
