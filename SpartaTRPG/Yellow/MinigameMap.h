#pragma once

#include <vector>
#include <string>
#include <utility>
#include <random>

class MinigameMap {
public:
    struct Map {
        int rows = 0;                        // 세로 (긴 변)
        int cols = 0;                        // 가로 (짧은 변)
        std::vector<std::string> grid;       
        std::pair<int, int> start{ 0,0 };       // (row, col)
        std::pair<int, int> goal{ 0,0 };        // (row, col)
        char at(int r, int c) const { return grid[r][c]; }
    };

    // ctor: shortSide = 짧은 변 길이 (이 값이 cols가 되고 rows = 2 * shortSide)
    // seed = 0 : nondeterministic seed from clock
    // maxAttempts: how many randomized attempts before fallback deterministic
    MinigameMap(int shortSide, unsigned seed = 0u, int maxAttempts = 500);

    // Generate the map. Returns true on success (including fallback).
    bool generate();

    // Access generated map
    const Map& getMap() const;
    

    // Optional setters
    void setSeed(unsigned seed);
    void setMaxAttempts(int attempts);

    Map m_map;
    unsigned m_seed;
    int m_maxAttempts;

    // helpers
    static bool inBounds(int r, int c, int rows, int cols);
    static bool canPlaceNext(int nr, int nc,
        const std::vector<std::vector<unsigned char>>& visited,
        int curR, int curC,
        const std::pair<int, int>& goal);
    static bool dfsBuild(int r, int c,
        std::vector<std::vector<unsigned char>>& visited,
        const std::pair<int, int>& goal,
        std::mt19937& rng,
        std::vector<std::pair<int, int>>& outPath);
};

