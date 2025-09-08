#include "Item.h"

Item::Item(int _itemUID)
	: itemUID(_itemUID)
{
	SetItemValue(_itemUID);
	count = 1;
}

void Item::AddItem(int _count)
{
	count += count;
}

int Item::UsingItem(int usingCount)
{
	if (count < usingCount)
		return -1;

	return --count;
}

void Item::SetItemValue(int _itemUID)
{
	switch (_itemUID)
	{
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1):
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 2):
		value = 10;
	default:
		break;
	}
}

std::string Item::GetName()
{
	switch (itemUID)
	{
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1):
		return "골드";
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 2):
		return "다이아몬드";
	default:
		return {};
	}
}

int Item::GetItemCount()
{
	return count;
}
