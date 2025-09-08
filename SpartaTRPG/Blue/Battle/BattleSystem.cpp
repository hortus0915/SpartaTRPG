#include <cstdlib> 
#include <algorithm> 
#include <sstream>
#include "BattleSystem.h"

void BattleSystem::BeginVSP(Side& _target)
{
	_target.chr->vSPCost = _target.chr->GetCurSP();
}

bool BattleSystem::TryPickWithVSP(Side& _target, const Card* _card)
{
	if (!_card) return;
	int cost = _card->GetStaminaCost();

	return (_target.chr->TryApplyVSPCost(cost));
}

void BattleSystem::MovoToCharacter(Side& _target)
{
	_target.chr->AddSP(-_target.card->GetStaminaCost());
	int steps = _target.card->GetDamageRate();

	Board::Pos& pos = *_target.pos;

	u16 mask = _target.card->GetRange();

	const u16 RIGHT = (DIR_R | DIR_UR | DIR_DR);
	const u16 LEFT = (DIR_L | DIR_UL | DIR_DL);
	const u16 DOWN = (DIR_D | DIR_DL | DIR_DR);
	const u16 UP = (DIR_U | DIR_UL | DIR_UR);

	int dx = ((mask & RIGHT) ? 1 : 0) - ((mask & LEFT) ? 1 : 0);
	int dy = ((mask & DOWN) ? 1 : 0) - ((mask & UP) ? 1 : 0);

	int newX = pos.x + dx * steps;
	int newY = pos.y + dy * steps;

	if (newX < 0) newX = 0;
	if (newX >= Board::W) newX = Board::W - 1;

	if (newY < 0) newY = 0;
	if (newY >= Board::H) newY = Board::H - 1;

	pos.x = newX;
	pos.y = newY;

}

int BattleSystem::AttackToCharacter(Side& _attacker, Side& _target , vector<Board::Pos>& outRange)
{
	const int dx = _target.pos->x - _attacker.pos->x;
	const int dy = _target.pos->y - _attacker.pos->y;

	const int bit = (dy + 1) * 3 + (dx + 1);
	const u16 mask = _attacker.card->GetRange();

	_attacker.chr->AddSP(-_attacker.card->GetStaminaCost());

	outRange.clear();

	for (int dy = -1; dy <= 1; ++dy) {
		for (int dx = -1; dx <= 1; ++dx) {
			int bit = (dy + 1) * 3 + (dx + 1);
			if (mask & (1u << bit)) {
				int nx = _attacker.pos->x + dx;
				int ny = _attacker.pos->y + dy;

				if (nx < 0 || nx >= Board::W) continue;
				if (ny < 0 || ny >= Board::H) continue;

				outRange.push_back({ nx, ny });
			}
		}
	}


	if (dx < -1 || dx > 1 || dy < -1 || dy > 1) return 0;


	if ((mask & ((1u) << bit)) == 0) return 0;

	const float baseAtk = _attacker.chr->GetBaseDamage();
	float dmgF = baseAtk * _attacker.card->GetDamageRate();
	if (_attacker.chr->IsCritical()) 
	{
		cout << " 크리티컬! \n";
		dmgF = _attacker.chr->CalcCriDamage(dmgF);
	}

	return (int)dmgF;
}

void BattleSystem::ShieldToCharacter(Side& _self, Side& _attacker, float _attackDamage, float& _outAttackDamage, float& _outCounterDamage)
{
	float shieldRate = _self.card->GetDamageRate();
	int shieldDamage = 0;

	_self.chr->AddSP(-_self.card->GetStaminaCost());

	if (_self.chr->IsCounter())
	{
		//cout << " 카운터 발동! \n";
		_outCounterDamage = _attackDamage * 2.0f;
		_outAttackDamage = 0;
	}
	else
	{	
		int shieldDamage = _attackDamage * (1.0f - shieldRate);
	//	cout << " 방어 후 데미지 : " << shieldDamage << "\n";
		_outAttackDamage = shieldDamage;
	}

}

int BattleSystem::HealToCharacter(Side& _self)
{
	const int healAmount = (int)_self.card->GetDamageRate();
	const int ManaAmount = _self.card->GetStaminaCost();

	if (healAmount > 0) _self.chr->AddHP(healAmount);
	
	_self.chr->AddSP(-ManaAmount);


	return 0;
}

int BattleSystem::HealToCharacter(Side& _self, stringstream& sStream)
{
	const int healAmount = (int)_self.card->GetDamageRate();
	const int ManaAmount = _self.card->GetStaminaCost();

	if (healAmount > 0) _self.chr->AddHP(healAmount);

	 _self.chr->AddSP(-ManaAmount);
	 
	//test print
	if (healAmount > 0) sStream << " 체력 + " << healAmount;
	if (ManaAmount < 0) sStream << " 마나 + " << ManaAmount;
	std::cout << "\n";


	return 0;
}
