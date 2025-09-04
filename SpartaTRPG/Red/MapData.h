#pragma once
#include <map>
#include <vector>
#include "TileType.h"

#define MAP_WIDTH			5
#define MAP_HEIGHT			5
#define MAP_CHUNKWIDTH		30
#define MAP_CHUNKHEIGHT		15

#define VILLAGE_WIDTH 61
#define VILLAGE_HEIGHT 15

class TileInfo;

enum MapType
{
	NoneSelect,
	Village,
	Dungeon,
};

class TileObjectInfo;

class MapData
{
private:
	TileInfo** mapInfo;
	int GetIndex(int x, int y);
	int dungeonLevel;
	MapType mapType = MapType::Dungeon;
	std::map<TileType,std::vector<TileInfo*>> objectInfo;

	void DungeonMapSet();
	void VillageMapSet();
	void DungeonObjectCreate();
	void DungeonObjectLoad();
	void VillageObjectSet();

	void ObjectSet(TileType _tileType, int _fromIndexX, int _fromIndexY);
	void ObjectRandomSet(TileType _tileType, int _count);
	int TileSet(TileType _tileType, int _posX, int _posY, int _fromIndexX, int _fromIndexY);

	int GetRange(TileType _tileType);

public:
	MapData();
	~MapData();

	void Release();

	void CreateMap(MapType _mapType);

	char GetMapData(int posX, int posY);

	TileType GetMapInfo(int posX, int posY);

	const int GetMapWidth(MapType _mapType = MapType::NoneSelect);
	const int GetMapHeight(MapType _mapType = MapType::NoneSelect);
};

