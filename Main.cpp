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
    StateManager stateManager;
    ManhattanDistance manhattanCalculator3x3(3);
    ManhattanDistance manhattanCalculator4x4(4);

    cout << "\n\n3x3:";
    UnpackedState state3x3 = {{1, 0, 2}, {3, 4, 5}, {6, 7, 8}};
    PackedState packed3x3 = stateManager.getPackedState(state3x3);
    //stateManager.printPackedState(packed3x3);
    UnpackedState unpacked3x3 = stateManager.getUnpackedState(packed3x3);
    cout << "\nInitial state: ";
    stateManager.printUnpackedState(unpacked3x3);
    cout << "\nManhattan distance for state is " << manhattanCalculator3x3.calculate(packed3x3);
    int blankPosition = stateManager.getBlankTilePosition(packed3x3);
    cout << "\nPosition of blank = " << blankPosition;
    vector<PackedState> neighbors = stateManager.produceNextStates(packed3x3);
    int cont = 1;
    for (auto neighbor : neighbors) {
        cout << "\n--Neighbor " << cont;
        cont++;
        stateManager.printUnpackedState(stateManager.getUnpackedState(neighbor));
        cout << "\nManhattan distance for state is " << manhattanCalculator3x3.calculate(neighbor);
        cout << "\n\nIs goal = " << stateManager.isGoalState(neighbor);
    }

    cout << "\n\n4x4:";
    UnpackedState state4x4 = {{4, 1, 2, 3}, {0, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
    PackedState packed4x4 = stateManager.getPackedState(state4x4);
    //stateManager.printPackedState(packed4x4);
    UnpackedState unpacked4x4 = stateManager.getUnpackedState(packed4x4);
    cout << "\nInitial state: ";
    stateManager.printUnpackedState(unpacked4x4);
    cout << "\nManhattan distance for state is " << manhattanCalculator4x4.calculate(packed4x4);
    blankPosition = stateManager.getBlankTilePosition(packed4x4);
    cout << "\nPosition of blank = " << blankPosition;
    neighbors = stateManager.produceNextStates(packed4x4);
    cont = 1;
    for (auto neighbor : neighbors) {
        cout << "\n\n--Neighbor " << cont;
        cont++;
        stateManager.printUnpackedState(stateManager.getUnpackedState(neighbor));
        cout << "\nManhattan distance for state is " << manhattanCalculator4x4.calculate(neighbor);
        cout << "\nIs goal = " << stateManager.isGoalState(neighbor);
    }
    
    cout << "\n\n";
    return 0;
    
}


