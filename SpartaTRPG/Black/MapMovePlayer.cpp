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
		initString->push_back("스파르타 코딩클럽… 겉으로는 평범한 개발 학원이지만");
		initString->push_back("그 이면에는 지옥이 숨어 있었다.");
		initString->push_back("");
		initString->push_back("궁극의 개발자가 되려는 야망에 사로잡힌 총괄, 이다경 곤듀.");
		initString->push_back("그녀는 세 개의 성을 세우고, ");
		initString->push_back("학생들을 고통 속으로 몰아넣었다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("버그와 과제, 충돌과 혼돈…");
		initString->push_back("이 모든 것을 이겨내야만 진정한 개발자가 될 수 있다고 그녀는 믿었다.");
		initString->push_back("하지만… 곤듀에 맞서 싸우는 용자들이 있었으니");
		initString->push_back("");
		initString->push_back("바로 파워스파 레인저다!!!!!!!!");
		initString->push_back("");
		initString->push_back("하지만 원래 다섯 명이었던 스파레인저의 핑크는 탈주해버렸다...");
		initString->push_back("");
		initString->push_back("이 때 팀은 새로운 힘을 맞이했으니!");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("바로… 당신이다!");
		initString->push_back("");
		initString->push_back("이제, 새로운 레인저와 함께 세 개의 성을 돌파하고");
		initString->push_back("이다경 곤듀의 야망을 막아야 한다!");
		initString->push_back("");
		initString->push_back("기본 설명");
		initString->push_back("");
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
				initString->push_back("횃불을 발견했다!");

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
				SCENEMANAGER->ChangeChild("BattleScene");
				EnemyInfoBase* enemy = new EnemyInfoBase;
				SpawnEnemyByLevel(*enemy, USERMANAGER->GetPlayer()->GetLevel());
				battle->SetBattlers(USERMANAGER->GetPlayer(), enemy);
				SCENEMANAGER->CurrentSceneInit();
				return;
			}
			else if(moveToShop)
			{
				moveToShop = false;
				if (!isFirstShop)
				{
					//auto shop = (ShopScene*)SCENEMANAGER->FindChild("GameScene", "ShopScene");
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
				mapData->ObjectReset(posX, posY);

				auto temp = GetIntRange(0, 9);
				if (USERMANAGER->GetStage() % 2 == 0)
				{
					//auto minigameScene = (MinigameScene*)SCENEMANAGER->FindChild("GameScene", "QuizScene");
					SCENEMANAGER->ChangeChild("QuizScene");
					SCENEMANAGER->CurrentSceneInit();
				}
				else
				{
					//auto minigameScene = (MinigameScene*)SCENEMANAGER->FindChild("GameScene", "MinigameScene");
					SCENEMANAGER->ChangeChild("MinigameScene");
					SCENEMANAGER->CurrentSceneInit();
				}
				return;
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

	if (mapData->CheckKey() == false && USERMANAGER->CheckHasKey() == false)
	{
		//TODO -> GameOverScene으로 이동
		SCENEMANAGER->ChangeScene("GameOverScene");
		SCENEMANAGER->CurrentSceneInit();
		return;
	}
}

void MapMovePlayer::Render()
{
	__super::Render();
	StageInfoRender();
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
			if (USERMANAGER->GetPlayer()->GetLevel() < 10)
			{
				USERMANAGER->GetPlayer()->GainExp(10000);
				boss = new EnemyInfoBase;
				SpawnEnemyBoss(*boss, USERMANAGER->GetPlayer()->GetLevel());
				vector<string>* initString = new vector<string>();
				initString->push_back("보스방에 진입하려 합니다...");
				initString->push_back("하지만 아직 지식과 실력이 부족합니다");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("탈주닌자 핑크: 풉ㅋㅋ 보스 만나기엔 레벨이 좀 딸리지 않냐?");
				initString->push_back("내가 겪어봐서 아는데, 지금 들어가면 곤듀한테 순삭 당한다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("받아 내가 모아둔 경험치야");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("내가 널 걱정해서 이러는 건 아니고,");
				initString->push_back("신입 네가 쪽박 차는 꼴은 보고 싶지 않아서야.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("경험치를 10000 획득했습니다!");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("됐어. 이제 곤듀랑 맞설 수는 있겠지.");
				initString->push_back("하지만 잊지 마라. 이건 내가 준 힘이 아니라,");
				initString->push_back("네가 여기까지 버텨왔기에 받아들일 수 있었던 거다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("가라. 마지막은 네가 증명해라.");
				initString->push_back("네가 진짜 레인저인지, 아니면 나처럼 탈주자가 될지");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("보스방 입장");

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
			else
			{
				boss = new EnemyInfoBase;
				SpawnEnemyBoss(*boss, USERMANAGER->GetPlayer()->GetLevel());
				vector<string>* initString = new vector<string>();
				initString->push_back("보스방에 진입하려 합니다...");
				initString->push_back("문 너머에서 묘한 기운이 흘러나옵니다.");
				initString->push_back("서늘한 공기 속에서 손끝이 저절로 떨려온다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("블루: 이런 기분, 꼭 시험장 들어가기 직전 같다...");
				initString->push_back("괜히 배도 고픈데, 지금은 라면 먹을 상황도 아니고.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("이정우 튜터님 : 여기까지 오다니 대단해!");
				initString->push_back(" 너희라면 해낼 수 있을거야!");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("자, 이제 나아가라.");
				initString->push_back("겁을 이겨내는 순간, 너의 코드가 진짜 힘을 보여줄 것이다.");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("");
				initString->push_back("보스방 입장");
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
	case PINK:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("탈주닌자 핑크 : 에휴, 이래서 내가 나간 거지.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("한숨을 내쉬며 1000G를 쥐어주었다.....");
		USERMANAGER->AddItem(Item::GetItemUID(ItemType::Cost,ItemValueType::Cost, 1),1000, false);

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
		if (!isFirstPlay && !isFirstDungeon)
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
		initString->push_back("이다경 곤듀 : 여기까지 기어올라오다니, 하찮은 학생 주제에 제법이군.");
		initString->push_back("하지만 착각하지 마라.");
		initString->push_back("진짜 개발은 고독 속에서 이루어진다.");
		initString->push_back("협력? 팀워크? 그건 결국 약자들의 핑계일 뿐이다.");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("희망? 그건 환상이다.");
		initString->push_back("강창몬 따위에 의존하는 한, ");
		initString->push_back("너희는 영원히 진짜 개발자가 될 수 없다.");
		initString->push_back("");
		initString->push_back(""); 
		char buf[128];
		std::snprintf(buf, sizeof(buf), "%s : 아니, 진짜 개발은 함께 하는 거야.", USERMANAGER->GetPlayer()->GetName()); //TODO HP출력하는거
		initString->push_back(buf);
		initString->push_back("버그를 함께 고치고, 과제를 함께 이겨내고");
		initString->push_back("끝내는 웃으면서 완성하는 것!");
		initString->push_back("너의 왜곡된 신념은 우리가 여기서 끝낸다!");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("입으로 떠드는 건 쉽지! 그렇다면 직접 증명해 보아라!");
		initString->push_back("내가 만든 버그 지옥을 넘을 수 있는지!!!!!!!!!!!");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("전투를 시작합니다.");
		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::BossBattle>(
			PopupType::RESULTPOPUP,
			this,
			initString,
			15,
			0,
			5,
			1
		);
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
		break;
	}
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
		break;
	}
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
		break;
	}
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
		break;
	}
	case PINK:
	{
		vector<string>* initString = new vector<string>();
		initString->push_back("탈주닌자 핑크와 조우했다");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("");
		initString->push_back("탈주닌자 핑크 : 게임 개발이나 한다면서… 이런 것도 못 해?");
		POPUPMANAGER->InitPopup<MapMovePlayer, &MapMovePlayer::ObjectSelectedActive>(
			PopupType::RESULTPOPUP,
			this,
			initString,
			15,
			0,
			2,
			1
		);
		break;
	}
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

	auto playerInfo = USERMANAGER->GetPlayer();
	char buf[128];
	std::snprintf(buf, sizeof(buf), "%s  HP %d / %d    LV : %d", playerInfo->GetName().c_str(), (int)playerInfo->GetCurHP(), (int)playerInfo->GetMaxHP(), playerInfo->GetLevel()); //TODO HP출력하는거
	SCENEMANAGER->RenderToBackbuffer(1, MAX_SCREEN_HEIGTH, MAX_SCREEN_WIDTH, 1, buf);
}

void MapMovePlayer::StageInfoRender()
{
	switch (mapData->GetMapType())
	{
	case MapType::Village:
		SCENEMANAGER->RenderToBackbuffer(MAX_SCREEN_WIDTH/2 - 5, 0, MAX_SCREEN_WIDTH, 1, "마을");
		break;
	case MapType::Dungeon:
		char buf[128];
		std::snprintf(buf, sizeof(buf), "스테이지 %d", USERMANAGER->GetStage());
		SCENEMANAGER->RenderToBackbuffer(MAX_SCREEN_WIDTH / 2 - 5, 0, MAX_SCREEN_WIDTH, 1, buf);
		break;
	case MapType::BossRoom:
		SCENEMANAGER->RenderToBackbuffer(MAX_SCREEN_WIDTH / 2 - 5, 0, MAX_SCREEN_WIDTH, 1, "보스방");
		break;
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
	//auto shop = (BattleScene*)SCENEMANAGER->FindChild("GameScene", "ShopScene");
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
	SCENEMANAGER->ChangeChild("BattleScene");
	battle->SetBattlers(USERMANAGER->GetPlayer(), boss);
	SCENEMANAGER->CurrentSceneInit();
}