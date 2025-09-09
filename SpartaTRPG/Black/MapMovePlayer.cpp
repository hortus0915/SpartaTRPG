#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"
#include "../Red/SelectPopup.h"
#include "../Red/MapData.h"
#include "Singletons/Scenes/BattleScene.h"
#include "Singletons/EffectType.h"


MapMovePlayer::MapMovePlayer(string _sn, MapData* _mapData) : iMapMovable(_sn, _mapData)
{
	runResetSoundDuration = RUNSOUNDENDDURATION;
	runPlayDuration = 0;
	range_Of_Sight = 0;
	mapMove = 1;
	monsterEffect = nullptr;
	activeCheck = false;
	randomType = RandomItemType::None;
	moveToShop = false;
	moveToMiniGame = false;
}

void MapMovePlayer::Init(Color _characterColor, Color _bgColor)
{
	__super::Init(_characterColor, _bgColor);
	if (randomType != RandomItemType::None)
	{
		auto addedItem = USERMANAGER->GetRandomItem(randomType);
		USERMANAGER->AddItem(addedItem->GetItemUID(), addedItem->GetItemCount());
	}
}

void MapMovePlayer::Update(float deltaTime)
{
	if (monsterEffect != nullptr)
	{
		if (monsterEffect->IsRunning())
		{
			SOUNDMANAGER->StopAmbient(Text("RunSound.wav"));
			mapMove = -1;
		}
	}

	if (mapMove > 0)
	{
		range_Of_Sight += deltaTime * 50;
		
		if (range_Of_Sight > RANGE_OF_SIGHT)
		{
			range_Of_Sight = RANGE_OF_SIGHT;
			mapMove = 0;
		}
		MapImageSet();
	}
	if (mapMove < 0)
	{
		range_Of_Sight -= deltaTime * 50;

		if (range_Of_Sight < 0)
		{
			range_Of_Sight = 0;
			mapMove = 1;
			if (monsterEffect != nullptr)
			{
				monsterEffect = nullptr;
				mapData->ObjectReset(posX, posY);
				auto battle = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "BattleScene");
				SCENEMANAGER->ChangeChild("BattleScene");
				SCENEMANAGER->CurrentSceneInit();
				return;
			}
			else if(moveToShop)
			{
				moveToShop = false;
				auto shop = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "ShopScene");
				SCENEMANAGER->ChangeChild("ShopScene");
				SCENEMANAGER->CurrentSceneInit();
			}
			else if (moveToMiniGame)
			{
				moveToMiniGame = false;
				auto shop = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "MinigameScene");
				SCENEMANAGER->ChangeChild("MinigameScene");
				SCENEMANAGER->CurrentSceneInit();
			}
		}
		MapImageSet();
	}

	if (mapMove == 0 && monsterEffect == nullptr)
	{
		if (POPUPMANAGER->CheckPopupActive() == false)
			MapInput(deltaTime);

		if (!activeCheck)
		{
			CheckActive();
			activeCheck = true;
		}

		if (runResetSoundDuration == 0)
		{
			if (runPlayDuration > RUNSOUNDENDDURATIONMAX)
			{
				runPlayDuration = 0;
				SOUNDMANAGER->StopAmbient(Text("RunSound.wav"));
				SOUNDMANAGER->PlayAmbient(Text("RunSound.wav"));
			}
			runPlayDuration += deltaTime;
		}

		if (runResetSoundDuration < RUNSOUNDENDDURATION)
		{
			runResetSoundDuration += deltaTime;
		}
		else
		{
			SOUNDMANAGER->StopAmbient(Text("RunSound.wav"));
		}
	}
}

