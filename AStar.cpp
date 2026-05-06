/* // --- Phase 2: Environment Perception & Pathfinding ---
#include "AStar.h"
#include <SD.h>

AStar::AStar() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        gridMap[i] = 0; // Clear grid
    }
}

bool AStar::loadMapFromSD(const char* filename) {
    File mapFile = SD.open(filename, FILE_READ);
    if (!mapFile) return false;
    
    int y = 0;
    while (mapFile.available() && y < GRID_HEIGHT) {
        String line = mapFile.readStringUntil('\n');
        line.trim();
        for (int x = 0; x < GRID_WIDTH && (unsigned int)x < line.length(); x++) {
            if (line.charAt(x) == '1') {
                setObstacle(x, y);
            } else {
                clearObstacle(x, y);
            }
        }
        y++;
    }
    mapFile.close();
    return true;
}

void AStar::setObstacle(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        gridMap[y] |= (1UL << x);
    }
}

void AStar::clearObstacle(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        gridMap[y] &= ~(1UL << x);
    }
}

bool AStar::isObstacle(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return (gridMap[y] & (1UL << x)) != 0;
    }
    return true; // Out of bounds is treated as an obstacle
}

int AStar::getHeuristic(int x1, int y1, int x2, int y2) {
    // Manhattan Distance
    return abs(x1 - x2) + abs(y1 - y2);
}

void AStar::addToOpenList(int nodeIdx) {
    if (openListCount < MAX_OPEN) {
        openList[openListCount++] = nodeIdx;
    }
}

int AStar::getLowestFCostOpenNode() {
    if (openListCount == 0) return -1;
    
    int lowestIdx = 0;
    for (int i = 1; i < openListCount; i++) {
        if (nodes[openList[i]].fCost < nodes[openList[lowestIdx]].fCost) {
            lowestIdx = i;
        }
    }
    
    int nodeIdx = openList[lowestIdx];
    
    // Remove from open list
    for (int i = lowestIdx; i < openListCount - 1; i++) {
        openList[i] = openList[i + 1];
    }
    openListCount--;
    
    return nodeIdx;
}

void AStar::reconstructPath(int endNodeIdx, Coordinate* outPath, int& pathLength) {
    pathLength = 0;
    int currIdx = endNodeIdx;
    
    // Backtrack to build path array
    while (currIdx != -1 && pathLength < MAX_PATH_LENGTH) {
        outPath[pathLength].x = nodes[currIdx].x;
        outPath[pathLength].y = nodes[currIdx].y;
        pathLength++;
        currIdx = nodes[currIdx].parentIdx;
    }
    
    // Reverse array to go from start to goal
    for (int i = 0; i < pathLength / 2; i++) {
        Coordinate temp = outPath[i];
        outPath[i] = outPath[pathLength - 1 - i];
        outPath[pathLength - 1 - i] = temp;
    }
}

int AStar::findPath(int startX, int startY, int goalX, int goalY, Coordinate* outPath) {
    nodeCount = 0;
    openListCount = 0;
    
    if (isObstacle(goalX, goalY) || isObstacle(startX, startY)) {
        return 0; // No path possible
    }

    // Initialize Start Node
    nodes[nodeCount] = { (int8_t)startX, (int8_t)startY, 0, (int16_t)getHeuristic(startX, startY, goalX, goalY), 0, -1, false };
    nodes[nodeCount].fCost = nodes[nodeCount].gCost + nodes[nodeCount].hCost;
    addToOpenList(nodeCount);
    nodeCount++;

    while (openListCount > 0) {
        int currIdx = getLowestFCostOpenNode();
        
        if (nodes[currIdx].x == goalX && nodes[currIdx].y == goalY) {
            int pathLen = 0;
            reconstructPath(currIdx, outPath, pathLen);
            return pathLen;
        }
        
        nodes[currIdx].closed = true;
        
        // Check 4 neighbors (Up, Down, Left, Right)
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        
        for (int i = 0; i < 4; i++) {
            int nx = nodes[currIdx].x + dx[i];
            int ny = nodes[currIdx].y + dy[i];
            
            if (isObstacle(nx, ny)) continue;
            
            // Check if closed
            bool inClosed = false;
            for (int j = 0; j < nodeCount; j++) {
                if (nodes[j].closed && nodes[j].x == nx && nodes[j].y == ny) {
                    inClosed = true;
                    break;
                }
            }
            if (inClosed) continue;
            
            int tentative_gCost = nodes[currIdx].gCost + 1;
            
            // Check if in open list
            int openIdx = -1;
            for (int j = 0; j < openListCount; j++) {
                if (nodes[openList[j]].x == nx && nodes[openList[j]].y == ny) {
                    openIdx = openList[j];
                    break;
                }
            }
            
            if (openIdx == -1) {
                // Discover a new node
                if (nodeCount >= MAX_NODES) break; // Memory limit reached
                
                nodes[nodeCount] = { (int8_t)nx, (int8_t)ny, (int16_t)tentative_gCost, (int16_t)getHeuristic(nx, ny, goalX, goalY), 0, (int16_t)currIdx, false };
                nodes[nodeCount].fCost = nodes[nodeCount].gCost + nodes[nodeCount].hCost;
                addToOpenList(nodeCount);
                nodeCount++;
            } else if (tentative_gCost < nodes[openIdx].gCost) {
                // Better path found
                nodes[openIdx].parentIdx = currIdx;
                nodes[openIdx].gCost = tentative_gCost;
                nodes[openIdx].fCost = nodes[openIdx].gCost + nodes[openIdx].hCost;
            }
        }
    }
    
    return 0; // No path found
}
*/
