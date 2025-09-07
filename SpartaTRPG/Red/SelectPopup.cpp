#include "SelectPopup.h"
#include "../Black/Singletons/CommonManagers.h"

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

	if (isSelect)
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 13, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, temp, GREEN, GREEN);
	else
		SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) + 45, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) + MAPPOPUP_HEIGHT - 7, 3, 1, temp, RED, RED);
}

void SelectPopup::Init()
{
	__super::Init();
	isSelect = true;
}
