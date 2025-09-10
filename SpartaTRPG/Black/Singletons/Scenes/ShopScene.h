#pragma once
#include "../SceneInterface.h"

#include "../../CommonMacros.h"

#include "../../../Red/Item.h"

#include <map>
#include <vector>

using namespace std;

class ShopSceneBaseHud;
class ShopSceneItemHud;
class BlinkCursor;

typedef int ItemUID;

class ShopScene : public iScene
{
private:
	int posX, posY;

	std::map<ItemType, std::map<ItemUID, Item>> shopItemList;

	string menu[20];
	string title;
	string* contents;
	string gold;
	ItemType currentContentPage;
	int currentItemIdx;
	int currentItemPage;
	int contentsInPage;

	BlinkCursor* upArrow;
	BlinkCursor* downArrow;
	BlinkCursor* cursor;

	bool isDialogueOpen;

	ShopSceneBaseHud* baseUi;
	ShopSceneItemHud* selectedItemUI;


public:
	ShopScene(string _sceneName) : iScene(_sceneName), baseUi(nullptr), selectedItemUI(nullptr), contents(nullptr), isDialogueOpen(false) {}

	void ItemSetting();

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Update(float deltaTime) override;
	void Release() override;
	void Render() override;

	bool BuyItem(Item _item);
	bool IsCanBuyItem(Item _item);

	int GetGold();

	int GetCost(int _itemUID);
};

