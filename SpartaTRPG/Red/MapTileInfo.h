#pragma once
class MapTileInfo
{
public:
	MapTileInfo* preTile = nullptr;
	MapTileInfo* nextTile = nullptr;
	MapTileInfo* upponTile = nullptr;
	MapTileInfo* bottomTile = nullptr;

	MapTileInfo(int tileIndex);
	~MapTileInfo() {};

	int GetTileGroup();
	void SetTileGroup(int index);

private:
	int tileIndex = 0;
	int tileGroup = -1;
};

