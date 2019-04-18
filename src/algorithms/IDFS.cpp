#include "../../headers/algorithms/IDFS.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

Solution IDFS :: depthLimitedSearch(PackedState state, PackedState parent, int depthLimit, Result* result, ManhattanDistance* heuristic){
    Solution solution;
    StateManager stateManager;

    if (stateManager.isGoalState(state)){
        solution.isSolution = true;
        solution.cost = 0;
        return solution;
    }
    
    if(depthLimit > 0){
        result->increaseExpandedNodes();
        for (auto successorState : stateManager.produceNextStates(state)) {
            if(successorState != parent){
                solution = depthLimitedSearch(successorState, state, depthLimit-1, result, heuristic);
                if(solution.isSolution == true){
                    solution.cost++;
                    return solution;
                }
            }            
        }
    }  

    solution.isSolution = false;
    return solution;
}

Result IDFS :: execute(PackedState initialState){

    StateManager stateManager;
    ManhattanDistance* heuristic = new ManhattanDistance(stateManager.getNumberOfTiles(initialState));

    Result* result = new Result;
    result->startCountingTime();
    result->setInitialHeuristicValue(heuristic->calculate(initialState));
    
    int depthLimit = 0;
    Solution solution;

    while(true){
        solution = depthLimitedSearch(initialState, -1, depthLimit, result, heuristic);
        if (solution.isSolution == true) {
            result->setOptimalSolutionLenght(solution.cost);
            result->stopCountingTime();
            return *result;
        }
        depthLimit++;
    }

}