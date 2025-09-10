#pragma once

#include "../SceneInterface.h"
#include "../../CommonMacros.h"

#include "../../../Yellow/PoketmonNaming.h"

#define __TOTAL_X__ 10
#define __TOTAL_Y__ 10

class BlinkCursor;

class PoketmonNamingScene : public iScene {
private:
	string screen[MAX_SCREEN_HEIGTH];

	const int ERASE_INDEX = PoketmonNaming::LETTER_COUNT;     // 지우기
	const int DONE_INDEX = PoketmonNaming::LETTER_COUNT + 1; // 완료
	const int TOTAL_COUNT = PoketmonNaming::LETTER_COUNT + 2;
	float duration;
	float elapsedTime;

	PoketmonNaming naming;

	vector<wchar_t> buffer;
	string composed_name;

	bool is_end;

	int cursor_index;
	



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