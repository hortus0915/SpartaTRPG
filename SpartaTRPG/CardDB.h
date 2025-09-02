#pragma once
#include "CardData.h"
#include <vector>
#include <map>

namespace CardDB
{

    void InitDefaults();
    void Clear();

    void AddCard(const Card& _card);
}
