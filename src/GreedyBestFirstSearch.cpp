#include "../headers/GreedyBestFirstSearch.h"
#include "../headers/State.h"
#include "../headers/Node.h"
#include "../headers/ManhattanDistance.h"
#include "../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class GreedyCompare {
public:
    bool operator() (Node node1, Node node2) {
        ManhattanDistance heuristic(node1.numberOfTiles);
        int h1 = heuristic.calculate(node1.state);
        int h2 = heuristic.calculate(node2.state);
        if (h1 != h2)
            return h1 > h2;
        return node1.index < node2.index;
    };
};

using OpenSet = priority_queue<Node, vector<Node>, GreedyCompare>;

Node buildNode(PackedState state, int cost, int index, short numOfTiles) {
    Node node;
    node.state = state;
    node.numberOfTiles = numOfTiles;
    node.cost = cost;
    node.index = index;
    return node;
}

Node buildInitialNode(PackedState state, int numOfTiles) {
    return buildNode(state, 0, 0, numOfTiles);
}

GreedyBestFirstSearch :: GreedyBestFirstSearch(int numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
}

Result GreedyBestFirstSearch :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager(numberOfTiles);

    ManhattanDistance heuristic(stateManager.getNumberOfTiles());
    int index = 0;

    result.startCountingTime();

    result.setInitialHeuristicValue(heuristic.calculate(initialState));
    open.push(buildInitialNode(initialState, numberOfTiles));

    while (!open.empty()) {
        Node currentNode = open.top();
        open.pop();
       
        if (closed.find(currentNode.state) == closed.end()) {
            
            closed.insert(closed.begin(), currentNode.state);
            if (stateManager.isGoalState(currentNode.state)) {
                result.setOptimalSolutionLenght(currentNode.cost);
                result.stopCountingTime();
                return result;
            }

            result.increaseExpandedNodes();
            result.increaseTotalHeuristicValue(heuristic.calculate(currentNode.state));
            
            for (auto successorState : stateManager.produceNextStates(currentNode.state)) {
                open.push(buildNode(successorState, currentNode.cost+1, ++index, numberOfTiles));
            } 
        }
        
    }
    return result;
}
