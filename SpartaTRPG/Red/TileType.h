#pragma once

enum TileType
{
	Empty = 0, //빈 공간 ' '
	WallH = 1, //벽 '#'
	WallV = 2, //벽 '#'
	Wall = 3, //벽 '#'
	Exit = 4,//탈출로 'H'
	Box = 5, //보물상자 'B'
	BoxActive = 500, //박스 엑티브 범위
	Key = 6, //열쇠 'K'
	Monster = 7, //몬스터 '@'
	MonsterActiveRange = 700, // 몬스터 공격 범위
	Shop = 8,//상점
	ShopActiveRange = 800, // 상점 엑티브 범위
	DungeonIn = 9,//던전 입장
	BOSS = 10,//보스
	BOSSActive = 1000,//보스 조우 범위
	PINK = 11,
};
