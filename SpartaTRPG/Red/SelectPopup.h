#pragma once
#include "Popup.h"

class SelectPopup : public Popup
{
private:
	void SelectRender();

public:
	SelectPopup() : Popup() {}

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Init() override;
};

