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

int Clamp(const int& min, const int& max, const int& value)
{
	int temp = value;
	if (temp < min) temp = min;
	if (temp > max) temp = max;

	return temp;
}

float Clamp(const float& min, const float& max, const float& value)
{
	float temp = value;
	if (temp < min) temp = min;
	if (temp > max) temp = max;

	return temp;
}
