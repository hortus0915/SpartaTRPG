#pragma once

#include "../Effect.h"

#include "../../TextColors.h"

class EffectSlash : public Effect
{
private:
	string image[5];

	Color bgColor;

public:
	EffectSlash(int _width, int _height, float _duration) : Effect(_width, _height, _duration)
	{
		image[0] = "@";
		image[1] = "@";
		image[2] = "@";
		image[3] = "@";
		image[4] = "@";
	}

	// Effect을(를) 통해 상속됨
	void Update(float _deltaTime) override;
	void Render() override;
};

