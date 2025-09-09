#include "ShopScene.h"

#include "../CommonManagers.h"

#include "ShopSceneBaseHud.h"
#include "ShopSceneItemHud.h"

#include "../../BlinkCursor.h"

#include "../../../Blue/Card/CardDB.h"

#include <sstream>

//    #####################  #####################################
//  ######################## #                                   #
// ###########################  < Q        Equipment        E >  #
//################################################################
//#                          #                                   #
//#     S    H    O    P     #                ^                  #
//#                          # [ ] Item Name                     #
//############################                                   #
//#  						 # [ ] Item Name                     #
//#                 ***** 	 #                                   #
//#        ********  *****	 # [ ] Item Name                     #
//#      ******************	 #                                   #
//#     *** O**** O*** ****	 # [ ] Item Name                     #
//#     ***  ****  ***  ***	 #                                   #
//#      ************    **	 # [ ] Item Name                     #
//#         ******        *	 #                                   #
//#     **************     * # [ ] Item Name                     #
//#   *******************	 #                v                  #
//#  *********************	 #                                   #
//################################################################
// 소지금 : 100G
// ------------------------- I N F O ----------------------------
// 이동
// Cost : 10
// 타입 : 이동
// Desc
// --------------------------------------------------------------

void ShopScene::ItemSetting()
{
	int uid = Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 1);
	auto ret = shopItemList[ItemType::Eequipment].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 2);
	ret = shopItemList[ItemType::Eequipment].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 3);
	ret = shopItemList[ItemType::Eequipment].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();





	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 1);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 2);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 3);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 4);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 5);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 6);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 7);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 8);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 11);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 12);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 13);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 14);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();


	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 1);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 2);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 3);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();


	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 1);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 2);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 3);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 4);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();


	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 1);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 2);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 3);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 4);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 5);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 6);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 7);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 8);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 9);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 10);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 11);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 12);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 13);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 14);
	ret = shopItemList[ItemType::Card].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();



	uid = Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1);
	ret = shopItemList[ItemType::Potion].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2);
	ret = shopItemList[ItemType::Potion].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();

	uid = Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3);
	ret = shopItemList[ItemType::Potion].try_emplace(uid, uid);
	if (!ret.second) ret.first->second.AddItem();
}

int ShopScene::Init()
{
	CardDB::InitDefaults();

	posX = 27;
	posY = 0;

	if (!baseUi)
		baseUi = new ShopSceneBaseHud("ShopScene");
	if (!selectedItemUI)
		selectedItemUI = new ShopSceneItemHud("ShopScene");

	baseUi->Init(0, 0);
	selectedItemUI->Init(1, 23);

	if (shopItemList.size() <= 0)
	{
		ItemSetting();
	}

	menu[0]  = "#####################################";
	menu[1]  = "#                                   #";
	menu[2]  = "#  < Q                         E >  #";
	menu[3]  = "#####################################";
	menu[4]  = "#                                   #";
	menu[5]  = "#                                   #";
	menu[6]  = "#                                   #";
	menu[7]  = "#                                   #";
	menu[8]  = "#                                   #";
	menu[9]  = "#                                   #";
	menu[10] = "#                                   #";
	menu[11] = "#                                   #";
	menu[12] = "#                                   #";
	menu[13] = "#                                   #";
	menu[14] = "#                                   #";
	menu[15] = "#                                   #";
	menu[16] = "#                                   #";
	menu[17] = "#                                   #";
	menu[18] = "#                                   #";
	menu[19] = "#####################################";

	currentContentPage = (ItemType)((int)ItemType::Cost + 1);
	currentItemIdx = 0;
	currentItemPage = 0;
	contentsInPage = 6;

	if (!contents)
		contents = new string[contentsInPage];

	if (!upArrow)
		upArrow = new BlinkCursor("ShopScene");
	if (!downArrow)
		downArrow = new BlinkCursor("ShopScene");
	if (!cursor)
		cursor = new BlinkCursor("ShopScene");

	upArrow->SetPos(posX + 17, posY + 5);
	upArrow->SetShape("^");
	downArrow->SetPos(posX + 17, posY + 17);
	downArrow->SetShape("v");

	return 0;
}

void ShopScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	if (currentContentPage == ItemType::Eequipment)
		title = "장비";
	else if (currentContentPage == ItemType::Card)
		title = "카드";
	else if (currentContentPage == ItemType::Potion)
		title = "포션";

	auto& currentList = shopItemList[currentContentPage];

	if (KEYMANAGER->IsOnceKeyDown('Q'))
	{
		currentItemIdx = 0;
		currentContentPage = (ItemType)(((int)currentContentPage -1 + (int)ItemType::MAX) % (int)ItemType::MAX);
		if ((int)currentContentPage <= 0) currentContentPage = (ItemType)((int)ItemType::MAX - 1);
	}
	if (KEYMANAGER->IsOnceKeyDown('E'))
	{
		currentItemIdx = 0;
		currentContentPage = (ItemType)(((int)currentContentPage + 1) % (int)ItemType::MAX);
		if ((int)currentContentPage <= 0) currentContentPage = ItemType::Eequipment;
	}

	//if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
	//{
	//	if ((currentItemIdx - contentsInPage) >= 0)
	//	{
	//		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
	//		currentItemIdx = (currentItemIdx - contentsInPage + currentList.size()) % currentList.size();
	//	}
	//}
	//if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
	//{
	//	if ((currentItemIdx + contentsInPage) < currentList.size())
	//	{
	//		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
	//		currentItemIdx = (currentItemIdx + contentsInPage) % currentList.size();
	//	}
	//}
	if (KEYMANAGER->IsOnceKeyDown(VK_UP))
	{
		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
		currentItemIdx = (currentItemIdx - 1 + currentList.size()) % currentList.size();
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
		currentItemIdx = (currentItemIdx + 1) % currentList.size();
	}
	currentItemPage = (currentItemIdx / contentsInPage);

	auto originIter = currentList.begin();
	for (int i = 0; i < (currentItemPage * contentsInPage); ++i)
		++originIter;

	auto iter = originIter;
	stringstream sStream;
	for (int i = 0; i < contentsInPage; ++i)
	{
		contents[i] = "";

		sStream.str("");

		iter = originIter;
		for (int j = 0; j < i; ++j)
		{
			if (iter != currentList.end())
				++iter;
		}

		if (iter == currentList.end()) continue;

		int uid = iter->second.GetItemUID();
		sStream << "[ ] " << iter->second.GetName() << " (" << GetCost(uid) << "G)";
		contents[i] = sStream.str();
	}

	int originPosX = 3 + posX;
	int originPosY = 6 + posY;
	cursor->SetPos(originPosX, originPosY + (currentItemIdx % contentsInPage) * 2);

	iter = currentList.begin();
	for (int i = 0; i < currentItemIdx; ++i)
		++iter;
	selectedItemUI->SetItem(&iter->second, GetCost(iter->second.GetItemUID()));

	if (KEYMANAGER->IsOnceKeyDown(VK_RETURN))
	{
		if (BuyItem(iter->second))
		{
			baseUi->DelightTrigger();

		}
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_BACK))
	{
		SCENEMANAGER->ChangeChild("DungeonScene");
	}

	gold = "소지금 : " + to_string(GetGold()) + "G";
}

void ShopScene::Release()
{
	SAFE_RELEASE_DELETE(baseUi)
	SAFE_RELEASE_DELETE(selectedItemUI)
	SAFE_DELETE_ARR(contents)
}

void ShopScene::Render()
{
	__super::Render();

	for (int i = 0; i < 20; ++i)
	{
		SCENEMANAGER->RenderToBackbuffer(posX, posY + i, menu[i].size(), 1, menu[i]);
	}
	SCENEMANAGER->RenderToBackbuffer(posX + menu[0].size() / 2 - title.size() / 2, posY + 2, title.size(), 1, title);

	auto& currentList = shopItemList[currentContentPage];
	if (contentsInPage < currentList.size())
	{
		upArrow->Render();
		downArrow->Render();
	}

	int originPosX = 2 + posX;
	int originPosY = 6 + posY;
	for (int i = 0; i < contentsInPage; ++i)
	{
		SCENEMANAGER->RenderToBackbuffer(originPosX, originPosY + i * 2, contents[i].size(), 1, contents[i]);
	}
	cursor->Render();

	SCENEMANAGER->RenderToBackbuffer(1, 21, gold.size(), 1, gold);
}

bool ShopScene::BuyItem(Item _item)
{
	if (!IsCanBuyItem(_item))
		return false;

	int uid = Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1);
	int cost = GetCost(_item.GetItemUID());
	int targetItemUID = _item.GetItemUID();

	USERMANAGER->UsingItem(uid, cost);
	USERMANAGER->AddItem(targetItemUID);

	return true;
}

bool ShopScene::IsCanBuyItem(Item _item)
{
	int targetUID = _item.GetItemUID();
	return  GetGold() >= GetCost(_item.GetItemUID());
}

int ShopScene::GetGold()
{
	int uid = Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1);
	return USERMANAGER->GetItemInfo(uid)->GetValue();
}

int ShopScene::GetCost(int _itemUID)
{
	switch (_itemUID)
	{
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 1):
		return 100;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 2):
		return 200;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 3):
		return 300;




	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 1):
		return 10;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 2):
		return 10;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 3):
		return 10;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 4):
		return 10;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 5):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 6):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 7):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 8):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 11):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 12):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 13):
		return 100;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 14):
		return 100;

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 1):
		return 150;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 2):
		return 300;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 3):
		return 500;

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 1):
		return 200;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 2):
		return 200;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 3):
		return 500;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 4):
		return 1000;

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 1):
		return 45;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 2):
		return 26;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 3):
		return 22;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 4):
		return 20;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 5):
		return 20;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 6):
		return 30;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 7):
		return 44;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 8):
		return 50;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 9):
		return 33;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 10):
		return 33;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 11):
		return 33;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 12):
		return 33;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 13):
		return 30;
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 14):
		return 150;




	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1):
		return 200;
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2):
		return 400;
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3):
		return 1000;




	default:
		return {};
	}

	return -1;
}
