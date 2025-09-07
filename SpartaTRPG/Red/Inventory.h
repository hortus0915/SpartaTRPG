#pragma once
#include "Item.h"
#include <unordered_map>

class Inventory
{
private:
    std::map<ItemType, std::unordered_map<int, Item>> allItems;

public:

    Item* AddItem(int itemUID);
    Item* GetItem(int itemUID);
    int UsingItem(int itemUID, int count);
    std::unordered_map<int, Item>& GetItemPartition(ItemType _itemType);
};

