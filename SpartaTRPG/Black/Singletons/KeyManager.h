#pragma once
#include <bitset>
#include <Windows.h>

using namespace std;

#include "SingletonMacro.h"

#define KEYMAX 256

class KeyManager
{
	SINGLETON(KeyManager, )

private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	void Init();

	bool IsOnceKeyDown(int key);
	bool IsOnceKeyUp(int key);
	bool IsStayKeyDown(int key);
	bool IsToggleKey(int key);

	bitset<KEYMAX> GetKeyUp() { return _keyUp; }
	bitset<KEYMAX> GetKeyDown() { return _keyDown; }

	void SetKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { _keyUp.set(key, state); }
};
