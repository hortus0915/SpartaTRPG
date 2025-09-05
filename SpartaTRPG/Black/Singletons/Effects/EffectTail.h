#pragma once

#include "../Effect.h"

#include "../../TextColors.h"

class EffectTail : public Effect
{
private:
	string image;

	Color bgColor;

public:
	EffectTail(int _width, int _height, float _duration) : Effect(_width, _height, _duration) { }

	// Effect��(��) ���� ��ӵ�
	void Update(float _deltaTime) override;
	void Render() override;
};

