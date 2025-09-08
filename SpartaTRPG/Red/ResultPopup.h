#pragma once
#include "Popup.h"

class ResultPopup : public Popup
{
private:
public:
	ResultPopup() : Popup() {}

	virtual void Render() override;
	virtual void Init() override;
};

