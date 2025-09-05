#pragma once
#include "TileType.h"

class TileInfo
{
public:
	TileInfo();
	~TileInfo();

	void SetTileType(TileType _tileType, int _fromIndexX, int _fromIndexY);
	inline TileType GetTileType() { return tileType; }
	inline int GetFromIndexX() { return fromIndexX; }
	inline int GetFromIndexY() { return fromIndexY; }
private:
	TileType tileType;

	int fromIndexX;
	int fromIndexY;
};

