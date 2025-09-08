#include "InventoryPopup.h"
#include "../Black/Singletons/CommonManagers.h"

void InventoryPopup::Update(float deltaTime)
{
	if (KEYMANAGER->IsStayKeyDown(VK_BACK) || KEYMANAGER->IsStayKeyDown(VK_ESCAPE))
	{
		POPUPMANAGER->PopupActiveOff();
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RETURN))
	{
		if (isActive)
		{
			POPUPMANAGER->PopupActiveOff();
			InvokeActive(selectValue);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		if (itemIndex > 0)
			itemIndex--;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		if (itemIndex < printLine && printLine * customStringPageIndex + itemIndex - 1 < customString->size())
			itemIndex++;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (customStringPageIndex > 0)
		{
			itemIndex = 0;
			customStringPageIndex--;
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if (hasCustonStringMore && (customStringPageIndex + 1) * printLine < customString->size())
		{
			itemIndex = 0;
			customStringPageIndex++;
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD1))
	{
		if (itemIndex != 1)
		{
			itemIndex = 1;
			SetItemType(ItemType::Cost);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD2))
	{
		if (itemIndex != 2)
		{
			itemIndex = 2;
			SetItemType(ItemType::Eequipment);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD3))
	{
		if (itemIndex != 3)
		{
			itemIndex = 3;
			SetItemType(ItemType::Potion);
		}
	}
}

void InventoryPopup::Render()
{
	__super::Render();

	SCENEMANAGER->RenderToBackbuffer(
		(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + CATEGORYLENGTH,
		(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + 1,
		CATEGORYLENGTH * 3 + 1,
		1,
		"1.cost             2.equipment    3.Potion");
	auto temp = customString;
	RenderingCustomString();

	SCENEMANAGER->RenderToBackbuffer(
		(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + leftPadding - 3,
		(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + itemIndex + upPadding,
		1,
		1,
		">");
}

void InventoryPopup::Init()
{
	__super::Init();

	if(!customString)
		customString = new vector<string>();
	
	SetItemType(ItemType::Cost);
}

void InventoryPopup::SetCustomStringPadding(int _leftPadding, int _rightPadding, int _upPadding, int _downPadding)
{
	leftPadding = 15;
	upPadding = 3;
}

void InventoryPopup::SetItemType(ItemType _itemType)
{
	customString->clear();
	itemType = _itemType;
	auto partition = USERMANAGER->GetItemPartition(itemType);

	for (auto item : *partition)
	{
		char buf[128];
		std::snprintf(buf, sizeof(buf), "아이템 이름 : %s , 수량 : %d", item.second.GetName().c_str(), item.second.GetItemCount());
		customString->push_back(buf);
	}
}

void InventoryPopup::ShowItemDetail(int _itemUID)
{
	auto selectItem = USERMANAGER->GetItemInfo_fromIndex(itemType, printLine * customStringPageIndex + itemIndex);
}
