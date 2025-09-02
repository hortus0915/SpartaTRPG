#pragma once

#include "SingletonMacro.h"

#include <Windows.h>
#pragma comment (lib, "winmm.lib")

#include <Digitalv.h>

#include <string>
#include <map>

using namespace std;

#ifdef _UNICODE
typedef wstring STRING;
#define Text(txt) L##txt
#else
typedef string STRING;
#define Text(txt) ##txt
#endif

class SoundManager
{
	SINGLETON(SoundManager,: bgmID(-1))

private:
	static const STRING MPEG;
	static const STRING WAVE;

	DWORD bgmID;
	map<STRING, DWORD> ambientMap;

	void OpenFile(STRING fileName);

public:
	void PlayBGM(STRING fileName, int volume = 50);
	void PlayAmbient(STRING fileName, int volume = 50);

	void StopBGM();
	void StopAmbient(STRING fileName);
	void StopAllAmbient();

	void SetVolume(int volume, DWORD targetID);

	void PlaySfx(STRING fileName, DWORD millisecond = 0);
};
