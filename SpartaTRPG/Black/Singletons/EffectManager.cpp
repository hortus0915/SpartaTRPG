#include "EffectManager.h"

#include "../CommonMacros.h"

#include "Effect.h"
#include "EffectType.h"

#include <typeinfo>

EffectManager* EffectManager::instance = nullptr;

void EffectManager::Release()
{
	for (auto& m : mEffectMap)
	{
		for (auto& v : m.second)
		{
			SAFE_DELETE(v);
		}
	}
}


void EffectManager::Update(float deltaTime)
{
	for (auto& m : mEffectMap)
	{
		for (auto& v : m.second)
		{
			if (v->IsRunning())
				v->Update(deltaTime);
		}
	}
}
void EffectManager::Render()
{
	for (auto& m : mEffectMap)
	{
		for (auto& v : m.second)
		{
			if (v->IsRunning())
				v->Render();
		}
	}
}

void EffectManager::StartEffect(string _effectName, int _posX, int _posY)
{
	Effect* find = FindEffect(_effectName);
	if (find)
	{
		find->StartEffect(_posX, _posY);
	}
}

void EffectManager::StartEffect(string _effectName, int _startPosX, int _startPosY, int _endPosX, int _endPosY)
{
	Effect* find = FindEffect(_effectName);
	if (find)
	{
		find->StartEffect(_startPosX, _startPosY, _endPosX, _endPosY);
	}
}

Effect* EffectManager::FindEffect(string _effectName)
{
	Effect* findEffect = nullptr;
	EffectMapIter iter = mEffectMap.find(_effectName);
	if (iter != mEffectMap.end())
	{
		for (const auto& v : iter->second)
		{
			if (!v->IsRunning())
			{
				findEffect = v;
				break;
			}
		}

		if (!findEffect)
		{
			findEffect = CreateEffectInstance(_effectName);
			mEffectMap[_effectName].push_back(findEffect);
		}
	}
	else
	{
		findEffect = CreateEffectInstance(_effectName);
		mEffectMap[_effectName].push_back(findEffect);
	}

	return findEffect;
}

Effect* EffectManager::CreateEffectInstance(string _effectName)
{
	Effect* newEffect = nullptr;
	if (_effectName == Explosion)
	{
		newEffect = new EffectExplosion(5, 5, 0.3f);
	}
	else if (_effectName == Slash)
	{
		newEffect = new EffectSlash(1, 5, 0.15f);
	}

	return newEffect;
}
