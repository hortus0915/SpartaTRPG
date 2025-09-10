#include "TestScene2.h"

#include "MapMovePlayer.h"
#include "CommonMacros.h"

#include "TextColors.h"

int TestScene2::Init()
{
	player = new MapMovePlayer(sceneName);
	player->Init(1, 1, 3, 3, GREEN, CYAN);
	string test_word = "hello world";

	return 0;
}

void TestScene2::Release()
{
	SAFE_DELETE(player);
}

void TestScene2::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

void TestScene2::Render()
{
	__super::Render();
}
