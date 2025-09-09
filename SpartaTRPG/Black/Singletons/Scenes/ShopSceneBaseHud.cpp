#include "ShopSceneBaseHud.h"

#include "../CommonManagers.h"

#include "ShopSceneNPC.h"

// 0 //    #####################
// 1 //  ########################
// 2 // ##########################
// 3 //############################
// 4 //#                          #
// 5 //#     S    H    O    P     #
// 6 //#                          #
// 7 //############################
// 8 //#                          #
// 9 //#                 *****    #
//10 //#        ********  *****   #
//11 //#      ******************  #
//12 //#     *** O**** O*** ****  #
//13 //#     ***  ****  ***  ***  #
//14 //#      ************    **  #
//15 //#         ******        *  #
//16 //#     **************     * #
//17 //#   *******************    #
//18 //#  *********************   #
//19 //############################


void ShopSceneBaseHud::Init(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;

	image[ 0] = "    #####################";
	image[ 1] = "  ########################";
	image[ 2] = " ##########################";
	image[ 3] = "############################";
	image[ 4] = "#                          #";
	image[ 5] = "#     S    H    O    P     #";
	image[ 6] = "#                          #";
	image[ 7] = "############################";
	image[ 8] = "#                          #";
	image[ 9] = "#                          #";
	image[10] = "#                          #";
	image[11] = "#                          #";
	image[12] = "#                          #";
	image[13] = "#                          #";
	image[14] = "#                          #";
	image[15] = "#                          #";
	image[16] = "#                          #";
	image[17] = "#                          #";
	image[18] = "#                          #";
	image[19] = "############################";



	if (!npc)
		npc = new ShopSceneNPC("ShopScene");

	npc->Init(posX + 3, posY + 9);
}

void ShopSceneBaseHud::Release()
{
	SAFE_RELEASE_DELETE(npc)
}

void ShopSceneBaseHud::Render()
{
	for (int i = 0; i < 20; ++i)
	{
		SCENEMANAGER->RenderToBackbuffer(posX, posY + i, image[i].size(), 1, image[i]);
	}
}

void ShopSceneBaseHud::DelightTrigger()
{
	if (npc)
		npc->DelightTrigger();
}
