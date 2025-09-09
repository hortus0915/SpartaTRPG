#include "ResultPopup.h"
#include "../Black/Singletons/CommonManagers.h"

void ResultPopup::Render()
{
	__super::Render();
	RenderingCustomString();
}

void ResultPopup::Init()
{
	__super::Init();
}

void ResultPopup::LateInit()
{
	if (active_cb_ != nullptr)
		mustActive = true;
	selectValue = 0;
}
