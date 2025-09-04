#include "MapData.h"
#include "MapTileInfo.h"
#include "../Black/CommonMacros.h"
#include "../Black/CommonFuncs.h"

int MapData::GetIndex(int x, int y)
{
    return x + (y * MAP_WIDTH);
}

MapData::MapData()
{
    mapInfo = new TileType * [MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1];
    for (int i = 0; i < MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1; ++i)
    {
        mapInfo[i] = new TileType[MAP_HEIGHT * (MAP_CHUNKHEIGHT + 1) + 1];
        for (int j = 0; j < MAP_HEIGHT * (MAP_CHUNKHEIGHT + 1) + 1; ++j)
            mapInfo[i][j] = TileType::Empty;
    }
}

MapData::~MapData()
{
    if (mapInfo)
        Release();
}

void MapData::Release()
{
    for (int i = 0; i < MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1; ++i)
    {
        SAFE_DELETE_ARR(mapInfo[i])
    }
    SAFE_DELETE_ARR(mapInfo)
}

void MapData::CreateMap()
{
    MapTileInfo** boardTemp = nullptr;

    bool boardTempArray[MAP_WIDTH * 2 + 1][MAP_HEIGHT * 2 + 1];

    for (int y = 0; y < MAP_HEIGHT * 2 + 1; y++)
    {
        for (int x = 0; x < MAP_WIDTH * 2 + 1; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                boardTempArray[x][y] = false;
            }
            else
            {
                boardTempArray[x][y] = true;
            }
        }
    }

    if (boardTemp == nullptr)
    {
        boardTemp = new MapTileInfo*[MAP_WIDTH * MAP_HEIGHT];
    }
    int maxIndex = 0;

    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            boardTemp[GetIndex(i, j)] = new MapTileInfo(j * MAP_WIDTH + i);
        }
    }

    for (int i = 0; i < MAP_WIDTH; i++)
    {
        boardTemp[GetIndex(i, 0)]->SetTileGroup(i);
        maxIndex = i;
    }

    int row = 0;
    bool upponConnect = false;

    for (int rpw = 0; row < MAP_HEIGHT - 1;)
    {
        //���� row �¿� �� ����
        for (int i = 0; i < MAP_WIDTH - 1; i++)
        {
            //�������� 0�� ������ ���� ���� �԰� �Ը� �� �翷�� TileGroup�� ���� Group���� ����
            if (GetIntRange(0, 1) == 0)
            {
                boardTemp[GetIndex(i + 1, row)]->preTile = boardTemp[GetIndex(i, row)];
                boardTemp[GetIndex(i, row)]->nextTile = boardTemp[GetIndex(i + 1, row)];
                boardTemp[GetIndex(i, row)]->SetTileGroup(boardTemp[GetIndex(i + 1, row)]->GetTileGroup());
                boardTempArray[(i + 1) * 2][row * 2 + 1] = true;

                if (row > 0)
                {
                    //2��° �� ����  4���� Tile��� ���� ���� ���ٸ�
                    //���� 4���� �� �������� �Ѱ��� ���� �����ϰ� ���̻����� ��ġ �翷 Ȥ�� ���Ʒ� Ÿ���� �������� �������ش�.
                    if (boardTempArray[i * 2 + 1][row * 2] && boardTempArray[(i + 1) * 2 + 1][row * 2] && boardTempArray[(i + 1) * 2][(row - 1) * 2 + 1])
                    {
                        int siteTemp = GetIntRange(0, 3);
                        switch (siteTemp)
                        {
                        case 0:
                            boardTempArray[i * 2 + 1][row * 2] = false;
                            boardTemp[GetIndex(i, row - 1)]->bottomTile = nullptr;
                            boardTemp[GetIndex(i, row)]->upponTile = nullptr;
                            break;
                        case 1:
                            boardTempArray[(i + 1) * 2 + 1][row * 2] = false;
                            boardTemp[GetIndex(i + 1, row - 1)]->bottomTile = nullptr;
                            boardTemp[GetIndex(i + 1, row)]->upponTile = nullptr;
                            break;
                        case 2:
                            boardTempArray[(i + 1) * 2][(row - 1) * 2 + 1] = false;
                            boardTemp[GetIndex(i, row - 1)]->nextTile = nullptr;
                            boardTemp[GetIndex(i + 1, row - 1)]->preTile = nullptr;
                            break;
                        case 3:
                            boardTempArray[(i + 1) * 2][row * 2 + 1] = false;
                            boardTemp[GetIndex(i, row)]->nextTile = nullptr;
                            boardTemp[GetIndex(i + 1, row)]->preTile = nullptr;
                            break;
                        }
                    }
                }
            }
        }

        //���� ���� row �ʱ�ȭ ����
        for (int i = 0; i < MAP_WIDTH; i++)
        {
            if (boardTemp[GetIndex(i, row + 1)]->GetTileGroup() < 0)
            {
                boardTemp[GetIndex(i, row + 1)]->SetTileGroup(++maxIndex);
            }
        }

        //�Ʒ����� �� ����
        for (int i = 0; i < MAP_WIDTH - 1; i++)
        {
            //�������� 0�� �����ų� ���� Ÿ���� mazeGroup���� �Ʒ��� �������� ���� ������ �ʾҴٸ� �Ʒ����� �� ����
            if (GetIntRange(0, 1) == 0 || (boardTemp[GetIndex(i + 1, row)]->GetTileGroup() != boardTemp[GetIndex(i, row)]->GetTileGroup() && !upponConnect))
            {
                boardTemp[GetIndex(i, row + 1)]->upponTile = boardTemp[GetIndex(i, row)];
                boardTemp[GetIndex(i, row)]->bottomTile = boardTemp[GetIndex(i, row + 1)];
                boardTemp[GetIndex(i, row)]->SetTileGroup(boardTemp[GetIndex(i, row + 1)]->GetTileGroup());
                boardTempArray[i * 2 + 1][(row + 1) * 2] = true;
                upponConnect = true;
            }
            //Group�� ����Ǿ��ٸ� upponConnect(*�Ʒ��������� ���� �����Ǿ����� Ȯ���ϴ� bool)�� false�� �ʱ�ȭ
            if (boardTemp[GetIndex(i, row)]->GetTileGroup() != boardTemp[GetIndex(i + 1, row)]->GetTileGroup()) { upponConnect = false; }
        }
        //�ش� row�� ������ tile�� 0�� �����ų� �� tile�� ���� group�� �������� ���� �������� �ʾҴٸ� �Ʒ����� ���� ����
        if (GetIntRange(0, 1) == 0 || !upponConnect)
        {
            boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)]->upponTile = boardTemp[GetIndex(MAP_WIDTH - 1, row)];
            boardTemp[GetIndex(MAP_WIDTH - 1, row)]->bottomTile = boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)];
            boardTemp[GetIndex(MAP_WIDTH - 1, row)]->SetTileGroup(boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)]->GetTileGroup());
            boardTempArray[(MAP_WIDTH - 1) * 2 + 1][(row + 1) * 2] = true;
        }
        //�Ʒ��������� ���� �����Ǿ����� Ȯ���ϴ� bool�� false�� �ʱ�ȭ
        upponConnect = false;
        //�ٳѱ�
        row++;
    }

    //������ �� ����
    for (int i = 0; i < MAP_WIDTH - 1; i++)
    {
        //�翷 �� Ÿ���� �׷��� �ٸ��ٸ� �� ����
        if (boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->GetTileGroup() != boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->GetTileGroup())
        {
            boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->preTile = boardTemp[GetIndex(i, MAP_HEIGHT - 1)];
            boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->nextTile = boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)];
            boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->SetTileGroup(boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->GetTileGroup());
            boardTempArray[(i + 1) * 2][(MAP_HEIGHT - 1) * 2 + 1] = true;
            // �� ���� �ߴµ� 4���� �Է��ִ� *���ñ׸�2 ��Ȳ�̶�� 4���� �Ѱ��� �������� ���� �����ϰ� ������ �� �翷 Ȥ�� ���Ʒ��� Tile���� ������ ���ش�.
            if (boardTempArray[i * 2 + 1][(MAP_HEIGHT - 1) * 2] && boardTempArray[(i + 1) * 2 + 1][(MAP_HEIGHT - 1) * 2] && boardTempArray[(i + 1) * 2][((MAP_HEIGHT - 1) - 1) * 2 + 1])
            {
                int siteTemp = GetIntRange(0,3);
                switch (siteTemp)
                {
                case 0:
                    boardTempArray[i * 2 + 1][(MAP_HEIGHT - 2) * 2] = false;
                    boardTemp[GetIndex(i, MAP_HEIGHT - 2)]->bottomTile = nullptr;
                    boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->upponTile = nullptr;
                    break;
                case 1:
                    boardTempArray[(i + 1) * 2 + 1][(MAP_HEIGHT - 1) * 2] = false;
                    boardTemp[GetIndex(i + 1, MAP_HEIGHT - 2)]->bottomTile = nullptr;
                    boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->upponTile = nullptr;
                    break;
                case 2:
                    boardTempArray[(i + 1) * 2][((MAP_HEIGHT - 1) - 1) * 2 + 1] = false;
                    boardTemp[GetIndex(i, MAP_HEIGHT - 2)]->nextTile = nullptr;
                    boardTemp[GetIndex(i + 1, MAP_HEIGHT - 2)]->preTile = nullptr;
                    break;
                case 3:
                    boardTempArray[(i + 1) * 2][(MAP_HEIGHT - 1) * 2 + 1] = false;
                    boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->nextTile = nullptr;
                    boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->preTile = nullptr;
                    break;
                }
            }
        }
    }

    // �޸� ����
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            delete boardTemp[GetIndex(x, y)];
            boardTemp[GetIndex(x, y)] = nullptr;
        }
    }

    delete[] boardTemp;
    boardTemp = nullptr;

    const int outW = MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1; // ����=1
    const int outH = MAP_HEIGHT * (MAP_CHUNKHEIGHT + 1) + 1;

    for (int oy = 0; oy < outH; ++oy) {
        int by = (oy % (MAP_CHUNKHEIGHT + 1) == 0) ? 2 * (oy / (MAP_CHUNKHEIGHT + 1)) : 2 * (oy / (MAP_CHUNKHEIGHT + 1)) + 1;
        if (by < 0) by = 0; if (by >= MAP_WIDTH * 2 + 1) by = MAP_HEIGHT * 2 + 1 - 1;

        for (int ox = 0; ox < outW; ++ox) {
            int bx = (ox % (MAP_CHUNKWIDTH + 1) == 0) ? 2 * (ox / (MAP_CHUNKWIDTH + 1)) : 2 * (ox / (MAP_CHUNKWIDTH + 1)) + 1;
            if (bx < 0) bx = 0; if (bx >= MAP_WIDTH * 2 + 1) bx = MAP_WIDTH * 2;

            bool open = boardTempArray[bx][by];
            mapInfo[ox][oy] = open ? TileType::Empty : TileType::Wall;
        }
    }
}


char MapData::GetMapData(int posX, int posY)
{
    if (posX < 0 || posX >= MAP_WIDTH * (MAP_CHUNKWIDTH + 1) || posY < 0 || posY >= MAP_HEIGHT * (MAP_CHUNKHEIGHT + 1))
        return '#';

    switch (mapInfo[posX][posY])
    {
    case TileType::Empty:
        return ' ';
    case TileType::Wall:
        return '#';
    default:
        break;
    }
    return '#';
}

TileType MapData::GetMapInfo(int posX, int posY)
{
    return mapInfo[posX][posY];
}

int MapData::GetMapWidth()
{
    return MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1;
}

int MapData::GetMapHeight()
{
    return MAP_HEIGHT * (MAP_CHUNKHEIGHT + 1) + 1;
}

