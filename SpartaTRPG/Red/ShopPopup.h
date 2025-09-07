#pragma once
#include "Popup.h"
#include <map>

class ShopPopup : public Popup
{
private:

	int itemIndex = 0;

	std::map<int, map<string, int>> itemTemp;

public:
	ShopPopup() : Popup() {}

	virtual void Render() override;
	virtual void Init() override;


};

