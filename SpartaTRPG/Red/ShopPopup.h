#pragma once
#include "Popup.h"
#include <map>
#include "Item.h"

class ShopPopup : public Popup
{
private:
	ItemType itemType;
	int itemIndex;
public:
	ShopPopup() : Popup() { itemType = ItemType::Eequipment; itemIndex = 0; }

	virtual void Render() override;
	virtual void Init() override;


};

