#pragma once

#include <string>

using namespace std;

#include "../CommonMacros.h"

class ObjectsManager;
class IUpdatable;
class IRenderable;

class iScene
{
protected:
	string sceneName;

	ObjectsManager* objManager;

	bool isParentUpdate;
	bool isParentRender;

public:
	iScene(string _sceneName);
	virtual ~iScene();

	virtual int  Init() = 0;
	virtual void Release() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();

	void AddUpdatable(IUpdatable* _u, int priority = 0);
	void AddRenderable(IRenderable* _r, int priority = 0);

	inline string GetSceneName() { return sceneName; }
	inline void SetSceneName(string _sn) { sceneName = _sn; }

	inline void SetParentUpdate(bool b) { isParentUpdate = b; }
	inline void SetParentRender(bool b) { isParentRender = b; }
	inline bool IsParentUpdate() { return isParentUpdate; }
	inline bool IsParentRender() { return isParentRender; }
};
