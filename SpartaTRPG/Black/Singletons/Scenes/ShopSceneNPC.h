#pragma once

#include "../../BasicInterfaces.h"
#include "../../TextColors.h"

enum ShopNPCState
{
	Idle,
	Delight
};

class ShopSceneNPC : public IUpdatable, public IRenderable
{
private:
	int posX;
	int posY;

	float delightDuration;
	float delightCurrentTime;

	ShopNPCState currentState;

	string image[10];
	string eye[2];

public:
	ShopSceneNPC(string _sn) : IUpdatable(_sn), IRenderable(_sn), currentState(Idle){ }

	void Init(int _posX, int _posY);
	void Release();

	// IUpdatable을(를) 통해 상속됨
	void Update(float deltaTime) override;


	// IRenderable을(를) 통해 상속됨
	void Render() override;

	void DelightTrigger();

};

