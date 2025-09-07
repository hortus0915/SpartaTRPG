#pragma once
#include "Item.h"
#include <map>

class Inventory
{
private:
    std::map<ItemType, std::map<int, Item>> allItems;

public:

    Item* AddItem(int _itemUID);
    Item* GetItem(int _itemUID);
    int UsingItem(int _itemUID, int _count);
    std::map<int, Item>& GetItemPartition(ItemType _itemType);

    Item* GetItem_fromIndex(ItemType _itemType, long index);
};

