#include "EffectShining.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"

#include <sstream>

using namespace std;

void EffectShining::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	bgColor = GetIntRange(BLACK + 1, COLOREND - 1);


	stringstream sstream;

	char c = '*';
	float ratio = elapsedTime / duration;
	if (ratio < 0.2f)
	{
		bgColor = DARKYELLOW;

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[0] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[1] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[2] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << c   << "@" << "@" << "@";
		image[3] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[4] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[5] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[6] = sstream.str();
	}
	else if (ratio < 0.4f)
	{
		bgColor = YELLOW;

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[0] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[1] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << c   << c   << c   << "@" << "@";
		image[2] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << c   << c   << c   << "@" << "@";
		image[3] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << c   << c   << c   << "@" << "@";
		image[4] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[5] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[6] = sstream.str();
	}
	else if (ratio < 0.6f)
	{
		bgColor = YELLOW;

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[0] = sstream.str();

		sstream.str("");
		sstream << "@" << c   << "@" << c   << "@" << c   << "@";
		image[1] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << c   << c   << c   << "@" << "@";
		image[2] = sstream.str();

		sstream.str("");
		sstream << "@" << c   << c   << "@" << c   << c   << "@";
		image[3] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << c   << c   << c   << "@" << "@";
		image[4] = sstream.str();

		sstream.str("");
		sstream << "@" << c   << "@" << c   << "@" << c   << "@";
		image[5] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[6] = sstream.str();
	}
	else if (ratio < 0.8f)
	{
		bgColor = YELLOW;

		sstream.str("");
		sstream << c   << "@" << "@" << c   << "@" << "@" << c  ;
		image[0] = sstream.str();

		sstream.str("");
		sstream << "@" << c   << "@" << c   << "@" << c   << "@";
		image[1] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[2] = sstream.str();

		sstream.str("");
		sstream << c   << c   << "@" << "@" << "@" << c   << c  ;
		image[3] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[4] = sstream.str();

		sstream.str("");
		sstream << "@" << c   << "@" << c   << "@" << c   << "@";
		image[5] = sstream.str();

		sstream.str("");
		sstream << c   << "@" << "@" << c   << "@" << "@" << c  ;
		image[6] = sstream.str();
	}
	else if (ratio < 1.0f)
	{
		bgColor = WHITE;

		sstream.str("");
		sstream << c   << "@" << "@" << c   << "@" << "@" << c  ;
		image[0] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[1] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[2] = sstream.str();

		sstream.str("");
		sstream << c   << "@" << "@" << "@" << "@" << "@" << c  ;
		image[3] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[4] = sstream.str();

		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@" << "@" << "@";
		image[5] = sstream.str();

		sstream.str("");
		sstream << c   << "@" << "@" << c   << "@" << "@" << c  ;
		image[6] = sstream.str();
	}
}

void EffectShining::Render()
{
	SCENEMANAGER->RenderToBackbuffer(posX, posY, image[4].size(), height, image, WHITE, bgColor);
}
