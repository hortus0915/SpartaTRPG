#include "Inventory.h"
#include<algorithm>

Item* Inventory::AddItem(int itemUID)
{
	auto itemPartition = allItems[Item::GetItemType(itemUID)];
	auto findItem = itemPartition.find(itemUID);
	if (findItem == itemPartition.end())
	{
		Item* addItem = new Item(itemUID);
		itemPartition.emplace(std::make_pair(itemUID, addItem));
		return addItem;
	}

	findItem->second->AddItem();
	return findItem->second;
}

Item* Inventory::GetItem(int itemUID)
{
	auto itemPartition = allItems.find(Item::GetItemType(itemUID));
	if (itemPartition == allItems.end())
	{
		return nullptr;
	}

	auto findItem = itemPartition->second.find(itemUID);
	if (findItem == itemPartition->second.end())
	{
		return nullptr;
	}

	return findItem->second;
}

int Inventory::UsingItem(int itemUID, int count)
{
	auto itemPartition = allItems.find(Item::GetItemType(itemUID));
	if (itemPartition == allItems.end())
	{
		return -1;
	}

	auto findItem = itemPartition->second.find(itemUID);
	if (findItem == itemPartition->second.end())
	{
		return -1;
	}

	return findItem->second->UsingItem(count);
}

std::map<int, Item*>& Inventory::GetItemPartition(ItemType _itemType)
{
	return allItems[_itemType];
}
