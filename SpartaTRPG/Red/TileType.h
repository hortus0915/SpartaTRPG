#pragma once

enum TileType
{
	Empty = 0, //빈 공간 ' '
	Wall = 1, //벽 '#'
	Exit = 2,//탈출로 'H'
	Box = 3, //보물상자 'B'
	BoxActive = 300, //박스 엑티브 범위
	Key = 4, //열쇠 'K'
	Monster = 5, //몬스터 '@'
	MonsterActiveRange = 500, // 몬스터 공격 범위
	Shop = 6,//상점
	ShopActiveRange = 600, // 상점 엑티브 범위
	DungeonIn = 7,//던전 입장
};
