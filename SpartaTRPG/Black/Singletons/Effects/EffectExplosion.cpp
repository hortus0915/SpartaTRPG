#include "EffectExplosion.h"

#include "../CommonManagers.h"
#include "../../CommonFuncs.h"

#include <sstream>

using namespace std;

void EffectExplosion::Update(float _deltaTime)
{
	__super::Update(_deltaTime);

	bgColor = GetIntRange(BLACK + 1, COLOREND - 1);


	stringstream sstream;

	char c;
	float ratio = elapsedTime / duration;
	if (ratio < 0.2f)
	{
		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[0] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[1] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << c    << "@" << "@";
		image[2] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[3] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[4] = sstream.str();
	}
	else if (ratio < 0.4f)
	{
		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[0] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << c    << "@" << "@";
		image[1] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << c    << c    << c    << "@";
		image[2] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << c    << "@" << "@";
		image[3] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[4] = sstream.str();
	}
	else if (ratio < 0.6f)
	{
		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << c    << "@" << "@";
		image[0] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << c    << "@" << c    << "@";
		image[1] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << c    << "@" << "@" << "@" << c   ;
		image[2] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << c    << "@" << c    << "@";
		image[3] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << c    << "@" << "@";
		image[4] = sstream.str();
	}
	else if (ratio < 0.8f)
	{
		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << c    << "@" << c    << "@";
		image[0] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << c    << "@" << "@" << "@" << c   ;
		image[1] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[2] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << c    << "@" << "@" << "@" << c   ;
		image[3] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << c    << "@" << c    << "@";
		image[4] = sstream.str();
	}
	else if (ratio < 1.0f)
	{
		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << c    << "@" << "@" << "@" << c   ;
		image[0] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[1] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[2] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << "@" << "@" << "@" << "@" << "@";
		image[3] = sstream.str();

		c = GetIntRange('!', '?');
		sstream.str("");
		sstream << c    << "@" << "@" << "@" << c   ;
		image[4] = sstream.str();
	}
}

void EffectExplosion::Render()
{
	SCENEMANAGER->RenderToBackbuffer(posX, posY, image[4].size(), height, image, COLOREND - bgColor - 1, bgColor);
}
