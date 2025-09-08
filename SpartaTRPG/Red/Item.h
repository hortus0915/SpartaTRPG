#pragma once
#include <map>
#include <string>

enum class ItemType
{
    Cost = 0,
	Eequipment = 1,
	Card = 2,
	Potion = 3,
    MAX = 4,
};

enum class ItemValueType
{
    Gold = 0,
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
    void SetItemValue(int _itemUID);

public: 
    std::string GetName();
    int GetItemCount();
    static ItemType GetItemType(int _itemUID) noexcept
    {
        return static_cast<ItemType>(_itemUID / 10000);
    }
    static ItemValueType GetItemValueType(int _itemUID) noexcept
    {
        return static_cast<ItemValueType>((_itemUID / 100) % 100);
    }
    static int GetItemID(int _itemUID) noexcept
    {
        return _itemUID % 100;
    }

    static int GetItemUID(ItemType _itemType, ItemValueType _valueType, int _itemID) noexcept
    {
        return static_cast<int>(_itemType) * 10000 + static_cast<int>(_valueType) * 100 + _itemID;
    }
};

