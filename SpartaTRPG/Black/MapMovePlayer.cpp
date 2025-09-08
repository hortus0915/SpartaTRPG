#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"
#include "../Red/SelectPopup.h"
#include "../Red/MapData.h"
#include "Singletons/Scenes/BattleScene.h"


MapMovePlayer::MapMovePlayer(string _sn, MapData* _mapData) : iMapMovable(_sn, _mapData)
{
	runSoundDuration = RUNSOUNDENDDURATION;
	testInven = new Inventory();
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
	if (KEYMANAGER->IsStayKeyDown(VK_TAB))
	{
		POPUPMANAGER->InitPopup<MapMovePlayer, nullptr>(
			PopupType::INVENTORYPOPUP,
			nullptr
		);
	}
}

void MapMovePlayer::ObjectActive(TileType _tileType)
{
	switch (_tileType)
	{
	case Exit:
	{
		mapData->CreateMap(MapType::Dungeon);
		break;
	}
	case Box:
	case BoxActive:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("박스에서 아이템을 획득하였다!");

		POPUPMANAGER->InitPopup<MapMovePlayer, nullptr>(
			PopupType::RESULTPOPUP,
			nullptr,
			initString,
			15,
			0,
			5,
			0
		);
		//아이템 획득
		mapData->ObjectReset(posX, posY);
		break;
	}
	case Key:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("열쇠를 획득하였다!");

		POPUPMANAGER->InitPopup<MapMovePlayer, nullptr>(
			PopupType::RESULTPOPUP,
			nullptr,
			initString,
			15,
			0,
			5,
			0
		);
		mapData->ObjectReset(posX, posY);
		break;
	}
	case DungeonIn:
	{
		mapData->CreateMap(MapType::Dungeon);
		break;
	}
	case Monster:
	case MonsterActiveRange:
	{
		//전투 씬으로 이동
		mapData->ObjectReset(posX, posY);
		break;
	}
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
		POPUPMANAGER->PopupActiveOff();
		break;
	case Monster:
	case MonsterActiveRange:
	{
		auto battle = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "BattleScene");
		if (battle)
		{
			//battle->SetBattlers(USERMANAGER->GetPlayer(), USERMANAGER->SetMonster());
		}

		SCENEMANAGER->ChangeChild("BattleScene");
		SCENEMANAGER->CurrentSceneInit();

		break;
	}
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
			2,
			4
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
			2,
			4
		);
	}
	break;
	case DungeonIn:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("던전 입구");
		initString->push_back("");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		initString->push_back("던전에 입장하시겠습니까?");
		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::SELECTPOPUP,
			this,
			initString,
			15,
			0,
			2,
			4
		);
	}
	break;
	case Shop:
	case ShopActiveRange:
		break;
	case Exit:
	{
		if (USERMANAGER->CheckHasKey())
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
				2,
				4
			);
		}
		else
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("열쇠가 필요하다!");

			POPUPMANAGER->InitPopup<MapMovePlayer, nullptr>(
				PopupType::RESULTPOPUP,
				nullptr,
				initString,
				15,
				0,
				2,
				0
			);
		}
	}
	break;
	}
}

void MapMovePlayer::MapImageSet()
{
	int harfWidth = MAX_SCREEN_WIDTH / 2;
	int harfHeight = MAX_SCREEN_HEIGTH / 2;

	for (int i = 0; i < harfHeight; ++i)
	{
		int mapY = posY + i;
		for (int j = 0; j < harfWidth; ++j)
		{
			if (i == 0 && j == 0)
			{
				image[harfHeight + i][harfWidth + j] = 'O';
				continue;
			}

			if (SetWall(harfWidth, harfHeight, j, i, harfHeight + i, harfWidth + j)) continue;

			int mapX = posX + j;
			if (i * i * 4 + j * j < RANGE_OF_SIGHT * RANGE_OF_SIGHT)
			{
				image[harfHeight + i][harfWidth + j] = mapData->GetMapData(mapX, mapY);
			}
			else
			{
				image[harfHeight + i][harfWidth + j] = '.';
			}
		}
		for (int j = 1; j < harfWidth; ++j)
		{
			if (SetWall(harfWidth, harfHeight, j, i, harfHeight + i, harfWidth - j)) continue;

			int mapX = posX - j;
			if (i * i * 4 + j * j < RANGE_OF_SIGHT * RANGE_OF_SIGHT)
			{
				image[harfHeight + i][harfWidth - j] = mapData->GetMapData(mapX, mapY);
			}
			else
			{
				image[harfHeight + i][harfWidth - j] = '.';
			}
		}
	}
	for (int i = 1; i < harfHeight; ++i)
	{
		int mapY = posY - i;
		for (int j = 0; j < harfWidth; ++j)
		{
			if (SetWall(harfWidth, harfHeight, j, i, harfHeight - i, harfWidth + j)) continue;

			int mapX = posX + j;
			if (i * i * 4 + j * j < RANGE_OF_SIGHT * RANGE_OF_SIGHT)
			{
				image[harfHeight - i][harfWidth + j] = mapData->GetMapData(mapX, mapY);
			}
			else
			{
				image[harfHeight - i][harfWidth + j] = '.';
			}
		}
		for (int j = 1; j < harfWidth; ++j)
		{
			if (SetWall(harfWidth, harfHeight, j, i, harfHeight - i, harfWidth - j)) continue;

			int mapX = posX - j;
			if (i * i * 4 + j * j < RANGE_OF_SIGHT * RANGE_OF_SIGHT)
			{
				image[harfHeight - i][harfWidth - j] = mapData->GetMapData(mapX, mapY);
			}
			else
			{
				image[harfHeight - i][harfWidth - j] = '.';
			}
		}
	}
	isNewRender = true;
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
