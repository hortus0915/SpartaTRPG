#include "UserManager.h"

#include "../../Black/CommonMacros.h"
#include "../BasicInterfaces.h"
#include "../../Red/Inventory.h"
#include "CommonManagers.h"

UserManager* UserManager::instance = nullptr;

void UserManager::Init()
{
	stage = 0;
	stageKey = 0;
	random.Init();
	inventory = new Inventory();
	inventory->AddItem(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1), 100);
	inventory->AddItem(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 2), 100);
	inventory->AddItem(20101);
	inventory->AddItem(20102);
	inventory->AddItem(20103);
	inventory->AddItem(20104);
	inventory->AddItem(20111);
	inventory->AddItem(20112);
	inventory->AddItem(20201);
	inventory->AddItem(20301);
	inventory->AddItem(20401);
	inventory->AddItem(20402);
	inventory->AddItem(20403);
	inventory->AddItem(20404);
	inventory->AddItem(20405);
	inventory->AddItem(20406);
	inventory->AddItem(20407);
	inventory->AddItem(20408);
	inventory->AddItem(20409);
	inventory->AddItem(20409);
	inventory->AddItem(20409);
	inventory->AddItem(20410);
	inventory->AddItem(20411);
	inventory->AddItem(20412);
	inventory->AddItem(20413);
	inventory->AddItem(20414);
}

void UserManager::GetKey()
{
	stageKey++;
}

void UserManager::ResetKey()
{
	stageKey = 0;
}

bool UserManager::CheckHasKey()
{
	return stageKey > 0;
}

void UserManager::SetNextStage()
{
	stage++;
	stageKey = 0;
}

void UserManager::AddItem(int _itemUID, int _count)
{
	if (inventory)
	{
		auto addedItem = inventory->AddItem(_itemUID, _count);
		if (addedItem)
		{
			vector<string>* initString = new vector<string>();
			char buf[128];
			std::snprintf(buf, sizeof(buf), "%sÀ»(¸¦) %d°³ È¹µæÇß´Ù!", addedItem->GetName().c_str(), addedItem->GetItemCount());
			initString->push_back(buf);

			POPUPMANAGER->InitPopup<UserManager, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				5,
				0
			);
		}
	}
}

Item* UserManager::GetItemInfo(int itemUID)
{
	if (inventory)
		return inventory->GetItem(itemUID);
	return nullptr;
}

Item* UserManager::GetItemInfo_fromIndex(ItemType itemType, int index)
{
	if (inventory)
		return inventory->GetItem_fromIndex(itemType, index);
	return nullptr;
}

Item* UserManager::GetRandomItem(RandomItemType randomType)
{
	return random.GetRandomItem(randomType);
}

void UserManager::EquipItem(Item* _equipItem)
{
	if (_equipItem == nullptr || Item::GetItemType(_equipItem->GetItemUID()) != ItemType::Eequipment)
		return;

	equipItem = _equipItem;
}

std::map<int, Item>* UserManager::GetItemPartition(ItemType _itemType)
{
	if (inventory)
		return inventory->GetItemPartition(_itemType);
	return nullptr;
}

int UserManager::UsingItem(int itemUID, int count)
{
	if (inventory)
		return inventory->UsingItem(itemUID, count);

	return -1;
}

void UserManager::Release()
{
	if (inventory)
		SAFE_DELETE(inventory);
}

