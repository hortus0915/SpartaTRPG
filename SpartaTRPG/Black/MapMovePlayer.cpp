#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"
#include "../Red/SelectPopup.h"
#include "../Red/MapData.h"


MapMovePlayer::MapMovePlayer(string _sn, MapData* _mapData) : iMapMovable(_sn, _mapData)
{
	runSoundDuration = RUNSOUNDENDDURATION;
}

void MapMovePlayer::Init(Color _characterColor, Color _bgColor)
{
	__super::Init(_characterColor, _bgColor);
}

void MapMovePlayer::Update(float deltaTime)
{
	if(POPUPMANAGER->CheckPopupActive() == false)
		MapInput(deltaTime);

	if (!activeCheck)
	{
		CheckActive();
		activeCheck = true;
	}

	if (runSoundDuration < RUNSOUNDENDDURATION)
	{
		runSoundDuration += deltaTime;
	}
	else
	{
		SOUNDMANAGER->StopAmbient(Text("RunSound.wav"));
	}
}

void MapMovePlayer::Render()
{
	__super::Render();
}

void MapMovePlayer::Release()
{
	__super::Release();
}

void MapMovePlayer::MapInput(float deltaTime)
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		MoveTo(-1, 0); 
		CheckRunSoundPlay();
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		MoveTo(1, 0);
		CheckRunSoundPlay();
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		MoveTo(0, -1);
		CheckRunSoundPlay();
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		MoveTo(0, 1);
		CheckRunSoundPlay();
	}

}

void MapMovePlayer::ObjectActive(TileType _tileType)
{
	switch (_tileType)
	{
	case Exit:
		mapData->CreateMap(MapType::Dungeon);
		break;
	case Box:
	case BoxActive:
		//아이템 획득
		mapData->ObjectReset(posX, posY);
		break;
	case Key:
		mapData->GetDungeonKey();
		mapData->ObjectReset(posX, posY);
		break;
	case DungeonIn:
		mapData->CreateMap(MapType::Dungeon);
		break;
	case Monster:
	case MonsterActiveRange:
		//전투 씬으로 이동
		mapData->ObjectReset(posX, posY);
		break;
	default:
		break;
	}
}

void MapMovePlayer::CheckActive()
{
	auto mapInfo = mapData->GetMapInfo(posX, posY);
	
	switch (mapInfo)
	{
	case Empty:
	case Wall:
	case Monster:
	case MonsterActiveRange:
		POPUPMANAGER->PopupActiveOff();
		break;
	case Box:
	case BoxActive:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("박스를 열겠습니까?");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::SELECTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			0
		);
	}
	break;
	case Key:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("열쇠를 발견했다!");
		initString->push_back("열쇠를 줍겠습니까?");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::SELECTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			0
		);
	}
	break;
	case DungeonIn:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("던전 입구");
		initString->push_back("");
		initString->push_back("던전에 입장하시겠습니까?");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::SELECTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			0
		);
	}
	break;
	case Shop:
	case ShopActiveRange:
		break;
	case Exit:
	{
		if (mapData->CheckDungeonKey())
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("다음 던전으로 통하는 입구를 발견했다!");
			initString->push_back("다음 던전에 입장하시겠습니까?");

			POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
				PopupType::SELECTPOPUP,
				this,
				initString,
				15,
				0,
				5,
				0
			);
		}
	}
	break;
	}
}

void MapMovePlayer::ObjectSelectedActive(int selectValue)
{
	if (selectValue == 0)
	{
		ObjectActive(mapData->GetMapInfo(posX, posY));
		MapImageSet();
	}
}

void MapMovePlayer::CheckRunSoundPlay()
{
	if (runSoundDuration >= RUNSOUNDENDDURATION)
	{
		SOUNDMANAGER->PlayAmbient(Text("RunSound.wav"));
	}
	runSoundDuration = 0;
	activeCheck = false;
}
