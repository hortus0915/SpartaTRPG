#include "NPCDialoguePopup.h"
#include "../Black/Singletons/CommonManagers.h"
#include "../Black/Singletons/PopupManager.h"

void NPCDialoguePopup::RenderingCustomString()
{
	if (customString)
	{
		int stringMaxX = posX + width - leftPadding - rightPadding;
		int stringMaxY = posY + height - downPadding - upPadding;

		printLine = stringMaxY;

		if (customString->size() >= stringMaxY - 1)
		{
			hasCustonStringMore = true;
			printLine -= 1;
		}

		for (int i = 0; i < printLine; i++)
		{
			if (printLine * customStringPageIndex + i >= customString->size())
				break;

			SCENEMANAGER->RenderToBackbuffer(
				posX + leftPadding,
				posY + i + upPadding,
				width - rightPadding - leftPadding,
				1,
				(*customString)[printLine * customStringPageIndex + i]);
		}

		if (hasCustonStringMore)
		{
			if (customStringPageIndex > 0)
			{
				SCENEMANAGER->RenderToBackbuffer(
					posX + width / 2 - 10,
					posY + stringMaxY + upPadding - 1,
					width - rightPadding - leftPadding,
					1,
					"<");
			}
			if ((customStringPageIndex + 1) * printLine < customString->size())
			{
				SCENEMANAGER->RenderToBackbuffer(
					posX + width / 2 + 10,
					posY + stringMaxY + upPadding - 1,
					width - rightPadding - leftPadding,
					1,
					">");
			}
		}
	}
}

void NPCDialoguePopup::Render()
{
	SCENEMANAGER->RenderToBackbuffer(posX, posY, width, height, image, YELLOW);
	RenderingCustomString();
}

void NPCDialoguePopup::Init()
{
	VariableInit();
	selectValue = 1;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
				image[i][j] = 'o';
			else
				image[i][j] = ' ';
		}
		image[i][width] = '\0';
	}
}
