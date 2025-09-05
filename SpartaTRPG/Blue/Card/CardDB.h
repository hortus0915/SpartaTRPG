#pragma once
#include "CardData.h"
#include <vector>
#include <set>
#include <map>
#include <random>


namespace CardDB
{
    void InitDefaults();
    void Clear();

    void AddCard(const Card& _card);
    const Card* Get(int idx);

    int RandomNotOwnedIndex(const std::set<int>& ownedSet);

}
