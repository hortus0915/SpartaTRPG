#pragma once

enum TileType
{
	Empty = 0, //�� ���� ' '
	Wall = 1, //�� '#'
	Exit = 2,//Ż��� 'H'
	Box = 3, //�������� 'B'
	BoxActive = 300, //�ڽ� ��Ƽ�� ����
	Key = 4, //���� 'K'
	Monster = 5, //���� '@'
	MonsterActiveRange = 500, // ���� ���� ����
	Shop = 6,//����
	ShopActiveRange = 600, // ���� ��Ƽ�� ����
	DungeonIn = 7,//���� ����
};
