#include "Inventory.h"

Item* Inventory::AddItem(int _itemUID, int _count)
{
	auto& itemPartition = allItems[Item::GetItemType(_itemUID)];
	auto ret = itemPartition.try_emplace(_itemUID, _itemUID);

	if (!ret.second)
	{
		ret.first->second.AddItem(_count);
	}

	return &(ret.first->second);
}

Item* Inventory::GetItem(int _itemUID)
{
	auto itemPartition = allItems.find(Item::GetItemType(_itemUID));
	if (itemPartition == allItems.end())
	{
		return nullptr;
	}

	auto findItem = itemPartition->second.find(_itemUID);
	if (findItem == itemPartition->second.end())
	{
		return nullptr;
	}

	return &(findItem->second);
}

int Inventory::UsingItem(int _itemUID, int _count)
{
	auto itemPartition = allItems.find(Item::GetItemType(_itemUID));
	if (itemPartition == allItems.end())
	{
		return -1;
	}

	auto findItem = itemPartition->second.find(_itemUID);
	if (findItem == itemPartition->second.end())
	{
		return -1;
	}

	int ret = findItem->second.UsingItem(_count);
	if (ret <= 0) {
		itemPartition->second.erase(findItem);             
		ret = 0;
	}

	return ret;
}

std::map<int, Item>* Inventory::GetItemPartition(ItemType _itemType)
{
	return &(allItems[_itemType]);
}

Item* Inventory::GetItem_fromIndex(ItemType _itemType, long index)
{
	if (index < 0) return nullptr;

	auto partition = allItems.find(_itemType);
	if (partition == allItems.end() || partition->second.size() <= index)
		return nullptr;

	auto beginIter = partition->second.begin();
	std::advance(beginIter, index);

	return &(beginIter->second);
}