void MapMovePlayer::Render()
{
	__super::Render();
	TileDescrtiptionRender();
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
		mapMove = -1;
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

		auto addedItem = USERMANAGER->GetRandomItem(RandomItemType::Box);
		USERMANAGER->AddItem(addedItem->GetItemUID(), addedItem->GetItemCount());

		mapData->ObjectReset(posX, posY);
		break;
	}
	case Key:
	{
		mapData->ObjectReset(posX, posY);
		SOUNDMANAGER->StopAmbient(Text("RunSound.wav"));
		moveToMiniGame = true;
		mapMove = -1;
		break;
	}
	case DungeonIn:
	{
		mapMove = -1;
		activeCheck = true;
		mapData->CreateMap(MapType::Dungeon);
		break;
	}
	case Monster:
	case MonsterActiveRange:
	{
		//mapData->ObjectReset(posX, posY);
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
	case WallH:
	case WallV:
		POPUPMANAGER->PopupActiveOff();
		break;
	case Monster:
	case MonsterActiveRange:
	{
		auto monsterPosition = mapData->GetTileFromPosition(posX, posY);
		monsterEffect = EFFECTMANAGER->StartEffect(Shining, monsterPosition.first - posX + (MAX_SCREEN_WIDTH / 2) - 2, monsterPosition.second - posY + (MAX_SCREEN_HEIGTH / 2) - 2);
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
			5,
			1
		);
	}
	break;
	case Key:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("열쇠를 발견했다!");
		initString->push_back("");
		initString->push_back("열쇠를 줍기위해 미니게임을 도전하시겠습니까?");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::SELECTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			1
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
			1
		);
	}
	break;
	case Shop:
	case ShopActiveRange:
	{
		SOUNDMANAGER->StopAmbient(Text("RunSound.wav")); 
		moveToShop = true;
		mapMove = -1;
		break;
	}
	case Exit:
	{
		if (USERMANAGER->CheckHasKey())
		{
			vector<string>* initString = new vector<string>();
			initString->push_back("다음 던전으로 통하는 입구를 발견했다!");
			initString->push_back("");
			initString->push_back("다음 던전에 입장하시겠습니까?");

			POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
				PopupType::SELECTPOPUP,
				this,
				initString,
				15,
				0,
				5,
				1
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
				5,
				0
			);
		}
	}
	break;
	}
}

void MapMovePlayer::MapImageSet()
{
	tileDescriptions.clear();
	int harfWidth = MAX_SCREEN_WIDTH / 2;
	int harfHeight = MAX_SCREEN_HEIGTH / 2;
	int nowRange_Of_Sight = range_Of_Sight;

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
			if (i * i * 4 + j * j < nowRange_Of_Sight * nowRange_Of_Sight)
			{
				auto initData = mapData->GetMapData(mapX, mapY);
				CheckTileDescription(initData);
				image[harfHeight + i][harfWidth + j] = initData;
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
			if (i * i * 4 + j * j < nowRange_Of_Sight * nowRange_Of_Sight)
			{
				auto initData = mapData->GetMapData(mapX, mapY);
				CheckTileDescription(initData);
				image[harfHeight + i][harfWidth - j] = initData;
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
			if (i * i * 4 + j * j < nowRange_Of_Sight * nowRange_Of_Sight)
			{
				auto initData = mapData->GetMapData(mapX, mapY);
				CheckTileDescription(initData);
				image[harfHeight - i][harfWidth + j] = initData;
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
			if (i * i * 4 + j * j < nowRange_Of_Sight * nowRange_Of_Sight)
			{
				auto initData = mapData->GetMapData(mapX, mapY);
				CheckTileDescription(initData);
				image[harfHeight - i][harfWidth - j] = initData;
			}
			else
			{
				image[harfHeight - i][harfWidth - j] = '.';
			}
		}
	}
	isNewRender = true;
}

void MapMovePlayer::ObjectSelectedActive(int _selectValue)
{
	if (_selectValue == 0)
	{
		ObjectActive(mapData->GetMapInfo(posX, posY));
		MapImageSet();
	}
}

void MapMovePlayer::CheckRunSoundPlay()
{
	if (runResetSoundDuration >= RUNSOUNDENDDURATION)
	{
		SOUNDMANAGER->PlayAmbient(Text("RunSound.wav"));
	}
	runResetSoundDuration = 0;
	activeCheck = false;
}

void MapMovePlayer::TileDescrtiptionRender()
{
	int offsetY = 0;

	for (auto tileDescription : tileDescriptions)
	{
		offsetY++;
		SCENEMANAGER->RenderToBackbuffer(1, MAX_SCREEN_HEIGTH + offsetY, tileDescription.second.size(), 1, tileDescription.second);
	}
}

void MapMovePlayer::CheckTileDescription(char _data)
{
	if (_data == ' ')
		return;

	if (tileDescriptions.find(_data) == tileDescriptions.end())
	{
		tileDescriptions.emplace(_data, mapData->GetTileDescription(_data));
	}
}

void MapMovePlayer::SetVictory()
{
	auto addItem = USERMANAGER->GetRandomItem(RandomItemType::Monster);
	USERMANAGER->AddItem(addItem->GetItemUID(), addItem->GetItemCount());
}

void MapMovePlayer::SetDefeat()
{
	posX = 1;
	posY = 1;
	mapData->CreateMap(MapType::Village);
}
