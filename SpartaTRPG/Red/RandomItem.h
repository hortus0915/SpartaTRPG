#pragma once
#include <map>
#include <vector>
#include "Item.h"

using namespace std;

enum class RandomItemType
{
	None,
	Box,
	Monster,
	MiniGame,
};


class RandomItem
{
private:
	map<RandomItemType, map<int, vector<Item>>> randomItemTable;

public:
	void Init();

	Item* GetRandomItem(RandomItemType randomType);
};

