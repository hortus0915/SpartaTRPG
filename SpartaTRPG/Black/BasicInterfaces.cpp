#include "BasicInterfaces.h"

#include "Singletons/CommonManagers.h"

IUpdatable::IUpdatable(string _targetSceneName)
{
	SceneNode* node = SCENEMANAGER->FindScene(_targetSceneName);
	if (node)
	{
		node->AddUpdatable(this);
	}
}

IRenderable::IRenderable(string _targetSceneName)
{
	SceneNode* node = SCENEMANAGER->FindScene(_targetSceneName);
	if (node)
	{
		node->AddRenderable(this);
	}
}
