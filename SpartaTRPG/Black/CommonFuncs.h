#pragma once

#include <cstdlib>

int GetIntRange(int _from, int _to);
float GetFloatRange(float _from, float _to);

int Clamp(const int& min, const int& max, const int& value);
float Clamp(const float& min, const float& max, const float& value);

int Lerp(const int& start, const int& end, const float& ratio);
float Lerp(const float& start, const float& end, const float& ratio);
