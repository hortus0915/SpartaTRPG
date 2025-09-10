#include "Item.h"

Item::Item(int _itemUID, int _itemCount)
	: itemUID(_itemUID)
{
	SetItemValue(_itemUID);
	count = _itemCount;
}

void Item::AddItem(int _count)
{
	count += _count;
}

int Item::UsingItem(int usingCount)
{
	if (count < usingCount)
		return -1;

	return count -= usingCount;
}

void Item::SetItemValue(int _itemUID)
{
	switch (_itemUID)
	{
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1):

		value = 100;
		break;
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 2):
		value = 50;
		break;





	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 1):
		value = 10;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 2):
		value = 20;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 3):
		value = 30;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 4):
		value = 50;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 5):
		value = 60;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 6):
		value = 70;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 7):
		value = 80;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 8):
		value = 90;
		break;
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 9):
		value = 100;
		break;




	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 1):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 2):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 3):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 4):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 5):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 6):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 7):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 8):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 11):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 12):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 13):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 14):

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 1):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 2):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 3):

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 1):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 2):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 3):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 4):

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 1):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 2):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 3):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 4):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 5):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 6):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 7):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 8):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 9):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 10):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 11):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 12):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 13):
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 14):
		value = 1;




	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1):
		value = 20;
		break;
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2):
		value = 40;
		break;
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3):
		value = 100;
		break;



	default:
		break;
	}
}

std::string Item::GetName()
{
	switch (itemUID)
	{
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1):
		return "골드";
	case Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 2):
		return "다이아몬드";




	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 1):
		return "검";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 2):
		return "지팡이";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 3):
		return "활";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 4):
		return "좋은 칼";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 5):
		return "마우스";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 6):
		return "키보드";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 7):
		return "모니터";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 8):
		return "GeForce RTX 5060";
	case Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_ATTACK, 9):
		return "GeForce RTX 5090";




	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 1):
		return "한칸이동 →";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 2):
		return "한칸이동 ←";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 3):
		return "한칸이동 ↑";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 4):
		return "한칸이동 ↓";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 5):
		return "한칸이동↖";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 6):
		return "한칸이동↗";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 7):
		return "한칸이동↘";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 8):
		return "한칸이동↙";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 11):
		return "두칸이동 →";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 12):
		return "두칸이동 ←";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 13):
		return "두칸이동 ↑";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_MOVE, 14):
		return "두칸이동 ↓";

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 1):
		return "막기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 2):
		return "가드 업";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_SHIELD, 3):
		return "전면 방어";

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 1):
		return "응급 처치";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 2):
		return "기합";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 3):
		return "보급";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_HEAL, 4):
		return "회복";

	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 1):
		return "찌르기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 2):
		return "회전 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 3):
		return "십자 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 4):
		return "전방 일자 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 5):
		return "가로 일자 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 6):
		return "광역 십자 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 7):
		return "대각선 베기";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 8):
		return "원형 일격";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 9):
		return "부채꼴 찌르기(상)";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 10):
		return "부채꼴 베기(하)";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 11):
		return "부채꼴 베기(좌)";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 12):
		return "부채꼴 베기(우)";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 13):
		return "충격파";
	case Item::GetItemUID(ItemType::Card, ItemValueType::CardUID_ATTACK, 14):
		return "제자리 강타";




	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1):
		return "체력 포션(소)";
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2):
		return "체력 포션(중)";
	case Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3):
		return "체력 포션(대)";




	default:
		return {};
	}
}

int Item::GetItemCount()
{
	return count;
}
