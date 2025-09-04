#include "MapCreateTileInfo.h"

MapCreateTileInfo::MapCreateTileInfo(int tileIndex)
{
	this->tileIndex = tileIndex;
}

int MapCreateTileInfo::GetTileGroup()
{
	return tileGroup;
}

void MapCreateTileInfo::SetTileGroup(int index)
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
