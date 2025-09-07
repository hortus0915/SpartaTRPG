#include "QuizScene.h"
#include "QuizScene.h"
#include "../CommonManagers.h"

void QuizScene::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

int QuizScene::Init()
{
	if (!cursor)
		cursor = new BlinkCursor("QuizScene");

	cursor->SetPos(7, cursorIndex * 2 + 17);
	return 0;
}

void QuizScene::Release()
{
	SAFE_DELETE(cursor);
}
