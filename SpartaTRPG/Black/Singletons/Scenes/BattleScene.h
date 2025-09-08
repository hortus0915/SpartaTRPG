#pragma once

#include "../SceneInterface.h"

#include "../../../Blue/Card/CardDB.h"
#include "../../../Blue/Battle/Board.h"
#include "../../../Blue/Battle/BattleSystem.h"

#include <set>
#include <sstream>

class PlayerInfo;
class EnemyInfoBase;

class BattleSceneHud;
class BattleSceneCardHud;
class BlinkCursor;

enum BattleSequence
{
	None,
	CardSelect,
	CardUse,
	BattleEnd
};

#define BOARD_HEIGHT 13

#define DEFAULT_TRUN_TIME 1.0f

class BattleScene : public iScene
{
private:
	PlayerInfo*		player;
	EnemyInfoBase*	enemy;

	Board::Pos pPos;
	Board::Pos mPos;
	Board::Pos pMoveStartPos;
	Board::Pos mMoveStartPos;
	Board::Pos pMoveEndPos;
	Board::Pos mMoveEndPos;
	Board::Pos pRealPos;
	Board::Pos mRealPos;

	set<int> pdeck;
	set<int> mdeck;

	BattleSystem sys;
	BattleSystem::Side P;
	BattleSystem::Side M;

	const Card* chosen;
	const Card* mChosen;

	int damage;
	bool isGameOver;
	int playerCardIdx;
	int cardsCountInRow;

	string board[BOARD_HEIGHT];
	string cardSelect[3];
	string playerImage[3];
	string enemyImage[3];
	string sequenceStr;
	stringstream sStream;

	BattleSceneHud* battleUi;
	BattleSceneCardHud* cardUi;
	BlinkCursor* cursor;

	float playerCardUseDuration;
	float playerCardUseCurrentTime;
	float enemyCardUseDuration;
	float enemyCardUseCurrentTime;
	bool pActionDone;
	bool mActionDone;
	float playerAttackDamage;
	float enemyAttackDamage;

	BattleSequence currentSequence;

public:
	BattleScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void CalcRealPos(const Board::Pos& pos, Board::Pos& realPos);

	inline void SetBattlers(PlayerInfo* _player, EnemyInfoBase* _enemy) { player = _player; enemy = _enemy; }
};

