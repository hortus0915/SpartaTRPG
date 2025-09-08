#include "SelectPopup.h"
#include "../Black/Singletons/CommonManagers.h"
#include "../Black/Singletons/PopupManager.h"

void SelectPopup::Update(float deltaTime)
{
	__super::Update(deltaTime);
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
		selectValue = 0;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		SOUNDMANAGER->PlaySfx(Text("CursorMove.wav"));
		selectValue = 1;
	}	
}

void SelectPopup::Render()
{
	__super::Render();
	SelectRender();
}

void SelectPopup::SelectRender()
{
	string yes = "[yes]";
	string no = "[no ]";
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 12, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, yes.size(), 1, yes);
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 44, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, no.size(), 1, no);
	string temp = "   ";

	if (selectValue == 0)
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 13, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, temp, GREEN, GREEN);
	else
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 45, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, temp, RED, RED);

	RenderingCustomString();
}

void SelectPopup::Init()
{
	__super::Init();
	selectValue = 0;
}
