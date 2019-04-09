#include "../../headers/algorithms/AStar.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/ManhattanDistance.h"
#include "../../headers/StateManager.h"
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class AStarCompare {
public:
    bool operator() (Node node1, Node node2) {
        StateManager stateManager;
        short numOfTiles = stateManager.getNumberOfTiles(node1.state);
        ManhattanDistance heuristic(numOfTiles);
        int f1 = heuristic.calculate(node1.state);
        int f2 = heuristic.calculate(node2.state);
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

Node buildNode(PackedState state, int cost, int index) {
    Node node;
    node.state = state;
    node.cost = cost;
    node.index = index;
    return node;
}

Node buildInitialNode(PackedState state) {
    return buildNode(state, 0, 0);
}

Result AStar :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager;

    ManhattanDistance heuristic(stateManager.getNumberOfTiles(initialState));
    int index = 0;

    result.startCountingTime();

    result.setInitialHeuristicValue(heuristic.calculate(initialState));
    open.push(buildInitialNode(initialState));

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
                open.push(buildNode(successorState, currentNode.cost+1, ++index));
            } 
        }
        
    }
    return result;
}
