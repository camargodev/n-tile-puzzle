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
    UnpackedState state3x3 = {{1, 0, 2}, {3, 4, 5}, {6, 7, 8}};
    PackedState packed3x3 = stateManager.getPackedState(state3x3);
    //stateManager.printPackedState(packed3x3);
    UnpackedState unpacked3x3 = stateManager.getUnpackedState(packed3x3);
    cout << "\nInitial state: ";
    stateManager.printUnpackedState(unpacked3x3);
    int blankPosition = stateManager.getBlankTilePosition(packed3x3);
    cout << "\nPosition of blank = " << blankPosition;
    vector<PackedState> neighbors = stateManager.produceNextStates(packed3x3);
    int cont = 1;
    for (auto neighbor : neighbors) {
        cout << "\n--Neighbor " << cont;
        cont++;
        stateManager.printUnpackedState(stateManager.getUnpackedState(neighbor));
        cout << "\n\nIs goal = " << stateManager.isGoalState(neighbor);
    }

    cout << "\n\n4x4:";
    UnpackedState state4x4 = {{4, 1, 2, 3}, {0, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
    PackedState packed4x4 = stateManager.getPackedState(state4x4);
    //stateManager.printPackedState(packed4x4);
    UnpackedState unpacked4x4 = stateManager.getUnpackedState(packed4x4);
    cout << "\nInitial state: ";
    stateManager.printUnpackedState(unpacked4x4);
    blankPosition = stateManager.getBlankTilePosition(packed4x4);
    cout << "\nPosition of blank = " << blankPosition;
    neighbors = stateManager.produceNextStates(packed4x4);
    cont = 1;
    for (auto neighbor : neighbors) {
        cout << "\n\n--Neighbor " << cont;
        cont++;
        stateManager.printUnpackedState(stateManager.getUnpackedState(neighbor));
        cout << "\nIs goal = " << stateManager.isGoalState(neighbor);
    }

    // UnpackedState goal3x3 = {{0,1,2},{3,4,5},{6,7,8}};
    // UnpackedState goal4x4 = {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
    // cout << "\nValue of goal 3x3: " << stateManager.getPackedState(goal3x3);
    // cout << "\nValue of goal 4x4: " << stateManager.getPackedState(goal4x4);
    cout << "\n\n";


    return 0;
    
}


