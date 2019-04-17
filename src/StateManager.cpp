#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include <bitset>
#include "../headers/StateManager.h"
 
using namespace std;

int StateManager :: getNumberOfTiles(PackedState state) {
    return is3TileState(state) ? 3 : 4;
}

void StateManager :: printPackedState(PackedState pState) {
    cout << "\nPackedState = " << bitset<64>(pState);
}

void StateManager :: printUnpackedState(UnpackedState uState) {
      for(int i = 0; i < uState.size(); i++) {
        cout << "\n";
            for(int j = 0; j < uState[i].size(); j++) {
                cout << uState[i][j] << " ";
            }
        }     
}

bool StateManager :: isGoalState(PackedState state) {
    PackedState goal = is3TileState(state) ? GOAL_3x3 : GOAL_4x4;
    return state == goal;
}

PackedState StateManager :: pack(UnpackedState state) {
    PackedState packedState = 0;
    int numberOfTiles = state.size();
    for(int i = 0; i < numberOfTiles; i++) {
        for(int j = 0; j < numberOfTiles; j++) {
            packedState = packedState << 4;
            packedState = packedState|state[i][j];
        }
    }
    return packedState;
}

UnpackedState StateManager :: unpack(PackedState state) {
    PackedState mask = INITIAL_MASK;
    UnpackedState unpackedState;
    short numberOfTiles = getNumberOfTiles(state);
    for (int i = 0; i < numberOfTiles; i++) {
        Line line;
        for (int j = 0; j < numberOfTiles; j++) {
            uint64_t value = state & mask;
            value = value >> 4*(numberOfTiles*i+j);
            line.insert(line.begin(), value);
            mask = mask << 4;
        }   
        unpackedState.insert(unpackedState.begin(), line);
    }
    return unpackedState;
}

vector<State> StateManager :: produceNextStates(State state) {
    vector<State> neighbors;
    int blankPosition = getBlankTilePosition(state.value);
    short numberOfTiles = getNumberOfTiles(state.value);
    for (auto neighboorPosition : getNeighborsPositionsAndHeuristics(state)) {
        State newState;
        newState.value = swapValuesByPositions(state.value, blankPosition, neighboorPosition.first);
        newState.heuristic = neighboorPosition.second;
        neighbors.insert(neighbors.begin(), newState);
    }
    return neighbors;
}

int StateManager :: getBlankTilePosition(PackedState state) {
    PackedState mask = INITIAL_MASK;
    short numberOfTiles = getNumberOfTiles(state);
    for (int i = 0; i < numberOfTiles*numberOfTiles; i++) {
        uint64_t value = state & mask;
        short shortValue = value >> 4*i;
        if (shortValue == BLANK)
            return i;
        mask = mask << 4;
    }
}


int getValueAtPosition(PackedState state, int position) {
    uint64_t maskToGetNeighborValue = 15;
    maskToGetNeighborValue = maskToGetNeighborValue << 4*position;
    uint64_t neighborValue = state & maskToGetNeighborValue;
    neighborValue = neighborValue >> 4*(position);
    return (int) neighborValue;
}

int getExpectedPositionForNumber(int numberOfTiles, int number) {
    return (numberOfTiles*numberOfTiles) - number - 1;
}

int calculateDistanceBeetwenPositions(int pos1, int pos2, int numberOfTiles) {
    int pos1x = (int) floor(pos1/numberOfTiles);
    int pos1y = pos1 - numberOfTiles*pos1x;

    int pos2x = (int) floor(pos2/numberOfTiles);
    int pos2y = pos2 - numberOfTiles*pos2x;

    int horizontalDistance = abs(pos1x - pos2x);
    int verticalDistance = abs(pos1y - pos2y);

    return horizontalDistance + verticalDistance;
}

