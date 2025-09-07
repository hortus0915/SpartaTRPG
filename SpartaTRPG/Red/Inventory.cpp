#include "Inventory.h"

Item* Inventory::AddItem(int itemUID)
{
	auto itemPartition = allItems.find(Item::GetItemType(itemUID));
	if (itemPartition == allItems.end())
	{
		std::map<int, Item*> createPartition;
		Item* addItem = new Item(itemUID);
		createPartition.emplace(std::make_pair(itemUID, addItem));
		allItems.emplace(std::make_pair(Item::GetItemType(itemUID), createPartition));
		return addItem;
	}

	auto findItem = itemPartition->second.find(itemUID);
	if (findItem == itemPartition->second.end())
	{
		Item* addItem = new Item(itemUID);
		itemPartition->second.emplace(std::make_pair(itemUID, addItem));
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
	auto itemPartition = allItems.find(_itemType);
	if (itemPartition == allItems.end())
	{
		std::map<int, Item*> createPartition;
		allItems.emplace(std::make_pair(_itemType, createPartition));
		return createPartition;
	}

	return itemPartition->second;
}
