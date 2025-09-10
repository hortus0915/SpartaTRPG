#pragma once

#include "../SceneInterface.h"
#include "../../CommonMacros.h"

#include "../../../Yellow/PoketmonNaming.h"

class BlinkCursor;

class PoketmonNamingScene : public iScene {
private:
	string screen[MAX_SCREEN_HEIGTH];

	PoketmonNaming naming;

	vector<wchar_t> letters;
	string composed_name;
	int effectCount;

	bool correct;

	bool is_end;

	BlinkCursor* cursor;
	



public:
	PoketmonNamingScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	string GetLetters();
	void InputLetters(char32_t c);
	void DeleteLetters();


	void Update(float deltaTime) override;
	int Init() override;
	void Release() override;
	void Render() override;
};