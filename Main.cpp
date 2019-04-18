#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <deque>
#include <math.h>
#include <unordered_set>
#include <algorithm>
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
#include "headers/Node.h"
#include "headers/Result.h"
#include "headers/Input.h"
#include "headers/Input.h"
#include "headers/algorithms/BFS.h"
#include "headers/algorithms/GreedyBestFirstSearch.h"
#include "headers/algorithms/AStar.h"
 
using namespace std;

Result processAlgorithm(int algorithmId, PackedState initialState) {
    switch (algorithmId) {
        case InputReader::BFS_ID:
            return BFS().execute(initialState);
        case InputReader::GREEDY_ID:
            return GreedyBestFirstSearch().execute(initialState);
        case InputReader::ASTAR_ID:
            return AStar().execute(initialState);
    }
}

int main(int argc, char** argv)
{   
    StateManager manager;
    InputReader reader;
    Input input = reader.parseInput(argc, argv);
    for (auto unpackedState : input.states) {
        PackedState state = manager.pack(unpackedState);
        Result result = processAlgorithm(input.algorithm, state);
        result.printResult(); 
    }
    return 0;
    
}


