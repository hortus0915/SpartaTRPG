#include "TileInfo.h"

TileInfo::TileInfo()
{
}

TileInfo::~TileInfo()
{
}

void TileInfo::SetTileType(TileType _tileType, int _fromIndexX, int _fromIndexY)
{
	tileType = _tileType;
	fromIndexX = _fromIndexX;
	fromIndexY = _fromIndexY;
}
