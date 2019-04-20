#include "../../headers/algorithms/IDFS.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

IDFS :: IDFS(){
    this->result = new Result;
}

IDFS :: ~IDFS(){
    delete this->result;
}

Solution IDFS :: depthLimitedSearch(PackedState state, PackedState parent, int depthLimit){
    Solution solution;
    StateManager stateManager;

    if (stateManager.isGoalState(state)){
        solution.isSolution = true;
        solution.cost = 0;
        return solution;
    }
    
    if(depthLimit > 0){
        this->result->increaseExpandedNodes();
        for (auto successorState : stateManager.produceNextPackedStates(state)) {
            if(successorState != parent){
                solution = depthLimitedSearch(successorState, state, depthLimit-1);
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
    ManhattanDistance* heuristic = new ManhattanDistance();
    heuristic->setNumberOfTiles(stateManager.getNumberOfTiles(initialState));

    this->result->startCountingTime();
    this->result->setInitialHeuristicValue(heuristic->calculate(initialState));

    delete heuristic;
    
    int depthLimit = 0;
    Solution solution;

    while(true){
        solution = depthLimitedSearch(initialState, -1, depthLimit);
        if (solution.isSolution == true) {
            result->setOptimalSolutionLenght(solution.cost);
            result->stopCountingTime();
            return *(this->result);
        }
        depthLimit++;
    }

}