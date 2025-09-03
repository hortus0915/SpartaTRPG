#include "Black/MainGame.h"

#include "Black/CommonMacros.h"
#include "Black/Singletons/CommonManagers.h"

int main()
{
	int appPosX = 0;
	int appPosY = 0;

	int appWidth = 120;
	int appHeight = 50;

	int screenWidth = MAX_SCREEN_WIDTH;
	int screenHeight = MAX_SCREEN_HEIGTH;

	MainGame* mg = new MainGame(appPosX, appPosY, appWidth, appHeight, screenWidth, screenHeight);
	mg->Init();



	while (mg->IsGameRun())
	{


		TIMEMANAGER->Update(60.0f);
		mg->Update(TIMEMANAGER->GetElapsedTime());
		mg->Render();
	}

	SAFE_RELEASE_DELETE(mg);

	return 0;
}