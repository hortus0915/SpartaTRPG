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
    Cost = 0,
	CardUID_MOVE = 1,
    CardUID_ATTACK = 2,
    StatAdd_HP = 3, //장비
    StatAdd_MP = 4, // 카드
	HPHeal = 5,// 포션
	MPHeal = 6,
};

class Item
{
public:
    Item(int _itemUID);

    void AddItem(int _count = 1);
    int UsingItem(int usingCount = 1);
private:
    const int itemUID; // 00 ItemType 00 TiemValueType 00 ItemID
	int value;

	int count;
    void SetItemValue(int _itemUID);

public: 
    std::string GetName();
    int GetItemCount();

    static constexpr ItemType GetItemType(int _itemUID) noexcept
    {
        return static_cast<ItemType>(_itemUID / 10000);
    }
    static constexpr ItemValueType GetItemValueType(int _itemUID) noexcept
    {
        return static_cast<ItemValueType>((_itemUID / 100) % 100);
    }
    static constexpr int GetItemID(int _itemUID) noexcept
    {
        return _itemUID % 100;
    }
    static constexpr int GetItemUID(ItemType _itemType, ItemValueType _valueType, int _itemID) noexcept
    {
        return static_cast<int>(_itemType) * 10000 + static_cast<int>(_valueType) * 100 + _itemID;
    }
};

