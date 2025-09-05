#pragma once
class MapCreateTileInfo
{
public:
	MapCreateTileInfo* preTile = nullptr;
	MapCreateTileInfo* nextTile = nullptr;
	MapCreateTileInfo* upponTile = nullptr;
	MapCreateTileInfo* bottomTile = nullptr;

	MapCreateTileInfo(int tileIndex);
	~MapCreateTileInfo() {};

	int GetTileGroup();
	void SetTileGroup(int index);

private:
	int tileIndex = 0;
	int tileGroup = -1;
};

