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
        //현재 row 좌우 길 생성
        for (int i = 0; i < MAP_WIDTH - 1; i++)
        {
            //랜덤으로 0이 나오면 옆의 벽을 뚤고 뚤린 벽 양옆의 TileGroup을 같은 Group으로 변경
            if (GetIntRange(0, 1) == 0)
            {
                boardTemp[GetIndex(i + 1, row)]->preTile = boardTemp[GetIndex(i, row)];
                boardTemp[GetIndex(i, row)]->nextTile = boardTemp[GetIndex(i + 1, row)];
                boardTemp[GetIndex(i, row)]->SetTileGroup(boardTemp[GetIndex(i + 1, row)]->GetTileGroup());
                boardTempArray[(i + 1) * 2][row * 2 + 1] = true;

                if (row > 0)
                {
                    //2번째 줄 부터  4개의 Tile모두 서로 벽이 없다면
                    //벽을 4방향 중 랜덤으로 한곳에 벽을 생성하고 벽이생성된 위치 양옆 혹은 위아래 타일의 연결점을 삭제해준다.
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

        //다음 줄의 row 초기화 세팅
        for (int i = 0; i < MAP_WIDTH; i++)
        {
            if (boardTemp[GetIndex(i, row + 1)]->GetTileGroup() < 0)
            {
                boardTemp[GetIndex(i, row + 1)]->SetTileGroup(++maxIndex);
            }
        }

        //아래방향 길 생성
        for (int i = 0; i < MAP_WIDTH - 1; i++)
        {
            //랜덤으로 0이 나오거나 지금 타일의 mazeGroup에서 아래로 내려오는 길을 만들지 않았다면 아래방향 길 생성
            if (GetIntRange(0, 1) == 0 || (boardTemp[GetIndex(i + 1, row)]->GetTileGroup() != boardTemp[GetIndex(i, row)]->GetTileGroup() && !upponConnect))
            {
                boardTemp[GetIndex(i, row + 1)]->upponTile = boardTemp[GetIndex(i, row)];
                boardTemp[GetIndex(i, row)]->bottomTile = boardTemp[GetIndex(i, row + 1)];
                boardTemp[GetIndex(i, row)]->SetTileGroup(boardTemp[GetIndex(i, row + 1)]->GetTileGroup());
                boardTempArray[i * 2 + 1][(row + 1) * 2] = true;
                upponConnect = true;
            }
            //Group이 변경되었다면 upponConnect(*아래방향으로 길이 생성되엇는지 확인하는 bool)을 false로 초기화
            if (boardTemp[GetIndex(i, row)]->GetTileGroup() != boardTemp[GetIndex(i + 1, row)]->GetTileGroup()) { upponConnect = false; }
        }
        //해당 row의 마지막 tile이 0이 나오거나 이 tile이 속한 group에 내려오는 길이 생성되지 않았다면 아래방향 길을 생성
        if (GetIntRange(0, 1) == 0 || !upponConnect)
        {
            boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)]->upponTile = boardTemp[GetIndex(MAP_WIDTH - 1, row)];
            boardTemp[GetIndex(MAP_WIDTH - 1, row)]->bottomTile = boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)];
            boardTemp[GetIndex(MAP_WIDTH - 1, row)]->SetTileGroup(boardTemp[GetIndex(MAP_WIDTH - 1, row + 1)]->GetTileGroup());
            boardTempArray[(MAP_WIDTH - 1) * 2 + 1][(row + 1) * 2] = true;
        }
        //아래방향으로 길이 생성되엇는지 확인하는 bool을 false로 초기화
        upponConnect = false;
        //줄넘김
        row++;
    }

    //마지막 줄 세팅
    for (int i = 0; i < MAP_WIDTH - 1; i++)
    {
        //양옆 두 타일의 그룹이 다르다면 길 생성
        if (boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->GetTileGroup() != boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->GetTileGroup())
        {
            boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->preTile = boardTemp[GetIndex(i, MAP_HEIGHT - 1)];
            boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->nextTile = boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)];
            boardTemp[GetIndex(i, MAP_HEIGHT - 1)]->SetTileGroup(boardTemp[GetIndex(i + 1, MAP_HEIGHT - 1)]->GetTileGroup());
            boardTempArray[(i + 1) * 2][(MAP_HEIGHT - 1) * 2 + 1] = true;
            // 길 생성 했는데 4방향 뚤려있는 *예시그림2 상황이라면 4곳중 한곳을 랜덤으로 벽을 생성하고 생성된 벽 양옆 혹은 위아래의 Tile간의 연결을 없앤다.
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

    // 메모리 해제
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

    const int outW = MAP_WIDTH * (MAP_CHUNKWIDTH + 1) + 1; // 벽폭=1
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

