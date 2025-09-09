#include "LogManager.h"
#include "CommonManagers.h"

LogManager* LogManager::instance = nullptr;

void LogManager::Update(float deltaTime)
{
	if (!POPUPMANAGER->CheckPopupActive())
	{
		if (KEYMANAGER->IsStayKeyDown(VK_F1))
		{
			POPUPMANAGER->InitPopup<LogManager, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				&allLog,
				15,
				0,
				5,
				0
			);
		}
	}
}

void LogManager::AddLog(string log)
{
	allLog.push_back(log);
}

void LogManager::Init()
{
	allLog.clear();
}




