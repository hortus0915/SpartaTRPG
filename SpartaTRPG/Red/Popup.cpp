#include "Popup.h"
#include "../Black/Singletons/CommonManagers.h"
#include "../Black/Singletons/PopupManager.h"

void Popup::Update(float deltaTime)
{
	if (KEYMANAGER->IsStayKeyDown(VK_BACK))
	{
		POPUPMANAGER->PopupActiveOff();
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RETURN))
	{
		if (selectValue >= 0 && isActive)
		{
			POPUPMANAGER->PopupActiveOff();
			InvokeActive(selectValue);
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		if (hasCustonStringMore && customStringPageIndex > 0)
			customStringPageIndex--;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		if(hasCustonStringMore && customStringPageIndex * (POPUPSTRING_MAXHEIGHT - downPadding - upPadding - 1) < customString->size())
			customStringPageIndex++;
	}
}

void Popup::Render()
{
	SCENEMANAGER->RenderToBackbuffer((MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2, (MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2, MAPPOPUP_WIDTH, MAPPOPUP_HEIGHT, image);
}

void Popup::SetPopupActiveCallback(ActiveCallback cb, void* user)
{
	active_cb_ = cb;
	active_user_ = user;
}

Popup::Popup()
{
	VariableInit();
	image = new char* [MAPPOPUP_HEIGHT];
	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		image[i] = new char[MAPPOPUP_WIDTH + 1];
		for (int j = 0; j < MAPPOPUP_WIDTH; ++j)
		{
			if (i == 0 || j == 0 || i == MAPPOPUP_HEIGHT - 1 || j == MAPPOPUP_WIDTH - 1)
				image[i][j] = '#';
			else
				image[i][j] = ' ';
		}
		image[i][MAPPOPUP_WIDTH] = '\0';
	}
}

void Popup::Release()
{
	if (customString)
		SAFE_DELETE(customString);

	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		SAFE_DELETE_ARR(image[i])
	}

	SAFE_DELETE_ARR(image)
}

void Popup::SetCustonStrings(vector<string>* _customString)
{
	if (customString)
		SAFE_DELETE(customString);

	customString = _customString;
	customStringPageIndex = 0;
}

void Popup::SetActive(bool active)
{
	isActive = active;
}

void Popup::SetCustomStringPadding(int _leftPadding, int _rightPadding, int _upPadding, int _downPadding)
{
	leftPadding = _leftPadding;
	rightPadding = _rightPadding;
	upPadding = _upPadding;
	downPadding = _downPadding;
}

void Popup::VariableInit()
{
	customString = nullptr;
	hasCustonStringMore = false;
	isActive = false;
	selectValue = -1;
	customStringPageIndex = 0;
	leftPadding = 0;
	rightPadding = 0;
	upPadding = 0;
	downPadding = 0;
}

void Popup::RenderingCustomString()
{
	if (customString)
	{
		int stringMaxX = POPUPSTRING_MAXWIDTH - leftPadding - rightPadding;
		int stringMaxY = POPUPSTRING_MAXHEIGHT - downPadding - upPadding;

		int printLine = stringMaxY;

		if (customString->size() >= stringMaxY - 1)
		{
			hasCustonStringMore = true;
			printLine -= 1;
		}

		for (int i = 0; i < printLine; i++)
		{
			if (printLine * customStringPageIndex + i >= customString->size() - 1)
				break;

			SCENEMANAGER->RenderToBackbuffer(
				(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + leftPadding,
				(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + i + upPadding,
				MAPPOPUP_WIDTH - rightPadding - leftPadding,
				1,
				(*customString)[printLine * customStringPageIndex + i]);
		}

		if (hasCustonStringMore)
		{
			if (customStringPageIndex > 0)
			{
				SCENEMANAGER->RenderToBackbuffer(
					MAX_SCREEN_WIDTH / 2 - 10,
					(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + stringMaxY + upPadding - 1,
					MAPPOPUP_WIDTH - rightPadding - leftPadding,
					1,
					"<");
			}
			if (customStringPageIndex * (POPUPSTRING_MAXHEIGHT - downPadding - upPadding - 1) < customString->size())
			{
				SCENEMANAGER->RenderToBackbuffer(
					MAX_SCREEN_WIDTH / 2 + 10,
					(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + stringMaxY + upPadding - 1,
					MAPPOPUP_WIDTH - rightPadding - leftPadding,
					1,
					">");
			}
		}
	}
}

void Popup::Init()
{
	VariableInit();

	SOUNDMANAGER->PlaySfx(TEXT("Buff1.wav"));

	if (customString)
		SAFE_DELETE(customString);

	for (int i = 0; i < MAPPOPUP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAPPOPUP_WIDTH; ++j)
		{
			if (i == 0 || j == 0 || i == MAPPOPUP_HEIGHT - 1 || j == MAPPOPUP_WIDTH - 1)
				image[i][j] = '#';
			else
				image[i][j] = ' ';
		}
		image[i][MAPPOPUP_WIDTH] = '\0';
	}
}
