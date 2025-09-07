#include "Inventory.h"
#include<algorithm>

Item* Inventory::AddItem(int itemUID)
{
	auto& itemPartition = allItems[Item::GetItemType(itemUID)];
	auto ret = itemPartition.try_emplace(itemUID, itemUID);

	if (!ret.second)
	{
		ret.first->second.AddItem();
	}

	return &(ret.first->second);
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

	return &(findItem->second);
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

	int ret = findItem->second.UsingItem(count); 
	if (ret <= 0) {
		itemPartition->second.erase(findItem);             
		ret = 0;
	}

	return ret;
}

std::unordered_map<int, Item>& Inventory::GetItemPartition(ItemType _itemType)
{
	return allItems[_itemType];
}
