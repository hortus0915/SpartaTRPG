#include "UserManager.h"

#include "../../Black/CommonMacros.h"
#include "../BasicInterfaces.h"
#include "../../Red/Inventory.h"

UserManager* UserManager::instance = nullptr;

void UserManager::Init()
{
	stage = 0;
	stageKey = 0;
	inventory = new Inventory();
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

void UserManager::AddItem(int itemUID)
{
	if (inventory)
		inventory->AddItem(itemUID);
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

