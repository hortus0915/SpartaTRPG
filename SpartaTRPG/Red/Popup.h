#pragma once
#include "../Black/BasicInterfaces.h"
#include "TileType.h"
#include <type_traits>
#include <vector>

#define MAXRANGTH 5

class Popup
{
public:

	using ActiveCallback = void(*)(int, void*);
	void SetPopupActiveCallback(ActiveCallback cb, void* user);

protected:
	char** image;
	bool isActive = false;

	int selectValue = 0;

	vector<string>* customString;
	int customStringIndex = 0;

	int leftPadding = 0;
	int rightPadding = 0;
	int upPadding = 0;
	int downPadding = 0;

	void InvokeActive(int v) {
		if (active_cb_) active_cb_(v, active_user_);
	}

public:
	Popup();

	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void Init();
	virtual void Release();

	ActiveCallback active_cb_{ nullptr };
	void* active_user_{ nullptr };

	inline bool CheckActive() { return isActive; }
	void SetActive(bool active = true);

	void RenderingCustomString();
	void SetCustonStrings(vector<string>* _customString);
	void SetCustomStringPadding(int _leftPadding = 0, int _rightPadding = 0, int _upPadding = 0, int _downPadding = 0);
};

