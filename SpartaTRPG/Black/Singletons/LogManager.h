#pragma once

#include <vector>
#include <string>

#include "../Singletons/SingletonMacro.h"
using namespace std;


class LogManager
{
	SINGLETON(LogManager, )

private:

	vector<string> allLog;

public:
	void Init();

	void Update(float deltaTime);
	void Render();

	void AddLog(string log);
};
