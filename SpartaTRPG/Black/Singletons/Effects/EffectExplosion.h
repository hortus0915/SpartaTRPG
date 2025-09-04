#pragma once

#include "../Effect.h"

#include "../../TextColors.h"

class EffectExplosion : public Effect
{
private:
	string image[5];

	Color bgColor;

public:
	EffectExplosion(int _width, int _height, float _duration) : Effect(_width, _height, _duration) { }

	// Effect을(를) 통해 상속됨
	void Update(float _deltaTime) override;
	void Render() override;
};

