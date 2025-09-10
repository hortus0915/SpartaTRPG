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
	tutorial,
	CardSelect,
	CardUse,
	Victory,   
	Defeat,    
	Draw,
	PopupSequence,
	BattleEnd
	
};

enum class SubPhase
{
	First,
	Second
};

#define BOARD_HEIGHT 13

#define DEFAULT_TRUN_TIME 1.0f

class BattleScene : public iScene
{
private:
	PlayerInfo* player;
	EnemyInfoBase* enemy;

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

	bool pShieldUp = false;
	bool mShieldUp = false;

	int damage;
	bool isGameOver;
	int playerCardIdx;
	int currentActionCount;
	int cardsCountInRow;

	string board[BOARD_HEIGHT];
	string* cardSelect;
	int		cardsNum;
	string playerImage[3];
	string enemyImage[3];
	string sequenceStr;
	string lastActionStr;
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

	SubPhase subPhase = SubPhase::First;
	bool playerFirstThisSubturn = true;

	float actionStartGap = 1.0f;  
	float actionStartTimer = 0.0f;
	bool  waitingToStartAction = true;  
	bool  isFirstActionThisRound = false; 

	static bool sTutorialShown;
	void ShowBattleTutorialOnce();

	bool isBossStroryPopup = false;
public:
	BattleScene(string _sceneName) : iScene(_sceneName), cardSelect(nullptr) {}

	// iScene을(를) 통해 상속됨
	int Init() override;
	void Release() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void CalcRealPos(const Board::Pos& pos, Board::Pos& realPos);
	void SortCards(vector<const Card*>& selected);

	void CreateEffect(const int& cardId, const vector<Board::Pos>& pos, const Board::Pos& originPos);

	void DoAction(BattleSystem::Side& _actor, BattleSystem::Side& _target, std::string& _outStr);

	void ResultVictoryPopupActive(int selected);
	void ResultDrawPopupActive(int selected);
	void ResultDefeatPopupActive(int selected);

	void GameEnd(int _selected);
	void BossFail(int _selected);

	inline void SetBattlers(PlayerInfo* _player, EnemyInfoBase* _enemy) { player = _player; enemy = _enemy; }
};

