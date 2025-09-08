#pragma once

#include "../SceneInterface.h"

#include "../../../Blue/Card/CardDB.h"
#include "../../../Blue/Battle/Board.h"
#include "../../../Blue/Battle/BattleSystem.h"

#include <set>
#include <sstream>
#include <vector>

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

	int cardSelectCount;
	int currentSelectCount;
	vector<const Card*> playerSelectedCard;
	vector<int> playerSelectedIdx;
	vector<const Card*> enemySelectedCard;

	BattleSystem sys;
	BattleSystem::Side P;
	BattleSystem::Side M;

	const Card* chosen;
	const Card* mChosen;

	int damage;
	bool isGameOver;
	int playerCardIdx;
	int currentActionCount;
	int cardsCountInRow;

	string board[BOARD_HEIGHT];
	string cardSelect[3];
	string playerImage[3];
	string enemyImage[3];
	string sequenceStr;
	stringstream sStream;

	BattleSceneHud* battleUi;
	BattleSceneCardHud* cardUi[3];
	BlinkCursor* cursor;

	float playerCardUseDuration;
	float playerCardUseCurrentTime;
	bool pActionDone;
	bool mActionDone;
	float playerAttackDamage;
	float playerAttackRealDamage;
	float enemyAttackDamage;
	float enemyAttackRealDamage;

	BattleSequence currentSequence;

public:
	BattleScene(string _sceneName) : iScene(_sceneName) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void CalcRealPos(const Board::Pos& pos, Board::Pos& realPos);
	void SortCards(vector<const Card*>& selected);

	void CreateEffect(const int& cardId, const vector<Board::Pos>& pos, const Board::Pos& originPos);

	inline void SetBattlers(PlayerInfo* _player, EnemyInfoBase* _enemy) { player = _player; enemy = _enemy; }
};

