#include "../../headers/algorithms/AStar.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/ManhattanDistance.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct AStarCompare {
    bool operator() (Node node1, Node node2) {
        int f1 = node1.state.heuristic;
        int f2 = node2.state.heuristic;
        int h1 = f1 + node1.cost;
        int h2 = f2 + node2.cost;
        if (h1 != h2)
            return h1 > h2;
        if (f1 != f2)
            return f1 > f2;
        return node1.index < node2.index;
    };
};

using OpenSet = priority_queue<Node, vector<Node>, AStarCompare>;

Node buildNode(State state, int cost, int index) {
    Node node;
    node.state = state;
    node.cost = cost;
    node.index = index;
    return node;
}

Node buildInitialNode(State state) {
    return buildNode(state, 0, 0);
}

Result AStar :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager;

    int index = 0;

    result.startCountingTime();

    State initial;
    initial.value = initialState;
    initial.heuristic = stateManager.calculateHeuristic(initialState);
    Node initialNode = buildInitialNode(initial);
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
            result.increaseTotalHeuristicValue(currentNode.state.heuristic);
            
            for (auto successorState : stateManager.produceNextStates(currentNode.state)) {
                //result.increaseTotalHeuristicValue(successorState.heuristic);
                //result.increaseGeneratedNodes();
                open.push(buildNode(successorState, currentNode.cost+1, ++index));
            } 
        }
        
    }
    return result;
}
