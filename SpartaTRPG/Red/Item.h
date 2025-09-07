#pragma once
#include <map>

enum class ItemType
{
	Eequipment = 1,
	Card = 2,
	Potion = 3,
};

enum class ItemValueType
{
	StatAdd_HP = 1, //장비
	StatAdd_MP = 2,
	CardUID = 3, // 카드
	HPHeal = 4,// 포션
	MPHeal = 5,
};

class Item
{
public:
    Item(int _itemUID);

    void AddItem();
    int UsingItem(int usingCount = 1);
private:
    const int itemUID; // 00 ItemType 00 TiemValueType 00 ItemID
	int value;

	int count;
    void SetItemValue(int itemUID);

public:

    static ItemType GetItemType(int itemUID) noexcept
    {
        return static_cast<ItemType>(itemUID / 10000);
    }
    static ItemValueType GetItemValueType(int itemUID) noexcept
    {
        return static_cast<ItemValueType>((itemUID / 100) % 100);
    }
    static int GetItemID(int itemUID) noexcept
    {
        return itemUID % 100;
    }

    static int GetItemUID(ItemType itemType, ItemValueType valueType, int itemID) noexcept
    {
        return static_cast<int>(itemType) * 10000 + static_cast<int>(valueType) * 100 + itemID;
    }
};

