#pragma once

#include <map>
#include <string>

using namespace std;

#include "SingletonMacro.h"
#include "SceneInterface.h"

#define SCENE_SUCCESS		100
#define SCENE_FAIL			-1
#define SCENE_FAIL_NOPARENT	-100
#define SCENE_FAIL_NOSCENE	-200

#pragma region SceneNode

typedef map<string, iScene*>			ChildSceneMap;
typedef map<string, iScene*>::iterator	ChildSceneMapIter;

class SceneNode
{
private:
	iScene*	parent;
	iScene*	currentScene;
	ChildSceneMap child;

public:
	SceneNode();
	~SceneNode();

	int  Init();
	void Release();
	void SceneRelease();
	void Update(float deltaTime);
	void Render();

	iScene* AddChild(string _keyName, iScene* _child);

	iScene* FindParent();
	iScene* FindChild(string _keyName);

	int	ChangeParent();
	int ChangeChild(string _keyName);

	bool DeleteChild(string _name);
	bool DeleteAll();

	bool IsCurrentIsParent();
	bool IsCurrentIsChild(string _keyName);

	void AddUpdatable(IUpdatable* _u, int priority = 0);
	void AddRenderable(IRenderable* _r, int priority = 0);

	inline void SetParent(iScene* _p) { parent = currentScene = _p; }
	inline iScene* GetCurrentScene() { return currentScene; }
};

#pragma endregion

#pragma region SceneManager

typedef map<string, SceneNode*>				SceneNodeMap;
typedef map<string, SceneNode*>::iterator	SceneNodeMapIter;

class MainGame;

#include "../TextColors.h"

class SceneManager
{
	SINGLETON(SceneManager, );

private:
	static SceneNode* currentSceneNode;

	SceneNodeMap	  mSceneList;

	MainGame* mainGame;

public:
	// 씬 매니져 Init(활성화된 씬 노드 없애기 (_currentSceneNode = NULL)) 
	void Init(MainGame* _mg);
	// 현재 씬 노드 Init(포함된 차일드 씬 전부 Init)
	int  SceneInit();
	// 키 값에 해당 하는 씬 Init
	int  SceneInit(string _keyName);
	// 현재 활성화 되어있는 씬만 Init(현재 활성화된 씬 노드의 _currentScene만 Init)
	int  CurrentSceneInit();

	// 활성화된 씬 노드 SceneRelease
	void SceneRelease();

	// 현재 활성화된 씬 노드 Update
	// 필요시 부모 씬과 현재 씬 동시에 업데이트 가능(기본 FALSE)
	void Update(float deltaTime);
	// 현재 활성화된 씬 노드 Render
	// 필요시 부모 씬과 현재 씬 동시에 렌더 가능(기본 TRUE)
	void Render();

	// (부모) 씬 이름, 등록할 (부모) 씬
	SceneNode*	AddScene(string _sceneName, iScene* _scene);
	// 부모 씬 이름, 등록할 자식 씬 이름, 등록할 씬
	iScene*		AddChild(string _parent, string _child, iScene* _childScene);

	// 키 값에 해당하는 씬 노드 반환
	SceneNode*	FindScene(string _sceneName);
	// 키 값에 해당하는 씬 노드의 부모 씬 반환
	iScene*		FindParent(string _sceneName);
	// 부모 씬 이름, 차일드 씬 이름
	// 부모 씬 이름으로 등록된 씬 노드에서 차일드 씬 반환
	iScene*		FindChild(string _parent, string _child);

	// 키 값에 해당하는 씬 노드 활성화
	// 이전 씬 노드 SceneRelease
	int 		ChangeScene(string _sceneName);
	// 현재 활성화된 씬 노드에서 키 값에 해당하는 자식 씬 활성화
	int 		ChangeChild(string _childName);
	// 현재 활성화된 씬 노드에서 부모 씬 활성화
	int 		ChangeParent();

	// 현재 활성화된 씬 노드 반환
	inline SceneNode* GetCurrentSceneNode() { return currentSceneNode; }
	// 현재 활성화된 씬 반환
	inline iScene* GetCurrentScene() { return currentSceneNode->GetCurrentScene(); }
	// 현재 노드의 활성화된 씬이 부모 씬인지
	inline bool IsCurrentIsParent() { return currentSceneNode->IsCurrentIsParent(); }
	// 현재 노드의 활성화된 씬이 키 값에 해당하는 차일드 씬인지
	inline bool IsCurrentIsChild(string _childName) { return currentSceneNode->IsCurrentIsChild(_childName); }
	// 현재 씬의 부모 씬 이름 반환
	inline string GetSceneName()
	{
		if (!currentSceneNode)
			return "";

		return currentSceneNode->FindParent()->GetSceneName();
	}

	void RenderToBackbuffer(int _posX, int _posY, int _width, int _height, char** _content, Color _charColor = ORIGINCOLOR, Color _bgColor = BLACK);
};

#pragma endregion
