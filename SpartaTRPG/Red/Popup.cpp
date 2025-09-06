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
		if (isActive)
		{
			InvokeActive(selectValue);
			POPUPMANAGER->PopupActiveOff();
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		if (customStringIndex > 0)
			customStringIndex--;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		if(hasCustonStringMore)
			customStringIndex++;
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
	customStringIndex = 0;
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
	selectValue = 0;
	customStringIndex = 0;
	leftPadding = 0;
	rightPadding = 0;
	upPadding = 0;
	downPadding = 0;
}

void Popup::RenderingCustomString()
{
	if (customString)
	{
		int moreLine = 0;
		for (int i = customStringIndex; i < (*customString).size(); i++)
		{
			if (i + moreLine + upPadding + downPadding >= POPUPSTRING_MAXHEIGHT - 1) 
			{
				hasCustonStringMore = true;
				break;
			}

			if ((*customString)[i].size() < MAPPOPUP_WIDTH - 2 - rightPadding)
				SCENEMANAGER->RenderToBackbuffer(
					(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + 1 + leftPadding,
					(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + 1 + i + moreLine + upPadding - customStringIndex,
					MAPPOPUP_WIDTH - 2 - rightPadding - leftPadding,
					1,
					(*customString)[i]);
			else
			{
				size_t pos = 0;
				while (pos < (*customString)[i].size())
				{
					if (i + moreLine + upPadding + downPadding >= POPUPSTRING_MAXHEIGHT - 1)
					{
						hasCustonStringMore = true;
						return;
					}
					size_t take = std::min<size_t>(MAPPOPUP_WIDTH - 2 - rightPadding - leftPadding, (*customString)[i].size() - pos);
					SCENEMANAGER->RenderToBackbuffer(
						(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + 1 + leftPadding,
						(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + 1 + i + moreLine + upPadding - customStringIndex,
						MAPPOPUP_WIDTH - 2 - rightPadding - leftPadding,
						1,
						(*customString)[i].substr(pos, take)
					);

					pos += take;

					if (pos < (*customString)[i].size())
						++moreLine;
				}
			}

			if (hasCustonStringMore) break;
		}

		if (hasCustonStringMore) {
			const int maxW = MAPPOPUP_WIDTH - 2 - rightPadding - leftPadding;
			const int arrowX =
				(MAX_SCREEN_WIDTH - MAPPOPUP_WIDTH) / 2 + 1 + leftPadding + maxW / 2;
			const int arrowY =
				(MAX_SCREEN_HEIGTH - MAPPOPUP_HEIGHT) / 2 + 1 + upPadding
				+ (POPUPSTRING_MAXHEIGHT - 1 - (upPadding + downPadding));

			SCENEMANAGER->RenderToBackbuffer(arrowX, arrowY, 1, 1, "v");
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
