#pragma once

#include "Singletons/SceneManager.h"

#include <string>

using namespace std;

class IUpdatable
{
public:
	IUpdatable(string _targetSceneName);

	virtual void Update(float deltaTime) = 0;
};

class IRenderable
{
public:
	IRenderable(string _targetSceneName);

	virtual void Render() = 0;
};
