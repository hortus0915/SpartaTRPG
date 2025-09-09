#include "ShopSceneNPC.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"

// 0//                ***** 
// 1//       ********  *****
// 2//     ******************
// 3//    *** O**** O*** ****
// 4//    ***  ****  ***  ***
// 5//     ************    **
// 6//        ******        *
// 7//    **************     *
// 8//  *******************	
// 9// *********************

void ShopSceneNPC::Init(int _posX, int _posY)
{
	posX = _posX;
	posY = _posY;

	image[0] = "@@@@@@@@@@@@@@@*****@@@";
	image[1] = "@@@@@@********@@*****@@";
	image[2] = "@@@@******************@";
	image[3] = "@@@***@@****@@***@****@";
	image[4] = "@@@***@@****@@***@@***@";
	image[5] = "@@@@************@@@@**@";
	image[6] = "@@@@@@@******@@@@@@@@*@";
	image[7] = "@@@**************@@@@@*";
	image[8] = "@*******************@@@";
	image[9] = "*********************@@";

	eye[0] = " O";
	eye[1] = "  ";

	currentState = Idle;
	delightCurrentTime = 0.0f;
	delightDuration = GetFloatRange(2.0f, 4.0f);
}

void ShopSceneNPC::Update(float _deltaTime)
{
	switch (currentState)
	{
		case Idle:
		{
			delightCurrentTime += _deltaTime;
			if (delightCurrentTime < delightDuration * 0.7f)
			{
				eye[0] = " O";
				eye[1] = "  ";
			}
			else if (delightCurrentTime < delightDuration * 0.75f)
			{
				eye[0] = "__";
				eye[1] = "  ";
			}
			else if (delightCurrentTime < delightDuration * 0.8f)
			{
				eye[0] = " O";
				eye[1] = "  ";
			}
			else if (delightCurrentTime < delightDuration * 0.85f)
			{
				eye[0] = "__";
				eye[1] = "  ";
			}
			else if (delightCurrentTime < delightDuration)
			{
				eye[0] = " O";
				eye[1] = "  ";
			}

			if (delightCurrentTime >= delightDuration)
			{
				delightCurrentTime = 0.0f;
				delightDuration = GetFloatRange(2.0f, 4.0f);
			}
		}
		break;

		case Delight:
		{
			eye[0] = "/\\";
			eye[1] = "**";

			delightCurrentTime += _deltaTime;
			if (delightCurrentTime >= delightDuration)
			{
				delightCurrentTime = 0.0f;
				delightDuration = GetFloatRange(2.0f, 4.0f);
			}
		}
		break;
	}
}

void ShopSceneNPC::Release()
{

}

void ShopSceneNPC::Render()
{
	SCENEMANAGER->RenderToBackbuffer(posX, posY, image[0].size(), 10, image, ORIGINCOLOR, BLACK);

	SCENEMANAGER->RenderToBackbuffer(posX + 6 , posY + 3, eye[0].size(), 1, eye[0], WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + 6 , posY + 4, eye[1].size(), 1, eye[1], WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + 12, posY + 3, eye[0].size(), 1, eye[0], WHITE, BLACK);
	SCENEMANAGER->RenderToBackbuffer(posX + 12, posY + 4, eye[1].size(), 1, eye[1], WHITE, BLACK);
}
