#include "../headers/BFS.h"
#include "../headers/State.h"
#include "../headers/Node.h"
#include "../headers/ManhattanDistance.h"
#include "../headers/StateManager.h"

using namespace std;
using OpenSet = deque<Node>;

BFS :: BFS(int numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
}

Result BFS :: execute(PackedState initialState) {
    Result result;
    OpenSet open;
    ClosedSet closed;
    StateManager stateManager(numberOfTiles);

    ManhattanDistance heuristic(stateManager.getNumberOfTiles());

    result.startCountingTime();

    result.setInitialHeuristicValue(heuristic.calculate(initialState));
    if (stateManager.isGoalState(initialState)) {
        result.stopCountingTime();
        return result;
    }

    Node initialNode;
    initialNode.cost = 0;
    initialNode.state = initialState;
    open.push_back(initialNode);
    closed.insert(closed.begin(), initialState);

    while (!open.empty()) {
        Node currentNode = open.front();
        open.pop_front();
        result.increaseExpandedNodes();
        result.increaseTotalHeuristicValue(heuristic.calculate(currentNode.state));
        for (auto successorState : stateManager.produceNextStates(currentNode.state)) {
            Node successorNode;
            successorNode.cost = currentNode.cost + 1;
            successorNode.state = successorState;
            if (stateManager.isGoalState(successorState)) {
                result.setOptimalSolutionLenght(successorNode.cost);
                result.stopCountingTime();
                return result;
            }
            if (closed.find(successorState) == closed.end()) {
                closed.insert(closed.begin(), successorState);
                open.push_back(successorNode);
            }
        }
    }
    return result;
}