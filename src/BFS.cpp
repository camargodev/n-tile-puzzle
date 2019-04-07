#include "../headers/BFS.h"
#include "../headers/State.h"
#include "../headers/Node.h"
#include "../headers/ManhattanDistance.h"

using namespace std;

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

    open.push_back(Node(initialState, 0));
    closed.insert(closed.begin(), initialState);

    while (!open.empty()) {
        Node currentNode = open.front();
        open.pop_front();
        result.increaseExpandedNodes();
        result.increaseTotalHeuristicValue(heuristic.calculate(currentNode.getState()));
        for (auto successorState : stateManager.produceNextStates(currentNode.getState())) {
            Node successorNode = Node(successorState, currentNode.getCost() + 1);
            if (stateManager.isGoalState(successorState)) {
                result.setOptimalSolutionLenght(successorNode.getCost());
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