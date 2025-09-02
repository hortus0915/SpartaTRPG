#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::instance = nullptr;

const STRING SoundManager::MPEG = Text("MPEGVideo");
const STRING SoundManager::WAVE = Text("WaveAudio");

void SoundManager::Release()
{
	StopBGM();
	StopAllAmbient();
	ambientMap.clear();
}

void SoundManager::OpenFile(STRING fileName)
{
	MCI_OPEN_PARMS m_mciOpenParms;
	DWORD m_dwDeviceID;
	MCI_OPEN_PARMS mciOpen;
	ZeroMemory(&mciOpen, sizeof(MCI_OPEN_PARMS));

	mciOpen.lpstrElementName = fileName.c_str(); // 파일 경로 입력

	if (fileName.find(Text(".mp3")) != STRING::npos)
	{
		mciOpen.lpstrDeviceType = MPEG.c_str();
	}
	else if (fileName.find(Text(".wav")) != STRING::npos)
	{
		mciOpen.lpstrDeviceType = WAVE.c_str();
	}
	else
	{
		return;
	}

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen);

	bgmID = mciOpen.wDeviceID;
}

void SoundManager::PlayBGM(STRING fileName, int volume)
{
	if (bgmID == -1)
	{
		OpenFile(fileName);
		if (bgmID == -1)
			return;
	}

	MCI_PLAY_PARMS m_mciPlayParms;
	MCI_PLAY_PARMS mciPlay;

	mciSendCommand(bgmID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&m_mciPlayParms);

	if (fileName.find(Text(".mp3")) != STRING::npos)
	{
		SetVolume(volume, bgmID);
	}
	else if (fileName.find(Text(".wav")) != STRING::npos)
	{
		waveOutSetVolume((HWAVEOUT)bgmID, MAKELONG(volume, volume)); // Set volume for .wav files
	}
}

void SoundManager::PlayAmbient(STRING fileName, int volume)
{
	if (ambientMap.find(fileName) != ambientMap.end())
	{
		MCI_PLAY_PARMS mciPlay;
		mciSendCommand(ambientMap[fileName], MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&mciPlay);
		return;
	}

	MCI_OPEN_PARMS mciOpen;
	ZeroMemory(&mciOpen, sizeof(MCI_OPEN_PARMS));

	mciOpen.lpstrElementName = fileName.c_str();
	if (fileName.find(Text(".mp3")) != STRING::npos)
	{
		mciOpen.lpstrDeviceType = MPEG.c_str();
	}
	else if (fileName.find(Text(".wav")) != STRING::npos)
	{
		mciOpen.lpstrDeviceType = WAVE.c_str();
	}
	else
	{
		return;
	}
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen);
	DWORD deviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlayParms;
	mciSendCommand(deviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&mciPlayParms);
	ambientMap[fileName] = deviceID;

	if (fileName.find(Text(".mp3")) != STRING::npos)
	{
		SetVolume(volume, deviceID);
	}
	else if (fileName.find(Text(".wav")) != STRING::npos)
	{
		MMRESULT re = waveOutSetVolume((HWAVEOUT)deviceID, MAKELONG(volume, volume)); // Set volume for .wav files
		if (re != MMSYSERR_NOERROR)
		{
			// Handle error if needed
			cout << "Error setting volume for .wav file: " << re << endl;
		}
		else
		{
			cout << "Volume set successfully for .wav file." << endl;
		}
	}
}

void SoundManager::StopBGM()
{
	if (bgmID != -1)
	{
		mciSendCommand(bgmID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	}
}

void SoundManager::StopAmbient(STRING fileName)
{
	if (ambientMap.find(fileName) == ambientMap.end())
		return;
	DWORD deviceID = ambientMap[fileName];
	mciSendCommand(deviceID, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	ambientMap.erase(fileName);
}

void SoundManager::StopAllAmbient()
{
	for (const auto& elem : ambientMap)
	{
		mciSendCommand(elem.second, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	}
	ambientMap.clear();
}

void SoundManager::SetVolume(int volume, DWORD targetID)
{
	if (targetID == -1)
		return;

	MCI_DGV_SETAUDIO_PARMS mciSetParms;
	ZeroMemory(&mciSetParms, sizeof(MCI_DGV_SETAUDIO_PARMS));

	mciSetParms.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetParms.dwValue = volume;

	MCIERROR err = mciSendCommand(targetID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD_PTR)&mciSetParms);
	if (err != 0)
	{
		// Handle error if needed
		cout << "Error setting volume: " << err << endl;
	}
}

void SoundManager::PlaySfx(STRING fileName, DWORD millisecond)
{
	sndPlaySound(fileName.c_str(), SND_ASYNC | SND_NODEFAULT);

	Sleep(millisecond);
}
