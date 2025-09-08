#include "InventoryPopup.h"
#include "../Black/Singletons/CommonManagers.h"

void InventoryPopup::Update(float deltaTime)
{
	if (KEYMANAGER->IsStayKeyDown(VK_BACK))
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
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (customStringPageIndex > 0)
			customStringPageIndex--;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if (customStringPageIndex)
			customStringPageIndex++;
	}
}

void InventoryPopup::Render()
{
	__super::Render();
	//카테고리 출력
	//customString으로 아이템 목록 출력
	//현제 선택중인 아이템 > 요거 이건 위에거랑 같이 넣고

	//사용 가능한 아이템인지 확인해서 사용, 버리기 버튼 활성화
	//사용 불가능한 아이템이면 버리기 버튼 가운데에 활성화
}

void InventoryPopup::Init()
{
	__super::Init();

	upPadding = 1;
	downPadding = 3;
	leftPadding = 8;

	if(!customString)
		customString = new vector<string>();

	SetItemType(ItemType::Cost);
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
		customString->emplace_back(buf);
	}
}
