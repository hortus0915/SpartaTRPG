#pragma once
#include "../Black/BasicInterfaces.h"
#include "TileType.h"

#define MAPPOPUP_WIDTH 81
#define MAPPOPUP_HEIGHT 17

class MapPopup : public IUpdatable, public IRenderable
{
private:
	char** image;
	bool isActive = false;
	bool isSelect = true;

public:
	MapPopup(string _targetSceneName);

	void Update(float deltaTime) override;
	void Render() override;
	void SelectRender();

	void Init();
	void Release();

	inline bool CheckActive() { return isActive; }
	inline bool CheckSelect() { return isSelect; }
	inline void Select(bool _isSelect) { isSelect = _isSelect; }
	int SetActive(TileType tileType);
};

