#include "../../headers/algorithms/GreedyBestFirstSearch.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/ManhattanDistance.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class GreedyCompare {
public:
    bool operator() (Node node1, Node node2) {
        StateManager stateManager;
        short numOfTiles = stateManager.getNumberOfTiles(node1.state);
        ManhattanDistance heuristic(numOfTiles);
        int h1 = heuristic.calculate(node1.state);
        int h2 = heuristic.calculate(node2.state);
        if (h1 != h2)
            return h1 > h2;
        return node1.index < node2.index;
    };
};

using OpenSet = priority_queue<Node, vector<Node>, GreedyCompare>;

Node buildGBFSNode(PackedState state, int cost, int index) {
    Node node;
    node.state = state;
    node.cost = cost;
    node.index = index;
    return node;
}

Node buildGBFSInitialNode(PackedState state) {
    return buildGBFSNode(state, 0, 0);
}

Result GreedyBestFirstSearch :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager;

    ManhattanDistance heuristic(stateManager.getNumberOfTiles(initialState));
    int index = 0;

    result.startCountingTime();

    result.setInitialHeuristicValue(heuristic.calculate(initialState));
    result.increaseTotalHeuristicValue(heuristic.calculate(initialState));
    open.push(buildGBFSInitialNode(initialState));

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
                open.push(buildGBFSNode(successorState, currentNode.cost+1, ++index));
            } 
        }
        
    }
    return result;
}
