#pragma once

#include "../Effect.h"

class EffectShining : public Effect
{
private:
	string image[7];

	Color bgColor;

public:
	EffectShining(int _width, int _height, float _duration) : Effect(_width, _height, _duration) {}

	// Effect을(를) 통해 상속됨
	void Update(float _deltaTime) override;
	void Render() override;
};

