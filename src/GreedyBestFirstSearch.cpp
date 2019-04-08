#include "../headers/GreedyBestFirstSearch.h"
#include "../headers/State.h"
#include "../headers/Node.h"
#include "../headers/ManhattanDistance.h"
#include "../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int numOfTiles;

class GreedyCompare {
public:
    bool operator() (Node node1, Node node2) {
        ManhattanDistance heuristic(numOfTiles);
        int h1 = heuristic.calculate(node1.getState());
        int h2 = heuristic.calculate(node2.getState());
        if (h1 != h2)
            return h1 > h2;
        return node1.getIndex() < node2.getIndex();
    };
};

using OpenSet = priority_queue<Node, vector<Node>, GreedyCompare>;

GreedyBestFirstSearch :: GreedyBestFirstSearch(int numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
    numOfTiles = this->numberOfTiles;
}

Result GreedyBestFirstSearch :: execute(PackedState initialState) {
    Result result;
    priority_queue<Node, vector<Node>, GreedyCompare> open;
    ClosedSet closed;
    StateManager stateManager(numberOfTiles);

    ManhattanDistance heuristic(stateManager.getNumberOfTiles());
    int order = 0;

    result.startCountingTime();

    result.setInitialHeuristicValue(heuristic.calculate(initialState));
    open.push(Node(initialState, 0, order++));

    while (!open.empty()) {
        Node currentNode = open.top();
        open.pop();
       
        if (closed.find(currentNode.getState()) == closed.end()) {
            
            closed.insert(closed.begin(), currentNode.getState());
            if (stateManager.isGoalState(currentNode.getState())) {
                result.setOptimalSolutionLenght(currentNode.getCost());
                result.stopCountingTime();
                return result;
            }

            result.increaseExpandedNodes();
            result.increaseTotalHeuristicValue(heuristic.calculate(currentNode.getState()));
            
            for (auto successorState : stateManager.produceNextStates(currentNode.getState())) {
                Node successorNode = Node(successorState, currentNode.getCost() + 1, order++);
                open.push(successorNode);
            } 
        }
        
    }
    return result;
}