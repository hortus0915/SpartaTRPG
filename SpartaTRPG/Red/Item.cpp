#include "Item.h"

Item::Item(int _itemUID)
	: itemUID(_itemUID)
{
	SetItemValue(_itemUID);
	count = 1;
}

void Item::AddItem()
{
	count++;
}

int Item::UsingItem(int usingCount)
{
	if (count < usingCount)
		return -1;

	return --count;
}

void Item::SetItemValue(int itemUID)
{
	switch (itemUID)
	{
	case 0:
		value = 10;
	default:
		break;
	}
}
