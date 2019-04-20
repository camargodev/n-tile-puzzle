#include "../../headers/algorithms/BFS.h"
#include "../../headers/State.h"
#include "../../headers/Node.h"
#include "../../headers/ManhattanDistance.h"
#include "../../headers/StateManager.h"

using namespace std;
using OpenSet = deque<Node>;

Result BFS :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager;

    result.startCountingTime();

    if (stateManager.isGoalState(initialState)) {
        result.stopCountingTime();
        return result;
    }

    Node initialNode;
    initialNode.cost = 0;
    initialNode.state.value = initialState;
    initialNode.state.heuristic = stateManager.calculateHeuristic(initialState);
    
    open.push_back(initialNode);
    closed.insert(closed.begin(), initialState);

    result.setInitialHeuristicValue(initialNode.state.heuristic);

    while (!open.empty()) {
        Node currentNode = open.front();
        open.pop_front();
        result.increaseExpandedNodes();
        for (auto successorState : stateManager.produceNextStates(currentNode.state)) {
            Node successorNode;
            successorNode.cost = currentNode.cost + 1;
            successorNode.state = successorState;
            if (stateManager.isGoalState(successorState.value)) {
                result.setOptimalSolutionLenght(successorNode.cost);
                result.stopCountingTime();
                return result;
            }
            if (closed.find(successorState.value) == closed.end()) {
                closed.insert(closed.begin(), successorState.value);
                open.push_back(successorNode);
            }
        }
    }
    return result;
}