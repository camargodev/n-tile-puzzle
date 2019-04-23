#include "../../headers/algorithms/IDAStar.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/ManhattanDistance.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

Node IDAStar :: buildNode(State state, int cost) {
    Node node;
    node.state = state;
    node.cost = cost;
    node.index = -1;
    return node;
}

Node IDAStar :: buildInitialNode(State state) {
    return IDAStar::buildNode(state, 0);
}

int IDAStar :: f(Node node){
    return node.cost + node.state.heuristic;
}

IDAStar :: IDAStar(){
    this->result = new Result;
}

IDAStar :: ~IDAStar(){
    delete this->result;
}

IDAStar::Solution IDAStar :: recursiveSearch(Node currentNode, PackedState parent, int fLimit){
    IDAStar::Solution solution;
    StateManager stateManager;
    int val = f(currentNode);

    if(val > fLimit){
        solution.limit = val;
        solution.isSolution = false;
        return solution;
    }

    if(stateManager.isGoalState(currentNode.state.value)){
        solution.isSolution = true;
        solution.cost = currentNode.cost;
        return solution;
    }

    unsigned long long int nextLimit = ULLONG_MAX;

    this->result->increaseExpandedNodes();

    for (auto successorState : stateManager.produceNextPackedStates(currentNode.state.value)) {
        if(successorState != parent){
            State sucState;
            sucState.heuristic = stateManager.calculateHeuristic(successorState);
            this->result->increaseTotalHeuristicValue(sucState.heuristic);
            if(sucState.heuristic < ULLONG_MAX){
                sucState.value = successorState;
                Node sucNode = IDAStar::buildNode(sucState, currentNode.cost+1);
                solution = recursiveSearch(sucNode, currentNode.state.value, fLimit);
                if(solution.isSolution == true){
                    return solution;
                }
                nextLimit = min(nextLimit, solution.limit);
            }
        }            
    }

    solution.limit = nextLimit;
    solution.isSolution = false;
    return solution;
}

Result IDAStar :: execute(PackedState initialState){
    StateManager stateManager;
    unsigned long long int fLimit = stateManager.calculateHeuristic(initialState);
    
    this->result->startCountingTime();
    this->result->setInitialHeuristicValue(fLimit);
    this->result->increaseTotalHeuristicValue(fLimit);

    State initial;
    initial.value = initialState;
    initial.heuristic = fLimit;
    Node initialNode = IDAStar::buildInitialNode(initial);
    
    IDAStar::Solution solution;

    while(fLimit != ULLONG_MAX){
        solution = recursiveSearch(initialNode, 0, fLimit);
        if(solution.isSolution == true){
            this->result->setOptimalSolutionLenght(solution.cost);
            this->result->stopCountingTime();
            return *(this->result);
        }
        fLimit = solution.limit;
    }

    this->result->setOptimalSolutionLenght(INT_MAX);
    return *(this->result);
}