#include "MapTileInfo.h"

MapTileInfo::MapTileInfo(int tileIndex)
{
	this->tileIndex = tileIndex;
}

int MapTileInfo::GetTileGroup()
{
	return tileGroup;
}

void MapTileInfo::SetTileGroup(int index)
{
    if (tileGroup != index)
    {
        tileGroup = index;
    }
    if (preTile != nullptr && preTile->GetTileGroup() != index)
    {
        preTile->SetTileGroup(tileGroup);
    }
    if (nextTile != nullptr && nextTile->GetTileGroup() != index)
    {
        nextTile->SetTileGroup(tileGroup);
    }
    if (upponTile != nullptr && upponTile->GetTileGroup() != index)
    {
        upponTile->SetTileGroup(tileGroup);
    }
    if (bottomTile != nullptr && bottomTile->GetTileGroup() != index)
    {
        bottomTile->SetTileGroup(tileGroup);
    }
}
