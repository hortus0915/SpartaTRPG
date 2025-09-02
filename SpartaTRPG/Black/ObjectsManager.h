#pragma once

#include <vector>
#include <map>

using namespace std;

class IUpdatable;
class IRenderable;

class ObjectsManager
{
private:
	map<int, vector<IUpdatable*>>  _updateList;
	map<int, vector<IRenderable*>> _renderList;

public:
	void Update(float deltaTime);
	void Render();
	void Release();

	void AddUpdatable(IUpdatable* u, int priority);
	void AddRenderable(IRenderable* r, int priority);
};
