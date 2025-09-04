#include "SceneManager.h"

#include "../CommonMacros.h"

#include "../MainGame.h"

#pragma region SceneNode

SceneNode::SceneNode()
	: parent(nullptr)
	, currentScene(nullptr)
{
}

SceneNode::~SceneNode()
{
}

int SceneNode::Init()
{
	if (!parent) return SCENE_FAIL_NOPARENT;

	for (const auto& k : child)
	{
		if (!k.second) continue;

		k.second->Init();
	}

	return this->ChangeParent();
}

void SceneNode::Release()
{
	SAFE_RELEASE_DELETE(parent);
	this->DeleteAll();
}

void SceneNode::SceneRelease()
{
	parent->Release();

	ChildSceneMapIter iter = child.begin();

	for (; iter != child.end(); ++iter)
	{
		if (iter->second)
			iter->second->Release();
	}
}

void SceneNode::Update(float deltaTime)
{
	if (!currentScene) return;
	if (this->IsCurrentIsParent())
		parent->Update(deltaTime);
	else
	{
		if (currentScene->IsParentUpdate())
			parent->Update(deltaTime);

		currentScene->Update(deltaTime);
	}
}

void SceneNode::Render()
{
	if (!currentScene) return;

	if (this->IsCurrentIsParent())
		parent->Render();
	else
	{
		if (currentScene->IsParentRender())
			parent->Render();

		currentScene->Render();
	}
}

iScene * SceneNode::AddChild(string _keyName, iScene * _child)
{
	if (!_child) return nullptr;

	iScene* c = this->FindChild(_keyName);

	if (c)
	{
		SAFE_RELEASE_DELETE(_child);
		c->SetSceneName(_keyName);
		return c;
	}

	_child->SetSceneName(_keyName);
	child.insert(make_pair(_keyName, _child));

	return _child;
}

iScene* SceneNode::FindParent()
{
	return parent;
}

iScene* SceneNode::FindChild(string _keyName)
{
	ChildSceneMapIter key = child.find(_keyName);

	if (key != child.end())
		return key->second;

	return nullptr;
}

int SceneNode::ChangeParent()
{
	currentScene = parent;

	if (!currentScene ||
		!this->IsCurrentIsParent())
		return SCENE_FAIL;

	return SCENE_SUCCESS;
}

int SceneNode::ChangeChild(string _keyName)
{
	iScene* next = this->FindChild(_keyName);

	if (!next)
		return SCENE_FAIL_NOSCENE;

	currentScene = next;

	return SCENE_SUCCESS;
}

bool SceneNode::DeleteChild(string _name)
{
	ChildSceneMapIter key = child.find(_name);

	if (key != child.end())
	{
		SAFE_RELEASE_DELETE(key->second);
		child.erase(key);
		return true;
	}

	return false;
}

bool SceneNode::DeleteAll()
{
	ChildSceneMapIter key = child.begin();

	for (; key != child.end();)
	{
		if (key->second)
		{
			SAFE_RELEASE_DELETE(key->second);
			key = child.erase(key);
		}
		else ++key;
	}

	child.clear();

	return true;
}

bool SceneNode::IsCurrentIsParent()
{
	return (currentScene == parent);
}

bool SceneNode::IsCurrentIsChild(string _keyName)
{
	return (currentScene == this->FindChild(_keyName));
}

void SceneNode::AddUpdatable(IUpdatable* _u, int priority)
{
	if (parent)
	{
		parent->AddUpdatable(_u);
	}
}

void SceneNode::AddRenderable(IRenderable* _r, int priority)
{
	if (parent)
	{
		parent->AddRenderable(_r);
	}
}

#pragma endregion


#pragma region SceneManager

SceneManager* SceneManager::instance = nullptr;
SceneNode* SceneManager::currentSceneNode = nullptr;

void SceneManager::Init(MainGame* _mg)
{
	currentSceneNode = nullptr;

	mainGame = _mg;
}

int SceneManager::SceneInit()
{
	if (!currentSceneNode)
		return SCENE_FAIL;

	return currentSceneNode->Init();
}

