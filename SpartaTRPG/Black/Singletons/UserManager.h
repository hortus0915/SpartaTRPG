#pragma once

#include <vector>
#include <map>

using namespace std;

#include "../Singletons/SingletonMacro.h"
#include "../../Red/Item.h"

#define MAPPOPUP_WIDTH 81
#define MAPPOPUP_HEIGHT 17

#define POPUPSTRING_MAXWIDTH 77
#define POPUPSTRING_MAXHEIGHT 15

using namespace std;

class Inventory;

class UserManager
{
	SINGLETON(UserManager, )

private:
	int stage = 0;
	int stageKey = 0;

	Inventory* inventory = nullptr;
public:
	void Init();
	void GetKey();
	void ResetKey();
	bool CheckHasKey();

	void SetNextStage();

	void AddItem(int itemUID);
	Item* GetItemInfo(int itemUID);
	Item* GetItemInfo_fromIndex(ItemType itemType ,int index); 
	std::map<int, Item>* GetItemPartition(ItemType _itemType);

	int UsingItem(int itemUID, int count);
	inline int GetStage() { return stage; }
};
