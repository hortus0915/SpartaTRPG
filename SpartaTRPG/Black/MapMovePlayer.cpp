#include "MapMovePlayer.h"

#include "Singletons/CommonManagers.h"
#include "../Red/MapPopup.h"
#include "../Red/MapData.h"

MapMovePlayer::MapMovePlayer(string _sn, MapData* _mapData) : iMapMovable(_sn, _mapData)
{
	popup = new MapPopup(_sn);
}

void MapMovePlayer::Init(Color _characterColor, Color _bgColor)
{
	__super::Init(_characterColor, _bgColor);
}

void MapMovePlayer::Update(float deltaTime)
{
	if (popup->CheckActive())
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		{
			popup->Select(true);
		}
		if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
		{
			popup->Select(false);
		}
		if (KEYMANAGER->IsStayKeyDown(VK_RETURN))
		{
			if (popup->CheckSelect())
			{
				popup->SetActive(TileType::Empty);
				ObjectActive(mapData->GetMapInfo(posX, posY));
				MapImageSet();
			}
			else
			{
				popup->SetActive(TileType::Empty);
			}
		}
		if (KEYMANAGER->IsStayKeyDown(VK_BACK))
		{
			popup->SetActive(TileType::Empty);
		}
	}
	else
	{
		if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
		{
			MoveTo(-1, 0);
			showPopup = false;
		}
		if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
		{
			MoveTo(1, 0);
			showPopup = false;
		}
		if (KEYMANAGER->IsStayKeyDown(VK_UP))
		{
			MoveTo(0, -1);
			showPopup = false;
		}
		if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		{
			MoveTo(0, 1);
			showPopup = false;
		}

		if (!showPopup)
		{
			CheckPopup();
			showPopup = true;
		}
	}
}

void MapMovePlayer::Render()
{
	__super::Render();

	if (popup->CheckActive())
	{
		popup->Render();
	}
}

void MapMovePlayer::Release()
{
	__super::Release();

	if (popup)
	{
		popup->Release();
		SAFE_DELETE(popup);
	}
}

void MapMovePlayer::ObjectActive(TileType _tileType)
{
	switch (_tileType)
	{
	case Empty:
		break;
	case Wall:
		break;
	case Exit:
		break;
	case Box:
		break;
	case BoxActive:
		break;
	case Key:
		break;
	case Shop:
	case ShopActiveRange:
		break;
	case DungeonIn:
		mapData->CreateMap(MapType::Dungeon);
		break;
	case Monster:
	case MonsterActiveRange:
		break;
	default:
		break;
	}
}

void MapMovePlayer::CheckPopup()
{
	auto mapInfo = mapData->GetMapInfo(posX, posY);
	popup->SetActive(mapInfo);
}
