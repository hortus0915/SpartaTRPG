#include "CommonFuncs.h"


int GetIntRange(int _from, int _to)
{
	return rand() % (_to - _from + 1) + _from;
}

float GetFloatRange(float _from, float _to)
{
	float rnd = (float)rand() / (float)RAND_MAX;

	return rnd * (_to - _from) + _from;
}
