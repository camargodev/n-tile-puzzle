#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
#include "headers/Node.h"
#include "headers/Result.h"
#include "headers/BFS.h"
#include "headers/GreedyBestFirstSearch.h"
#include "headers/AStar.h"
 
using namespace std;

int main()
{   
 //   UnpackedState state = {{8, 3, 5}, {7, 2, 6}, {0, 4, 1}};
    UnpackedState state = {{3, 0, 8}, {7, 5, 2}, {1, 6, 4}};
    
    short numberOfTiles = state.size();

    StateManager stateManager(numberOfTiles);
    AStar gbfs(numberOfTiles);

    PackedState initialState = stateManager.pack(state);

    Result result = gbfs.execute(initialState);
    result.printResult();

    cout << "\n\n";
    return 0;
    
}


