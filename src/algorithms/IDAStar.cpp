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
    //cout << "\nOPA101\n";
    int val = f(currentNode);

    //cout << "\nOPA102\n";
    if(val > fLimit){
        solution.limit = val;
        solution.isSolution = false;
        return solution;
    }

    //cout << "\nOPA103\n";
    if(stateManager.isGoalState(currentNode.state.value)){
        solution.isSolution = true;
        solution.cost = currentNode.cost;
        return solution;
    }

    unsigned long long int nextLimit = ULLONG_MAX;

    //cout << "\nOPA104\n";
    this->result->increaseExpandedNodes();
    //cout << "\nOPA105\n";
    this->result->increaseTotalHeuristicValue(currentNode.state.heuristic);
    //cout << "\nOPA106\n";
    for (auto successorState : stateManager.produceNextPackedStates(currentNode.state.value)) {
        if(successorState != parent){
            State sucState;
            sucState.heuristic = stateManager.calculateHeuristic(successorState);
            //cout << "\nOPA107\n";
            if(sucState.heuristic < ULLONG_MAX){
                //cout << "\nOPA108\n";
                sucState.value = successorState;
                //cout << "\nOPA109\n";
                Node sucNode = IDAStar::buildNode(sucState, currentNode.cost+1);
                //cout << "\nOPA110\n";
                solution = recursiveSearch(sucNode, currentNode.state.value, fLimit);
                //cout << "\nOPA111\n";
                if(solution.isSolution == true){
                    return solution;
                }
                //cout << "\nOPA112\n";
                nextLimit = min(nextLimit, solution.limit);
                //cout << "\nOPA113\n";
            }
        }            
    }

    solution.limit = nextLimit;
    solution.isSolution = false;
    return solution;
}

Result IDAStar :: execute(PackedState initialState){
    //cout << "\nOPA1\n";
    StateManager stateManager;
    //cout << "\nOPA2\n";
    unsigned long long int fLimit = stateManager.calculateHeuristic(initialState);
    //cout << "\nOPA3\n";
    
    this->result->startCountingTime();
    //cout << "\nOPA4\n";
    this->result->setInitialHeuristicValue(fLimit);
    //cout << "\nOPA5\n";
    this->result->increaseTotalHeuristicValue(fLimit);
    //cout << "\nOPA6\n";

    State initial;
    //cout << "\nOPA7\n";
    initial.value = initialState;
    //cout << "\nOPA8\n";
    initial.heuristic = fLimit;
    //cout << "\nOPA9\n";
    Node initialNode = IDAStar::buildInitialNode(initial);
    //cout << "\nOPA10\n";
    
    IDAStar::Solution solution;

    while(fLimit < ULLONG_MAX){
        //cout << "\nOPA11\n";
        solution = recursiveSearch(initialNode, 0, fLimit);
       //cout << "\nOPA12\n";
        if(solution.isSolution == true){
            //cout << "\nOPA13\n";
            this->result->setOptimalSolutionLenght(solution.cost);
            //cout << "\nOPA14\n";
            this->result->stopCountingTime();
            //cout << "\nOPA15\n";
            return *(this->result);
        }
        fLimit = solution.limit;
    }

    //cout << "\nOPA2\n";
    this->result->setOptimalSolutionLenght(INT_MAX);
    return *(this->result);
}