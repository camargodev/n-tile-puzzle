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
        int h1 = node1.state.heuristic;
        int h2 = node2.state.heuristic;
        if (h1 != h2)
            return h1 > h2;
        return node1.index < node2.index;
    };
};

using OpenSet = priority_queue<Node, vector<Node>, GreedyCompare>;

Node buildGBFSNode(State state, int cost, int index) {
    Node node;
    node.state = state;
    node.cost = cost;
    node.index = index;
    return node;
}

Node buildGBFSInitialNode(State state) {
    return buildGBFSNode(state, 0, 0);
}

Result GreedyBestFirstSearch :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager;

    int index = 0;

    result.startCountingTime();

    State initial;
    initial.value = initialState;
    initial.heuristic = stateManager.calculateHeuristic(initialState);
    Node initialNode = buildGBFSInitialNode(initial);
    result.setInitialHeuristicValue(initialNode.state.heuristic);
    result.increaseTotalHeuristicValue(initialNode.state.heuristic);
    open.push(initialNode);

    while (!open.empty()) {
        Node currentNode = open.top();
        open.pop();
       
        if (closed.find(currentNode.state.value) == closed.end()) {
            
            closed.insert(closed.begin(), currentNode.state.value);
            if (stateManager.isGoalState(currentNode.state.value)) {
                result.setOptimalSolutionLenght(currentNode.cost);
                result.stopCountingTime();
                return result;
            }

            result.increaseExpandedNodes();
            
            for (auto successorState : stateManager.produceNextStates(currentNode.state)) {
                result.increaseTotalHeuristicValue(successorState.heuristic);
                open.push(buildGBFSNode(successorState, currentNode.cost+1, ++index));
            } 
        }
        
    }
    return result;
}