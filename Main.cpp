#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <deque>
#include <algorithm>
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
#include "headers/Node.h"
#include "headers/Result.h"
 
using namespace std;
using ClosedSet = vector<PackedState>;
using OpenSet = deque<Node>;

StateManager stateManager;

Result executeBFS(PackedState initialState) {    
    Result result;
    OpenSet open;
    ClosedSet closed;

    result.startCountingTime();
    open.push_back(Node(initialState, 0));
    closed.insert(closed.begin(), initialState);
    
    while (!open.empty()) {
        Node currentNode = open.front();
        open.pop_front();
        result.increaseExpandedNodes();
        for (auto successorState : stateManager.produceNextStates(currentNode.getState())) {
            Node successorNode = Node(successorState, currentNode.getCost() + 1);
            if (stateManager.isGoalState(successorState)) {
                result.setOptimalSolutionLenght(successorNode.getCost());
                result.stopCountingTime();
                return result;
            }
            if (find(closed.begin(), closed.end(), successorState) == closed.end()) {
                closed.insert(closed.begin(), successorState);
                open.push_back(successorNode);
            }
        }
    }
    return result;

}

int main()
{
    
    PackedState initialState = stateManager.pack({{8, 3, 5}, {7, 2, 6}, {0, 4, 1}});
    Result result = executeBFS(initialState);
    result.printResult();

    cout << "\n\n";
    return 0;
    
}


