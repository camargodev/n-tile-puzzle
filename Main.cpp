#include<iostream>
#include <stdlib.h> 
#include <vector>
#include "headers/Position.h"
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
 
using namespace std;

void printState3x3(State3x3 state) {
    for (int i = 0; i < NUMBER_OF_TILES; i++) { 
        for (int j = 0; j < NUMBER_OF_TILES; j++) { 
            cout << state[i][j] << " ";
        }
        cout << "\n";
    }

}

int main()
{
    ManhattanDistance manhattanDistance;
    StateManager stateManager;
    
    State3x3 initialState = {{{3,0,8}, {7,5,2}, {1,6,4}}};
    cout << "Initial state is:\n";
    printState3x3(initialState);
    int distance = manhattanDistance.calculate(initialState);
    cout << "Manhattan distance to S* is " << distance << "\n";

    vector<State3x3> states = stateManager.produceNextStates(initialState);
    for(auto state : states) {
        cout << "\nNeighbor:\n";
        printState3x3(state);
        distance = manhattanDistance.calculate(state);
        cout << "Manhattan distance to S* is " << distance << "\n";
        cout << "Is objective: " << stateManager.isObjectiveState(state) << "\n";
    }

    return 0;
}
