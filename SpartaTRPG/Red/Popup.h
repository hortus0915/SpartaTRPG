#pragma once
#include "../Black/BasicInterfaces.h"
#include "TileType.h"

#define MAPPOPUP_WIDTH 81
#define MAPPOPUP_HEIGHT 17

class Popup : public IUpdatable, public IRenderable
{
protected:
	char** image;
	bool isActive = false;

public:
	Popup(string _targetSceneName);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void Init();
	virtual void Release();

	inline bool CheckActive() { return isActive; }
	void SetActive(bool active = true);
};

