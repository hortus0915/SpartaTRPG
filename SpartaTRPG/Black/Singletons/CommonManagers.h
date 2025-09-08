#pragma once

#include "SceneManager.h"
#include "SoundManager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "EffectManager.h"
#include "PopupManager.h"
#include "UserManager.h"

#define SCENEMANAGER	SceneManager::GetInstance()
#define SOUNDMANAGER	SoundManager::GetInstance()
#define KEYMANAGER		KeyManager::GetInstance()
#define TIMEMANAGER		TimeManager::GetInstance()
#define EFFECTMANAGER	EffectManager::GetInstance()
#define POPUPMANAGER	PopupManager::GetInstance()
#define USERMANAGER		UserManager::GetInstance()
