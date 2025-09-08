#pragma once
#include "Popup.h"
#include <map>
#include "Item.h"

class InventoryPopup : public Popup
{
private:
	ItemType itemType;
	int itemIndex;

	const int maxPartitionIndex = static_cast<int>(ItemType::MAX);

	std::map<ItemType, vector<string>*> partitionString;
public:
	InventoryPopup() : Popup() { itemType = ItemType::Eequipment; itemIndex = 0;}

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Init() override;

	void SetItemType(ItemType _itemType);
};

