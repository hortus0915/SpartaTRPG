#include "../Black/ObjectsManager.h"

#include "../Black/CommonMacros.h"
#include "BasicInterfaces.h"

void ObjectsManager::Update(float deltaTime)
{
	for (const auto& m : _updateList)
	{
		for (auto& v : m.second)
		{
			if (v)
				v->Update(deltaTime);
		}
	}
}

void ObjectsManager::Render()
{
	for (const auto& m : _renderList)
	{
		for (auto& v : m.second)
		{
			if (v)
				v->Render();
		}
	}
}

void ObjectsManager::Release()
{
	for (auto& m : _updateList)
	{
		for (auto& v : m.second)
		{
			SAFE_DELETE(v)
		}
	}

	for (auto& m : _renderList)
	{
		for (auto& v : m.second)
		{
			SAFE_DELETE(v)
		}
	}
}

void ObjectsManager::AddUpdatable(IUpdatable* u, int priority)
{
	_updateList[priority].push_back(u);
}

void ObjectsManager::AddRenderable(IRenderable* r, int priority)
{
	_renderList[priority].push_back(r);
}
