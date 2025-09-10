#pragma once

#include <vector>
#include <map>

using namespace std;

#include "../Singletons/SingletonMacro.h"
#include "../../Red/RandomItem.h"
#include "../../Red/Item.h"

#define MAPPOPUP_WIDTH 81
#define MAPPOPUP_HEIGHT 17

#define POPUPSTRING_MAXWIDTH 77
#define POPUPSTRING_MAXHEIGHT 15

#define MAXSTAGE 2

using namespace std;

class Inventory;
class PlayerInfo;

class UserManager
{
	SINGLETON(UserManager, )

private:
	int stage = 0;
	int stageKey = 0;

	Inventory* inventory = nullptr;
	Item* equipItem = nullptr;
	RandomItem random;

	PlayerInfo* player;


public:
	void Init();
	void GetKey();
	void ResetKey();
	bool CheckHasKey();

	void SetNextStage();

	void AddItem(int itemUID, int _count, bool _showAddPopup);
	Item* GetItemInfo(int itemUID);
	Item* GetItemInfo_fromIndex(ItemType _itemType ,int _index); 
	std::map<int, Item>* GetItemPartition(ItemType _itemType);
	Item* GetRandomItem(RandomItemType _randomType);

	void EquipItem(Item* _equipItem);
	Item* GetEquipItem() const { return equipItem; }

	int UsingItem(int _itemUID, int _count);
	inline int GetStage() { return stage; }

	inline PlayerInfo* GetPlayer() const { return player; }
};
