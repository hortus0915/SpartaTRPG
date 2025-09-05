#pragma once
#include "Popup.h"

class SelectPopup : public Popup
{
private:
	bool isSelect = true;
	void SelectRender();

public:

	SelectPopup(string _targetSecene) : Popup(_targetSecene) {}

	virtual void Render() override;
	virtual void Init() override;

	inline bool CheckSelect() { return isSelect; }
	inline void Select(bool _isSelect) { isSelect = _isSelect; }
};

