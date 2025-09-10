#include "InventoryPopup.h"
#include "../Black/Singletons/CommonManagers.h"
#include "../Blue/Card/CardData.h"
#include "../Blue/Card/CardDB.h"

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
			ShowItemDetail();
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		if (itemIndex > 0)
			itemIndex--;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		if (itemIndex < printLine && printLine * customStringPageIndex + itemIndex < customString->size() - 1)
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
			SetItemType(ItemType::Cost);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD2))
	{
		if (itemIndex != 2)
		{
			SetItemType(ItemType::Eequipment);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD3))
	{
		if (itemIndex != 3)
		{
			SetItemType(ItemType::Card);
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD4))
	{
		if (itemIndex != 4)
		{
			SetItemType(ItemType::Potion);
		}
	}

	if (KEYMANAGER->IsOnceKeyDown('1'))
	{
		if (itemIndex != 1)
		{
			SetItemType(ItemType::Cost);
		}
	}
	if (KEYMANAGER->IsOnceKeyDown('2'))
	{
		if (itemIndex != 2)
		{
			SetItemType(ItemType::Eequipment);
		}
	}
	if (KEYMANAGER->IsOnceKeyDown('3'))
	{
		if (itemIndex != 3)
		{
			SetItemType(ItemType::Card);
		}
	}
	if (KEYMANAGER->IsOnceKeyDown('4'))
	{
		if (itemIndex != 4)
		{
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
		"1.cost       2.equipment    3.card       4.Potion");
	auto temp = customString;
	RenderingCustomString();
	if (itemIndex >= 0)
	{
		SCENEMANAGER->RenderToBackbuffer(
			(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + leftPadding - 3,
			(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + itemIndex + upPadding,
			1,
			1,
			">");
	}
	SCENEMANAGER->RenderToBackbuffer(
		(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + CATEGORYLENGTH * (static_cast<int>(itemType) + 1),
		(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + 1
		, CATEGORYLENGTH, 1, "            ", GREEN, GREEN);
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
		if (_itemType == ItemType::Eequipment && (USERMANAGER->GetEquipItem() == nullptr || item.second.GetItemUID() == USERMANAGER->GetEquipItem()->GetItemUID()))
		{
			char buf[128];
			std::snprintf(buf, sizeof(buf), "아이템 이름 : %s , 수량 : %d - 장착", item.second.GetName().c_str(), item.second.GetItemCount());
			customString->push_back(buf);
		}
		else
		{
			char buf[128];
			std::snprintf(buf, sizeof(buf), "아이템 이름 : %s , 수량 : %d", item.second.GetName().c_str(), item.second.GetItemCount());
			customString->push_back(buf);
		}
	}

	if (customString->size() != 0)
		itemIndex = 0;
	else
		itemIndex = -1;
}

void InventoryPopup::ShowItemDetail()
{
	selectItem = USERMANAGER->GetItemInfo_fromIndex(itemType, printLine * customStringPageIndex + itemIndex);

	if (selectItem)
	{
		switch (Item::GetItemType(selectItem->GetItemUID()))
		{
		case ItemType::Cost:
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("상점에서 사용되는 재화");
			initString->push_back("");
			char buf[128];
			std::snprintf(buf, sizeof(buf), "%s을(를) %d개 갖고 있다", selectItem->GetName().c_str(), selectItem->GetItemCount());
			initString->push_back(buf);

			POPUPMANAGER->InitPopup<InventoryPopup, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				5,
				0
			);
			selectItem = nullptr;
			break;
		}
		case ItemType::Eequipment:
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("장비 아이템");
			initString->push_back("");
			char buf[128];
			std::snprintf(buf, sizeof(buf), "%s을(를) %d개 갖고 있다", selectItem->GetName().c_str(), selectItem->GetItemCount());
			initString->push_back(buf);
			initString->push_back("");
			initString->push_back("장착 하시겠습니까?");

			POPUPMANAGER->InitPopup<InventoryPopup, &InventoryPopup::EquipItem>(
				PopupType::SELECTPOPUP,
				this,
				initString,
				15,
				0,
				5,
				0
			);
			break;
		}
		case ItemType::Card:
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("전투에서 사용되는 카드");
			initString->push_back(" ");
			RenderCardInfo(initString);
			initString->push_back("");
			char buf[128];
			std::snprintf(buf, sizeof(buf), "%d개 갖고 있다", selectItem->GetItemCount());
			initString->push_back(buf);

			POPUPMANAGER->InitPopup<InventoryPopup, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				2,
				0
			);
			selectItem = nullptr;
			break;
		}

		case ItemType::Potion:
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("포션");
			initString->push_back("");
			char buf[128];
			std::snprintf(buf, sizeof(buf), "%s을(를) %d개 갖고 있다", selectItem->GetName().c_str(), selectItem->GetItemCount());
			initString->push_back(buf);
			initString->push_back("");
			initString->push_back("사용 하시겠습니까?");

			POPUPMANAGER->InitPopup<InventoryPopup, &InventoryPopup::UsingPotion>(
				PopupType::SELECTPOPUP,
				this,
				initString,
				15,
				0,
				5,
				0
			);
		}
		default:
			break;
		}
	}
}

