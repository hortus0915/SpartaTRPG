#include "PopupManager.h"

#include "../../Black/CommonMacros.h"
#include "../../Black/MainGame.h"
#include "../BasicInterfaces.h"
#include "../../Red/Popup.h"
#include "../../Red/ResultPopup.h"
#include "../../Red/SelectPopup.h"

PopupManager* PopupManager::instance = nullptr;

void PopupManager::Update(float deltaTime)
{
	if (activePopup)
		activePopup->Update(deltaTime);
}

void PopupManager::Init(MainGame* _mg)
{
	activePopup = nullptr;

	mainGame = _mg;

	mPopupList.insert(make_pair(PopupType::RESULTPOPUP, new ResultPopup()));
	mPopupList.insert(make_pair(PopupType::SELECTPOPUP, new SelectPopup()));
}

void PopupManager::Render()
{
	if (activePopup)
		activePopup->Render();
}

void PopupManager::PopupActiveOff()
{
	if (activePopup)
	{
		activePopup->SetActive(false);
		activePopup = nullptr;
	}
}

bool PopupManager::CheckPopupActive()
{
	if (activePopup && activePopup->CheckActive())
		return true;

	return false;
}

void PopupManager::Release()
{
	for (auto popup : mPopupList)
	{
		if (popup.second)
		{
			SAFE_DELETE(popup.second);
		}
	}
}


