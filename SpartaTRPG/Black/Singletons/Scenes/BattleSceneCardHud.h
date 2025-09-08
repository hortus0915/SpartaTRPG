#pragma once

#include <sstream>

using namespace std;

#include "../../BasicInterfaces.h"
#include "../../TextColors.h"

class Card;

#define TITLE	image[0]
#define COST	image[1]
#define TYPE	image[2]
#define	DESC	image[3]

class BattleSceneCardHud : public IRenderable
{
private:
	int posX;
	int posY;

	static string upper;
	static string lower;

	string image[4];
	string attackRange[9];


	const Card* currentCard;

	stringstream sStream;

public:
	BattleSceneCardHud(string _sn) : IRenderable(_sn), currentCard(nullptr), posX(0), posY(0) { }

	void Init(int _posX, int _posY);
	void Release();

	// IRenderable을(를) 통해 상속됨
	void Render() override;

	inline void SetCard(const Card* _card) { currentCard = _card; }
};

