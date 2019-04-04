#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
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
    
    State3x3 initialState = {{{4, 1, 2}, {3, 0, 5}, {6, 7, 8}}};
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
    }

    return 0;
}
