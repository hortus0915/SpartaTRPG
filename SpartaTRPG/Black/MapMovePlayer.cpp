#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"
#include "../Red/SelectPopup.h"
#include "../Red/MapData.h"
#include "Singletons/Scenes/BattleScene.h"
#include "Singletons/EffectType.h"
#include "Singletons/Scenes/MinigameScene.h"
#include "CommonFuncs.h"
#include "Singletons/Scenes/ShopScene.h"
#include "../Black/EnemyInfoBase.h"
#include "../Black/PlayerInfo.h"


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
	isFirstPlay = true;
	isFirstShop = true;
	isFirstDungeon = true;
	isFirstDungeon2 = false;
}

void MapMovePlayer::Init(Color _characterColor, Color _bgColor)
{
	__super::Init(_characterColor, _bgColor);

	if (isFirstPlay)
	{
		mapMove = 0;
		range_Of_Sight = 0;
		vector<string>* initString = new vector<string>();
		initString->push_back("안녕하세요, 여행자님!");
		initString->push_back("");
		initString->push_back("이 여정에 함께하게 되어 기쁩니다.");
		initString->push_back("");
		initString->push_back("메세지는 화살표를 통해 페이지를 넘길 수 있습니다");
		initString->push_back("");
		initString->push_back("게임은 마을에서 부터 시작됩니다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("'S' 표식에 다가가면 상점으로 이동할 수 있습니다.");
		initString->push_back("'D' 표식으로 가면 던전에 입장할 수 있습니다..");
		initString->push_back("");
		initString->push_back("HP가 0이 되면 이 마을로 다시 돌아옵니다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("백스페이스나 ESC로 메세지창을 닫을 수 있습니다.");
		initString->push_back("");
		initString->push_back("엔터키를 통해서 선택을 완료할 수 있습니다.");
		initString->push_back("");
		initString->push_back("탭키를 눌러 인벤토리를 열 수 있습니다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("그럼, 행운을 빕니다. 키보드를 잡고, 모험을 시작하세요!");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::TutorialPopup>(
			PopupType::RESULTPOPUP,
			this,
			initString,
			5,
			0,
			2,
			0
		);
	}

	if (randomType != RandomItemType::None)
	{
		auto addedItem = USERMANAGER->GetRandomItem(randomType);
		USERMANAGER->AddItem(addedItem->GetItemUID(), addedItem->GetItemCount(),true);
	}
}

void MapMovePlayer::Update(float deltaTime)
{
	if (mapData->CheckKey() == false)
	{
		//TODO -> GameOverScene으로 이동
		vector<string>* initString = new vector<string>();
		initString->push_back("던전에 입장하셨습니다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("'#' 벽은 이동할 수 없습니다.");
		initString->push_back("'I' 아이템이 들어있는 박스입니다. 대박을 노리세요!");
		initString->push_back("'K' 다음 층으로 갈 수 있게하는 열쇠입니다.");
		initString->push_back("해당 아이템의 획득을 위해서는 가벼운 게임을 진행해야합니다.");
		initString->push_back("'H' 다음 층으로 이동할 수 있는 통로입니다.");
		initString->push_back("열쇠를 찾아서 다음층으로 이동하세요!");
		initString->push_back("'M' 맵에 있는 몬스터 입니다.");
		initString->push_back("가까이 다가가면 전투가 벌어집니다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("던전의 가장 위에 매우 위험한 보스가 숨어 있습니다. 준비 없이 맞서지 마세요.");

		POPUPMANAGER->InitPopup<MapMovePlayer>(
			PopupType::RESULTPOPUP,
			nullptr,
			initString,
			5,
			0,
			2,
			0
		);
	}

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

			if (isFirstDungeon2)
			{
				isFirstDungeon2 = false;
				vector<string>* initString = new vector<string>();
				initString->push_back("던전에 입장하셨습니다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("'#' 벽은 이동할 수 없습니다.");
				initString->push_back("'I' 아이템이 들어있는 박스입니다. 대박을 노리세요!");
				initString->push_back("'K' 다음 층으로 갈 수 있게하는 열쇠입니다.");
				initString->push_back("해당 아이템의 획득을 위해서는 가벼운 게임을 진행해야합니다.");
				initString->push_back("'H' 다음 층으로 이동할 수 있는 통로입니다.");
				initString->push_back("열쇠를 찾아서 다음층으로 이동하세요!");
				initString->push_back("'M' 맵에 있는 몬스터 입니다.");
				initString->push_back("가까이 다가가면 전투가 벌어집니다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("던전의 가장 위에 매우 위험한 보스가 숨어 있습니다. 준비 없이 맞서지 마세요.");

				POPUPMANAGER->InitPopup<MapMovePlayer>(
					PopupType::RESULTPOPUP,
					nullptr,
					initString,
					5,
					0,
					2,
					0
				);
			}
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
			if (isFirstDungeon)
			{
				mapMove = 0;
				isFirstDungeon = false;
				vector<string>* initString = new vector<string>();
				initString->push_back("너무 어두워서 아무것도 보이지 않는다");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("...");
				initString->push_back("");
				initString->push_back("횟불을 발견했다!");

				POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::DungeonTutorialPopup>(
					PopupType::RESULTPOPUP,
					this,
					initString,
					5,
					0,
					2,
					0
				);
			}

			if (monsterEffect != nullptr)
			{
				monsterEffect = nullptr;
				mapData->ObjectReset(posX, posY);
				auto battle = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "BattleScene");
				EnemyInfoBase* enemy = new EnemyInfoBase;
				SpawnEnemyByLevel(*enemy, USERMANAGER->GetPlayer()->GetLevel());
				SCENEMANAGER->ChangeChild("BattleScene");
				SCENEMANAGER->CurrentSceneInit();
				return;
			}
			else if(moveToShop)
			{
				moveToShop = false;
				if (!isFirstShop)
				{
					auto shop = (ShopScene*)SCENEMANAGER->FindChild("GameScene", "ShopScene");
					SCENEMANAGER->ChangeChild("ShopScene");
					SCENEMANAGER->CurrentSceneInit();
				}
				else
				{
					mapMove = 0;
					vector<string>* initString = new vector<string>();
					initString->push_back("상점에 도착하셨군요");
					initString->push_back("");
					initString->push_back("가지고있는 골드를 사용하여 다양한 아이템을 구매하실 수 있습니다!");
					initString->push_back("");
					initString->push_back("장착가능한 장비부터 ~ 전투에 사용되는 카드");
					initString->push_back("체력을 회복시켜주는 포션까지!");
					initString->push_back("");
					initString->push_back("아이템을 구매하여 던전을 준비하세요!");

					POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ShopTutorialPopup>(
						PopupType::RESULTPOPUP,
						this,
						initString,
						5,
						0,
						2,
						0
					);
				}
			}
			else if (moveToMiniGame)
			{
				moveToMiniGame = false;

				auto temp = GetIntRange(0, 9);
				if (temp < 8)
				{
					auto minigameScene = (MinigameScene*)SCENEMANAGER->FindChild("GameScene", "MinigameScene");
					SCENEMANAGER->ChangeChild("MinigameScene");
					SCENEMANAGER->CurrentSceneInit();
				}
				else
				{
					auto minigameScene = (MinigameScene*)SCENEMANAGER->FindChild("GameScene", "QuizScene");
					SCENEMANAGER->ChangeChild("QuizScene");
					SCENEMANAGER->CurrentSceneInit();
				}
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
	PlayerInfoRender();
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
		if (USERMANAGER->GetStage() == MAXSTAGE - 1)
		{
			mapMove = -1;
			mapData->CreateMap(MapType::BossRoom);
			SetPos(BOSS_WIDTH / 2, BOSS_HEIGHT - 4);
		}
		else
		{
			mapMove = -1;
			mapData->CreateMap(MapType::Dungeon);
		}
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
		USERMANAGER->AddItem(addedItem->GetItemUID(), addedItem->GetItemCount(), true);

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
		if(!isFirstPlay && !isFirstDungeon)
			POPUPMANAGER->PopupActiveOff();
		break;
	case Monster:
	case MonsterActiveRange:
	{
		auto monsterPosition = mapData->GetTileFromPosition(posX, posY);
		monsterEffect = EFFECTMANAGER->StartEffect(Shining, monsterPosition.first - posX + (MAX_SCREEN_WIDTH / 2) - 2, monsterPosition.second - posY + (MAX_SCREEN_HEIGTH / 2) - 2);
		break;
	}
	case BOSS:
	case BOSSActive:
	{
		mapMove = -1;
		vector<string>* initString = new vector<string>();
		initString->push_back("보스와의 전투를 시작합니다.");

		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::BossBattle>(
			PopupType::RESULTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			1
		);
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
	int offsetY = 1;

	for (auto tileDescription : tileDescriptions)
	{
		offsetY++;
		SCENEMANAGER->RenderToBackbuffer(1, MAX_SCREEN_HEIGTH + offsetY, tileDescription.second.size(), 1, tileDescription.second);
	}
}

void MapMovePlayer::PlayerInfoRender()
{
	char buf[128];
	std::snprintf(buf, sizeof(buf), "플레이어  HP : "); //TODO HP출력하는거
	SCENEMANAGER->RenderToBackbuffer(1, MAX_SCREEN_HEIGTH, MAX_SCREEN_WIDTH, 1, buf);
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
	USERMANAGER->AddItem(addItem->GetItemUID(), addItem->GetItemCount(), true);
}

void MapMovePlayer::SetDefeat()
{
	mapData->CreateMap(MapType::Village);
	SetPos(1, VILLAGE_HEIGHT / 2);
}

void MapMovePlayer::TutorialPopup(int _select)
{
	mapMove = 1;
	isFirstPlay = false;
}

void MapMovePlayer::ShopTutorialPopup(int _select)
{
	mapMove = 1;
	isFirstShop = false;
	auto shop = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "ShopScene");
	SCENEMANAGER->ChangeChild("ShopScene");
	SCENEMANAGER->CurrentSceneInit();
}

void MapMovePlayer::DungeonTutorialPopup(int _select)
{
	mapMove = 1;
	isFirstDungeon2 = true;
}

void MapMovePlayer::BossBattle(int _select)
{
	auto battle = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "BattleScene");
	EnemyInfoBase* enemy = new EnemyInfoBase;
	SpawnEnemyBoss(*enemy, USERMANAGER->GetPlayer()->GetLevel());
	SCENEMANAGER->ChangeChild("BattleScene");
	SCENEMANAGER->CurrentSceneInit();
}