int SceneManager::SceneInit(string _keyName)
{
	SceneNode* s = this->FindScene(_keyName);

	if (!s)
		return SCENE_FAIL_NOSCENE;

	return s->Init();
}

int SceneManager::CurrentSceneInit()
{
	if (currentSceneNode)
	{
		if (!(currentSceneNode->GetCurrentScene()))
			return SCENE_FAIL_NOSCENE;

		return currentSceneNode->GetCurrentScene()->Init();
	}

	return SCENE_FAIL_NOSCENE;
}

void SceneManager::Release()
{
	SceneNodeMapIter key = mSceneList.begin();

	for (; key != mSceneList.end();)
	{
		if (key->second)
		{
			SAFE_RELEASE_DELETE(key->second);
			key = mSceneList.erase(key);
		}
		else ++key;
	}

	mSceneList.clear();
}

void SceneManager::SceneRelease()
{
	if (currentSceneNode)
		currentSceneNode->SceneRelease();
}

void SceneManager::Update(float deltaTime)
{
	if (currentSceneNode)
		currentSceneNode->Update(deltaTime);
}

void SceneManager::Render()
{
	if (currentSceneNode)
		currentSceneNode->Render();
}

SceneNode * SceneManager::AddScene(string _sceneName, iScene * _scene)
{
	SceneNode* s = this->FindScene(_sceneName);

	if (s)
	{
		SAFE_RELEASE_DELETE(_scene);
		return s;
	}

	s = new SceneNode;
	s->SetParent(_scene);

	_scene->SetSceneName(_sceneName);
	mSceneList.insert(make_pair(_sceneName, s));

	return s;
}

iScene * SceneManager::AddChild(string _parent, string _child, iScene * _childScene)
{
	SceneNode* s = this->FindScene(_parent);

	if (s)
		return s->AddChild(_child, _childScene);

	return nullptr;
}

SceneNode* SceneManager::FindScene(string _sceneName)
{
	SceneNodeMapIter key = mSceneList.find(_sceneName);

	if (key != mSceneList.end())
		return key->second;

	return nullptr;
}

iScene* SceneManager::FindParent(string _sceneName)
{
	SceneNode* s = this->FindScene(_sceneName);

	if (s)
		return s->FindParent();

	return nullptr;
}

iScene* SceneManager::FindChild(string _parent, string _child)
{
	SceneNode* s = this->FindScene(_parent);

	if (s)
		return s->FindChild(_child);

	return nullptr;
}

int SceneManager::ChangeScene(string _sceneName)
{
	SceneNode* next = this->FindScene(_sceneName);

	if (!next)
		return SCENE_FAIL_NOSCENE;

	this->SceneRelease();
	currentSceneNode = next;

	prevSceneStack.push(_sceneName);

	return SCENE_SUCCESS;
}

int SceneManager::ChangeChild(string _childName)
{
	return currentSceneNode->ChangeChild(_childName);
}

int SceneManager::ChangeParent()
{
	return currentSceneNode->ChangeParent();
}

int SceneManager::ChaneToPrevScene()
{
	prevSceneStack.pop();
	SceneNode* next = this->FindScene(prevSceneStack.top());

	if (!next)
		return SCENE_FAIL_NOSCENE;

	this->SceneRelease();
	currentSceneNode = next;

	return SCENE_SUCCESS;
}

void SceneManager::RenderToBackbuffer(int _posX, int _posY, int _width, int _height, char** _content, Color _charColor, Color _bgColor)
{
	if (!mainGame || !_content) return;

	mainGame->CopyToBackbuffer(_posX, _posY, _width, _height, _content, _charColor, _bgColor);
}

void SceneManager::RenderToBackbuffer(int _posX, int _posY, int _width, int _height, string* _content, Color _charColor, Color _bgColor)
{
	if (!mainGame || !_content) return;

	mainGame->CopyToBackbuffer(_posX, _posY, _width, _height, _content, _charColor, _bgColor);
}

#pragma endregion
