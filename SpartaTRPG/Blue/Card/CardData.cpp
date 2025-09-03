#include "CardData.h"

using namespace std;

Card::Card(int _idx, const string& _name, CardType _type, u16 _range,
	float _damageRate, int _staminaCost)
	: idx(_idx), name(_name), type(_type), range(_range),
	damageRate(_damageRate), staminaCost(_staminaCost) {
}

void Card::PrintInfo() const
{
	cout << "[Idx:" << idx;

	if(type != MOVE)	cout << " | 이름:" << name;

	if (staminaCost > 0) cout << " | 마나:" << staminaCost;

	switch (type)
	{
	case MOVE:
		PrintMoveRange();
		break;
	case ATTACK: 
		PrintRange();
		break;
	case SHIELD: 
		cout << "| 타입:방어 " << (int)(damageRate * 100)<<"%]\n";
		break;
	case HEAL:  
		PrintHealInfo();
		break;
	}


}

void Card::PrintRange() const
{
	cout << "| 타입:공격]\n";
	cout << " 공격범위" << " | 배율 :" << damageRate << "\n";

	for (int i = 0; i < 9; i++)
	{
		if (range & (1u << i))
			cout << "[X]";
		else
			cout << "[ ]";

		if (i % 3 == 2) cout << "\n"; // 줄바꿈 (3칸마다)
	}
}

void Card::PrintMoveRange() const
{

	const char* arrows[9] =
	{
		 "↖","↑","↗",
		 "←"," ","→",
		 "↙","↓","↘"
	};

	int dirIdx = 4;
	for (int i = 0; i < 9; ++i) {
		if (range & (1u << i)) { dirIdx = i; break; }
	}


	string directStep = string(arrows[dirIdx]) + " " + to_string((int)damageRate) + "칸";
	cout << " | 타입:이동" << directStep<< "]\n";

}

void Card::PrintHealInfo() const
{  
	// - damageRate > 0  => 체력 +damageRate
	// - staminaCost < 0 => 마나 +(-staminaCost)
	bool hpHeal = (damageRate > 0.0f);
	bool spHeal = (staminaCost < 0);

	cout << " | 타입: 힐 | 효과:";

	if (hpHeal) cout << " 체력+" << (int)(damageRate);
	if (spHeal)cout << " 마나+" << (-staminaCost);
	

	cout << "]\n";
}
