#include<iostream>
#include <stdlib.h> 
#include <vector>
#include <bitset>
#include "headers/Position.h"
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
 
using namespace std;



int main()
{
    // ManhattanDistance manhattanDistance;
    StateManager stateManager;
    
    // State3x3 initialState = {{{3,0,8}, {7,5,2}, {1,6,4}}};
    // cout << "Initial state is:\n";
    // printState3x3(initialState);
    // int distance = manhattanDistance.calculate(initialState);
    // cout << "Manhattan distance to S* is " << distance << "\n";
    // vector<State3x3> states = stateManager.produceNextStates(initialState);
    // for(auto state : states) {
    //     cout << "\nNeighbor:\n";
    //     printState3x3(state);
    //     int packedState = stateManager.getPackedState(state);
    //     cout << "Packed state is " << packedState << "\n";
    //     cout << "Unpacked state is:\n";
    //     printState3x3(stateManager.getUnpackedState(packedState));
    //     distance = manhattanDistance.calculate(state);
    //     cout << "Manhattan distance to S* is " << distance << "\n";
    //     cout << "Is objective: " << stateManager.isObjectiveState(state) << "\n";
    // }

    cout << "\n\n3x3:";
    UnpackedState state3x3 = {{0, 3, 4}, {5, 1, 8}, {2, 7, 6}};
    PackedState packed3x3 = stateManager.getPackedState(state3x3);
    stateManager.printPackedState(packed3x3);
    UnpackedState unpacked3x3 = stateManager.getUnpackedState(packed3x3);
    stateManager.printUnpackedState(unpacked3x3);
    
    cout << "\n\n4x4:";
    UnpackedState state4x4 = {{12, 0, 3, 4}, {9, 5, 1, 8}, {15, 2, 7, 6}, {11, 10, 14, 13}};
    PackedState packed4x4 = stateManager.getPackedState(state4x4);
    stateManager.printPackedState(packed4x4);
    UnpackedState unpacked4x4 = stateManager.getUnpackedState(packed4x4);
    stateManager.printUnpackedState(unpacked4x4);

    return 0;
}


