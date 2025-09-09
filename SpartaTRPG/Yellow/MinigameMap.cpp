#include "MinigameMap.h"

#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

MinigameMap::MinigameMap(int shortSide, unsigned seed, int maxAttempts)
    : m_seed(seed), m_maxAttempts(maxAttempts)
{
    // shortSide는 '짧은 변' 길이 (가로)
    m_map.cols = std::max(2, shortSide); // 가로 (짧은 변) 최소 2
    m_map.rows = m_map.cols * 3;         // 세로 = 2 * 짧은변 (긴 변)
    m_map.grid.assign(m_map.rows, std::string(m_map.cols, 'X'));
    // start/goal will be set in generate()
}

bool MinigameMap::inBounds(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

bool MinigameMap::canPlaceNext(int nr, int nc,
    const std::vector<std::vector<unsigned char>>& visited,
    int curR, int curC,
    const std::pair<int, int>& goal)
{
    int rows = (int)visited.size();
    int cols = (int)visited[0].size();
    if (!inBounds(nr, nc, rows, cols)) return false;
    if (visited[nr][nc] != 0) return false;
    // disallow entering bottom row except at goal
    if (nr == rows - 1 && !(nr == goal.first && nc == goal.second)) return false;

    const int dr[4] = { -1,1,0,0 };
    const int dc[4] = { 0,0,-1,1 };
    int visitedCount = 0;
    bool hasCurNeighbor = false;
    for (int k = 0; k < 4; ++k) {
        int ar = nr + dr[k], ac = nc + dc[k];
        if (!inBounds(ar, ac, rows, cols)) continue;
        if (visited[ar][ac] != 0) {
            ++visitedCount;
            if (ar == curR && ac == curC) hasCurNeighbor = true;
            if (visitedCount > 1) return false; // would create branch/cycle
        }
    }
    return (visitedCount == 1 && hasCurNeighbor);
}

bool MinigameMap::dfsBuild(int r, int c,
    std::vector<std::vector<unsigned char>>& visited,
    const std::pair<int, int>& goal,
    std::mt19937& rng,
    std::vector<std::pair<int, int>>& outPath)
{
    if (std::make_pair(r, c) == goal) {
        outPath.push_back({ r,c });
        return true;
    }

    array<pair<int, int>, 4> moves = { pair<int,int>{-1,0}, {1,0}, {0,-1}, {0,1} };
    shuffle(moves.begin(), moves.end(), rng);

    for (auto mv : moves) {
        int nr = r + mv.first;
        int nc = c + mv.second;
        if (!inBounds(nr, nc, (int)visited.size(), (int)visited[0].size())) continue;
        if (!canPlaceNext(nr, nc, visited, r, c, goal)) continue;
        visited[nr][nc] = 1;
        if (dfsBuild(nr, nc, visited, goal, rng, outPath)) {
            outPath.push_back({ r,c });
            return true;
        }
        visited[nr][nc] = 0; // backtrack
    }
    return false;
}

bool MinigameMap::generate() {
    const int rows = m_map.rows;
    const int cols = m_map.cols;

    // prepare seed
    unsigned useSeed = m_seed ? m_seed
        : (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 masterRng(useSeed);
    std::uniform_int_distribution<int> distW(0, cols - 1);

    // pick start on top row (row=0), goal on bottom row (row=rows-1)
    m_map.start = { 0, distW(masterRng) };
    m_map.goal = { rows - 1, distW(masterRng) };

    // attempts with randomized DFS/backtracking
    for (int attempt = 0; attempt < m_maxAttempts; ++attempt) {
        std::vector<std::vector<unsigned char>> visited(rows, std::vector<unsigned char>(cols, 0));
        visited[m_map.start.first][m_map.start.second] = 1;

        std::mt19937 rng(masterRng()); // different state per attempt
        std::vector<std::pair<int, int>> path;
        bool ok = dfsBuild(m_map.start.first, m_map.start.second, visited, m_map.goal, rng, path);
        if (ok) {
            // fill grid from visited
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    m_map.grid[r][c] = visited[r][c] ? '.' : 'X';
                }
            }
            m_map.grid[m_map.start.first][m_map.start.second] = 'S';
            m_map.grid[m_map.goal.first][m_map.goal.second] = 'G';
            return true;
        }
        // tweak masterRng state to change next attempt
        masterRng.seed(masterRng() ^ (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    // fallback deterministic unique path: straight down from start then across last row to goal
    for (int r = 0; r < rows; ++r) m_map.grid[r].assign(cols, 'X');
    int cr = m_map.start.first, cc = m_map.start.second;
    m_map.grid[cr][cc] = 'S';
    while (cr < rows - 1) {
        ++cr;
        m_map.grid[cr][cc] = '.';
    }
    while (cc < m_map.goal.second) m_map.grid[rows - 1][++cc] = '.';
    while (cc > m_map.goal.second) m_map.grid[rows - 1][--cc] = '.';
    m_map.grid[m_map.start.first][m_map.start.second] = 'S';
    m_map.grid[m_map.goal.first][m_map.goal.second] = 'G';
    return true; // fallback considered success
}

const MinigameMap::Map& MinigameMap::getMap() const {
    return m_map;
}


void MinigameMap::setSeed(unsigned seed) { m_seed = seed; }
void MinigameMap::setMaxAttempts(int attempts) { m_maxAttempts = attempts; }
