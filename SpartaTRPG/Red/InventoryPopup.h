#pragma once
#include "Popup.h"
#include <map>
#include "Item.h"

#define CATEGORYLENGTH 13

class InventoryPopup : public Popup
{
private:
	ItemType itemType;
	int itemIndex;
	Item* selectItem;

	const int maxPartitionIndex = static_cast<int>(ItemType::MAX);

	std::map<ItemType, vector<string>*> partitionString;
public:
	InventoryPopup() : Popup() { itemType = ItemType::Eequipment; itemIndex = 0;}

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Init() override;

	virtual void SetCustomStringPadding(int _leftPadding = 0, int _rightPadding = 0, int _upPadding = 0, int _downPadding = 0) override;
	void SetItemType(ItemType _itemType);
	void ShowItemDetail();

	void EquipItem(int _selectValue);
	void UsingPotion(int _selectValue);
	void RenderCardInfo(vector<string>* _customString);

};

