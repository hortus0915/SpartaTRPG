#include "SceneInterface.h"

#include "../ObjectsManager.h"
#include "../BasicInterfaces.h"

iScene::iScene(string _sceneName)
	: sceneName(_sceneName)
	, isParentUpdate(false)
	, isParentRender(true)
	, objManager(nullptr)
{
	objManager = new ObjectsManager;
}
iScene::~iScene()
{
	SAFE_RELEASE_DELETE(objManager)
}

void iScene::Update(float deltaTime)
{
	if (objManager)
		objManager->Update(deltaTime);
}

void iScene::Render()
{
	if (objManager)
		objManager->Render();
}

void iScene::AddUpdatable(IUpdatable* _u, int priority)
{
	if (objManager)
		objManager->AddUpdatable(_u, priority);
}

void iScene::AddRenderable(IRenderable* _r, int priority)
{
	if (objManager)
		objManager->AddRenderable(_r, priority);
}
