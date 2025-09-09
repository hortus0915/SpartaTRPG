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
    CardUID_SHIELD = 2,
    CardUID_HEAL = 3,
    CardUID_ATTACK = 4,
    StatAdd_ATTACK = 5, //장비
    StatAdd_HP = 6, //장비
    StatAdd_MP = 7, // 카드
    HPHeal = 8,// 포션
    MPHeal = 9,
};

class Item
{
public:
    Item(int _itemUID, int _itemCount = 1);

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

    int GetItemUID() { return itemUID; }
    int GetValue() { return value; }

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

    static constexpr int GetCardUID(int _cardUID)
    {
        return static_cast<int>(ItemType::Card) * 10000 + _cardUID;
    }
    static constexpr int GetCardIDX(int _itemUID)
    {
        return _itemUID % 1000;
    }
};
