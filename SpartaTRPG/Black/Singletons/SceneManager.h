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
	// �� �Ŵ��� Init(Ȱ��ȭ�� �� ��� ���ֱ� (_currentSceneNode = NULL)) 
	void Init(MainGame* _mg);
	// ���� �� ��� Init(���Ե� ���ϵ� �� ���� Init)
	int  SceneInit();
	// Ű ���� �ش� �ϴ� �� Init
	int  SceneInit(string _keyName);
	// ���� Ȱ��ȭ �Ǿ��ִ� ���� Init(���� Ȱ��ȭ�� �� ����� _currentScene�� Init)
	int  CurrentSceneInit();

	// Ȱ��ȭ�� �� ��� SceneRelease
	void SceneRelease();

	// ���� Ȱ��ȭ�� �� ��� Update
	// �ʿ�� �θ� ���� ���� �� ���ÿ� ������Ʈ ����(�⺻ FALSE)
	void Update(float deltaTime);
	// ���� Ȱ��ȭ�� �� ��� Render
	// �ʿ�� �θ� ���� ���� �� ���ÿ� ���� ����(�⺻ TRUE)
	void Render();

	// (�θ�) �� �̸�, ����� (�θ�) ��
	SceneNode*	AddScene(string _sceneName, iScene* _scene);
	// �θ� �� �̸�, ����� �ڽ� �� �̸�, ����� ��
	iScene*		AddChild(string _parent, string _child, iScene* _childScene);

	// Ű ���� �ش��ϴ� �� ��� ��ȯ
	SceneNode*	FindScene(string _sceneName);
	// Ű ���� �ش��ϴ� �� ����� �θ� �� ��ȯ
	iScene*		FindParent(string _sceneName);
	// �θ� �� �̸�, ���ϵ� �� �̸�
	// �θ� �� �̸����� ��ϵ� �� ��忡�� ���ϵ� �� ��ȯ
	iScene*		FindChild(string _parent, string _child);

	// Ű ���� �ش��ϴ� �� ��� Ȱ��ȭ
	// ���� �� ��� SceneRelease
	int 		ChangeScene(string _sceneName);
	// ���� Ȱ��ȭ�� �� ��忡�� Ű ���� �ش��ϴ� �ڽ� �� Ȱ��ȭ
	int 		ChangeChild(string _childName);
	// ���� Ȱ��ȭ�� �� ��忡�� �θ� �� Ȱ��ȭ
	int 		ChangeParent();

	// ���� Ȱ��ȭ�� �� ��� ��ȯ
	inline SceneNode* GetCurrentSceneNode() { return currentSceneNode; }
	// ���� Ȱ��ȭ�� �� ��ȯ
	inline iScene* GetCurrentScene() { return currentSceneNode->GetCurrentScene(); }
	// ���� ����� Ȱ��ȭ�� ���� �θ� ������
	inline bool IsCurrentIsParent() { return currentSceneNode->IsCurrentIsParent(); }
	// ���� ����� Ȱ��ȭ�� ���� Ű ���� �ش��ϴ� ���ϵ� ������
	inline bool IsCurrentIsChild(string _childName) { return currentSceneNode->IsCurrentIsChild(_childName); }
	// ���� ���� �θ� �� �̸� ��ȯ
	inline string GetSceneName()
	{
		if (!currentSceneNode)
			return "";

		return currentSceneNode->FindParent()->GetSceneName();
	}

	void RenderToBackbuffer(int _posX, int _posY, int _width, int _height, char** _content, Color _charColor = ORIGINCOLOR, Color _bgColor = BLACK);
};

#pragma endregion
