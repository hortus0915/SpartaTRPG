#pragma once
#include <map>
#include "Item.h"

class Inventory
{
private:
    std::map<ItemType, std::map<int, Item*>> allItems;

public:

    Item* AddItem(int itemUID);
    Item* GetItem(int itemUID);
    int UsingItem(int itemUID, int count);
    std::map<int, Item*>& GetItemPartition(ItemType _itemType);
};