vector<pair<int, int>> StateManager :: getNeighborsPositionsAndHeuristics(State state) {
    vector<pair<int, int>> neighbors;
    int blankPosition = getBlankTilePosition(state.value);
    int numberOfTiles = getNumberOfTiles(state.value);
    if (blankPosition < numberOfTiles*(numberOfTiles-1)) {
        int newPosition = blankPosition+numberOfTiles;
        int valAtNewPosition = getValueAtPosition(state.value, newPosition);
        int expectedPosition = getExpectedPositionForNumber(numberOfTiles, valAtNewPosition);
        int diffToSubtract = calculateDistanceBeetwenPositions(newPosition, expectedPosition, numberOfTiles);
        int diffToAdd = calculateDistanceBeetwenPositions(blankPosition, expectedPosition, numberOfTiles);
        int heuristic = state.heuristic - diffToSubtract + diffToAdd;
        neighbors.insert(neighbors.begin(), make_pair(newPosition, heuristic));
    }
    if ((blankPosition+1) % numberOfTiles != 0) {
        int newPosition = blankPosition+1;
        int valAtNewPosition = getValueAtPosition(state.value, newPosition);
        int expectedPosition = getExpectedPositionForNumber(numberOfTiles, valAtNewPosition);
        int diffToSubtract = calculateDistanceBeetwenPositions(newPosition, expectedPosition, numberOfTiles);
        int diffToAdd = calculateDistanceBeetwenPositions(blankPosition, expectedPosition, numberOfTiles);
        int heuristic = state.heuristic - diffToSubtract + diffToAdd;
        neighbors.insert(neighbors.begin(), make_pair(newPosition, heuristic));
    }
    if (blankPosition % numberOfTiles != 0) {
        int newPosition = blankPosition-1;
        int valAtNewPosition = getValueAtPosition(state.value, newPosition);
        int expectedPosition = getExpectedPositionForNumber(numberOfTiles, valAtNewPosition);
        int diffToSubtract = calculateDistanceBeetwenPositions(newPosition, expectedPosition, numberOfTiles);
        int diffToAdd = calculateDistanceBeetwenPositions(blankPosition, expectedPosition, numberOfTiles);
        int heuristic = state.heuristic - diffToSubtract + diffToAdd;
        neighbors.insert(neighbors.begin(), make_pair(newPosition, heuristic));
    }
    if (blankPosition > numberOfTiles-1) {
        int newPosition = blankPosition-numberOfTiles;
        int valAtNewPosition = getValueAtPosition(state.value, newPosition);
        int expectedPosition = getExpectedPositionForNumber(numberOfTiles, valAtNewPosition);
        int diffToSubtract = calculateDistanceBeetwenPositions(newPosition, expectedPosition, numberOfTiles);
        int diffToAdd = calculateDistanceBeetwenPositions(blankPosition, expectedPosition, numberOfTiles);
        int heuristic = state.heuristic - diffToSubtract + diffToAdd;
        neighbors.insert(neighbors.begin(), make_pair(newPosition, heuristic));
    }
    return neighbors;
}

PackedState StateManager :: swapValuesByPositions(PackedState state, int blankPosition, int neighborPosition) {
    
    uint64_t maskToGetNeighborValue = INITIAL_MASK;
    maskToGetNeighborValue = maskToGetNeighborValue << 4*neighborPosition;
    uint64_t neighborValue = state & maskToGetNeighborValue;
    
    // cleans neighbor position
    uint64_t maskToCleanNeighborPosition = ~maskToGetNeighborValue;
    uint64_t stateWithBlankNeighbor = state & maskToCleanNeighborPosition;
    
    // moves neighbor value to blank position
    if (neighborPosition < blankPosition)
        neighborValue = neighborValue << 4*(blankPosition-neighborPosition);
    else
        neighborValue = neighborValue >> 4*(neighborPosition-blankPosition);

    return stateWithBlankNeighbor | neighborValue;
}


bool StateManager :: is3TileState(PackedState state) {
    uint64_t mask = INITIAL_MASK;
    uint64_t maskAtPos14 = mask << 4*14;
    uint64_t maskAtPos13 = mask << 4*13;
    uint64_t valAtPos13 = state & maskAtPos13;
    uint64_t valAtPos14 = state & maskAtPos14;
    return valAtPos13 == 0 && valAtPos14 == 0;
}

