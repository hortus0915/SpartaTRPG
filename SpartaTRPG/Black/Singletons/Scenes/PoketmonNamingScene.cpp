#include "PoketmonNamingScene.h"
#include "../CommonManagers.h"

#include <string>
#include <iostream>

string PoketmonNamingScene::GetLetters()
{
	return composed_name;
}


void PoketmonNamingScene::InputLetters(char32_t c)
{
	letters.push_back(c);
}

void PoketmonNamingScene::DeleteLetters()
{
	letters.pop_back();
}

void PoketmonNamingScene::Update(float deltaTime)
{
}

int PoketmonNamingScene::Init()
{
	composed_name = "";
	letters = { L'そ', L'び', L'し', L'せ', L'ぱ', L'い', L'び', L'い', L'じ', L'た', L'ず', L'ぬ', L'ぉ', L'ぇ', L'で', L'し' };
	composed_name = naming.Compose(letters);
	return 0;
}

void PoketmonNamingScene::Release()
{
}

void PoketmonNamingScene::Render()
{
	SCENEMANAGER->RenderToBackbuffer(1, 1, 1, 1, composed_name, 1, 0);
}
