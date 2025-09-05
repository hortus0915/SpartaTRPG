#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

#include "SingletonMacro.h"

class Effect;

typedef map<string, vector<Effect*>>			EffectMap;
typedef map<string, vector<Effect*>>::iterator EffectMapIter;

class EffectManager
{
	SINGLETON(EffectManager, )

private:
	EffectMap mEffectMap;

public:

	void Update(float _deltaTime);
	void Render();

	Effect* StartEffect(string _effectName, int _posX, int _posY);
	Effect* StartEffect(string _effectName, int _startPosX, int _startPosY, int _endPosX, int _endPosY);

	Effect* FindEffect(string _effectName);
	Effect* CreateEffectInstance(string _effectName);
};

