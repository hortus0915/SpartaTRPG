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
		PopupInput();
	}
	else
	{
		MapInput();

		if (!activeCheck)
		{
			CheckActive();
			activeCheck = true;
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

void MapMovePlayer::PopupInput()
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
			popup->SetActive(false);
			ObjectActive(mapData->GetMapInfo(posX, posY));
			MapImageSet();
		}
		else
		{
			popup->SetActive(false);
		}
	}
	if (KEYMANAGER->IsStayKeyDown(VK_BACK))
	{
		popup->SetActive(false);
	}
}

void MapMovePlayer::MapInput()
{
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT))
	{
		MoveTo(-1, 0);
		activeCheck = false;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT))
	{
		MoveTo(1, 0);
		activeCheck = false;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		MoveTo(0, -1);
		activeCheck = false;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		MoveTo(0, 1);
		activeCheck = false;
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
		//¾ÆÀÌÅÛ È¹µæ
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
		//ÀüÅõ ¾ÀÀ¸·Î ÀÌµ¿
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
		popup->SetActive(false);
		break;
	case Box:
	case BoxActive:
	case Key:
	case DungeonIn:
	case Shop:
	case ShopActiveRange:
		popup->SetActive();
		break;
	case Exit:
		if (mapData->CheckDungeonKey())
		{
			popup->SetActive();
		}
		break;
	default:
		break;
	}
}
