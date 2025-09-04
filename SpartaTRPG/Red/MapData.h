#pragma once

#define MAP_WIDTH			5
#define MAP_HEIGHT			5
#define MAP_CHUNKWIDTH		30
#define MAP_CHUNKHEIGHT		15


enum TileType
{
	Empty, //ºó °ø°£ ' '
	Wall //º® '#'
};

class MapData
{
private:
	TileType** mapInfo;
	int GetIndex(int x, int y);

public:
	MapData();
	~MapData();

	void Release();

	void CreateMap();

	char GetMapData(int posX, int posY);

	TileType GetMapInfo(int posX, int posY);

	int GetMapWidth();
	int GetMapHeight();
};

