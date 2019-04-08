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
 
using namespace std;

int main()
{   
    UnpackedState state = {{8, 3, 5}, {7, 2, 6}, {0, 4, 1}};
    int numberOfTiles = state.size();

    StateManager stateManager(numberOfTiles);
    GreedyBestFirstSearch gbfs(numberOfTiles);

    PackedState initialState = stateManager.pack(state);

    Result result = gbfs.execute(initialState);
    result.printResult();

    cout << "\n\n";
    return 0;
    
}