void InventoryPopup::EquipItem(int _selectValue)
{
	if (_selectValue == 0)
	{
		USERMANAGER->EquipItem(selectItem);

		vector<string>* initString = new vector<string>();
		char buf[128];
		std::snprintf(buf, sizeof(buf), "%s을(를) 장착했습니다.", selectItem->GetName().c_str());
		initString->push_back(buf);


		POPUPMANAGER->InitPopup<InventoryPopup, nullptr>(
			PopupType::RESULTPOPUP,
			nullptr,
			initString,
			15,
			0,
			2,
			0
		);
	}

	selectItem = nullptr;
}

void InventoryPopup::UsingPotion(int _selectValue)
{
	if (_selectValue == 0 && selectItem != nullptr && Item::GetItemType(selectItem->GetItemUID()) == ItemType::Potion)
	{
		if (USERMANAGER->UsingItem(selectItem->GetItemUID(), 1) >= 0)
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("포션을 사용했습니다.");

			POPUPMANAGER->InitPopup<InventoryPopup, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				2,
				0
			);
		}
		else
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("아이템을 사용하지 못했습니다.");

			POPUPMANAGER->InitPopup<InventoryPopup, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				2,
				0
			);
		}
	}

	selectItem = nullptr;
}

void InventoryPopup::RenderCardInfo(vector<string>* _customString)
{
	int selectItemUID = selectItem->GetItemUID();
	if (selectItem &&  Item::GetItemType(selectItem->GetItemUID()) == ItemType::Card)
	{
		auto currentCard = CardDB::Get(selectItemUID % 10000);

		switch (currentCard->GetType())
		{
		case MOVE:
		{
			const char* arrows[9] =
			{
				 "↖","↑","↗",
				 "←"," ","→",
				 "↙","↓","↘"
			};

			int dirIdx = 4;
			for (int i = 0; i < 9; ++i) {
				if (currentCard->GetRange() & (1u << i)) { dirIdx = i; break; }
			}
			_customString->push_back(currentCard->GetName());
			char buf[128];
			std::snprintf(buf, sizeof(buf), "코스트 : %d", currentCard->GetStaminaCost());
			_customString->push_back(buf);
			_customString->push_back("타입 : 이동");
			std::snprintf(buf, sizeof(buf), "%s %d 칸", arrows[dirIdx], (int)currentCard->GetDamageRate());
			_customString->push_back(buf);

		}
		break;

		case ATTACK:
		{
			_customString->push_back(currentCard->GetName());

			char buf[128];
			std::snprintf(buf, sizeof(buf), "코스트 : %d", currentCard->GetStaminaCost());
			_customString->push_back(buf);
			_customString->push_back("타입 : 공격");

			std::snprintf(buf, sizeof(buf), "공격배율 : %f", currentCard->GetDamageRate());
			_customString->push_back(buf);
			_customString->push_back("");
			_customString->push_back("공격범위");

			string attackRange[9];
			for (int i = 0; i < 9; i++)
			{
				if (currentCard->GetRange() & (1u << i))
					attackRange[i] = "[X]";
				else
					attackRange[i] = "[ ]";
			}

			for (int i = 0; i < 3; ++i)
			{
				string temp = attackRange[0 + i * 3] + attackRange[1 + i * 3] + attackRange[2 + i * 3];
				_customString->push_back(temp);
			}
		}
		break;

		case SHIELD:
		{
			customString->push_back(currentCard->GetName());

			char buf[128];
			std::snprintf(buf, sizeof(buf), "코스트 : %d", currentCard->GetStaminaCost());
			_customString->push_back(buf);
			_customString->push_back("타입 : 방어");
			_customString->push_back("");
			std::snprintf(buf, sizeof(buf), "방어 : %d", (int)(currentCard->GetDamageRate() * 100));
			_customString->push_back(buf);
		}
		break;

		case HEAL:
		{
			int count = 5;
			_customString->push_back(currentCard->GetName());

			char buf[128];
			std::snprintf(buf, sizeof(buf), "코스트 : %d", currentCard->GetStaminaCost());
			_customString->push_back(buf);
			_customString->push_back("타입 : 힐");
			_customString->push_back("");

			bool hpHeal = (currentCard->GetDamageRate() > 0.0f);
			bool spHeal = (currentCard->GetStaminaCost() < 0);
			if (hpHeal)
			{
				_customString->push_back("");
				std::snprintf(buf, sizeof(buf), "체력 : %d", (int)currentCard->GetDamageRate());
				_customString->push_back(buf);
				--count;
			}
			if (spHeal)
			{
				_customString->push_back("");
				std::snprintf(buf, sizeof(buf), "마나 : %d", (int)currentCard->GetStaminaCost());
				_customString->push_back(buf);
				--count;
			}

		}
		break;
		}
	}
}
