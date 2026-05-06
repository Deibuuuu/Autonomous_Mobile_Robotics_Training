/* // --- Phase 3: A* Pathfinding ---
#pragma once
#include <Arduino.h>

#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define MAX_PATH_LENGTH 32

struct Coordinate {
    int8_t x;
    int8_t y;
};

class AStar {
public:
    AStar();
    
    // Grid map: 32 rows, each row is a 32-bit integer. 1 bit per cell.
    // 0 = empty, 1 = obstacle. Total memory footprint = 128 bytes.
    uint32_t gridMap[GRID_HEIGHT]; 

    void setObstacle(int x, int y);
    void clearObstacle(int x, int y);
    bool isObstacle(int x, int y);
    
    // Reads a 32x32 map.txt file from SD card where '1' is obstacle, '0' is empty.
    bool loadMapFromSD(const char* filename);

    // Runs A* and populates outPath. Returns length of the path.
    int findPath(int startX, int startY, int goalX, int goalY, Coordinate* outPath);

private:
    struct Node {
        int8_t x, y;
        int16_t gCost;
        int16_t hCost;
        int16_t fCost;
        int16_t parentIdx;
        bool closed;
    };

    // Statically allocated structures to prevent heap fragmentation on AVR
    #define MAX_NODES 128
    #define MAX_OPEN 64

    Node nodes[MAX_NODES]; 
    int nodeCount;
    
    int openList[MAX_OPEN];
    int openListCount;

    int getHeuristic(int x1, int y1, int x2, int y2);
    void addToOpenList(int nodeIdx);
    int getLowestFCostOpenNode();
    void reconstructPath(int endNodeIdx, Coordinate* outPath, int& pathLength);
};
*/
