#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include <bitset>
#include "../headers/StateManager.h"
 
using namespace std;

StateManager :: StateManager(int numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
}

int StateManager :: getNumberOfTiles() {
    return this->numberOfTiles;
}

void StateManager :: printPackedState(PackedState pState) {
    cout << "\nPackedState = " << bitset<64>(pState);
}

void StateManager :: printUnpackedState(UnpackedState uState) {
      for(int i = 0; i < numberOfTiles; i++) {
        cout << "\n";
            for(int j = 0; j < numberOfTiles; j++) {
                cout << uState[i][j] << " ";
            }
        }     
}

bool StateManager :: isGoalState(PackedState state) {
    PackedState goal = numberOfTiles == 3 ? GOAL_3x3 : GOAL_4x4;
    return state == goal;
}

PackedState StateManager :: pack(UnpackedState state) {
    PackedState packedState = 0;
    this->numberOfTiles = state.size();
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

vector<PackedState> StateManager :: produceNextStates(PackedState state) {
    vector<PackedState> neighbors;
    int blankPosition = getBlankTilePosition(state);
    vector<int> neighborsPositions = getNeighborsPositions(blankPosition);
    for (auto neighboorPosition : neighborsPositions) {
        PackedState neighbor = swapValuesByPositions(state, blankPosition, neighboorPosition);
        neighbors.insert(neighbors.begin(), neighbor);
    }
    return neighbors;
}

int StateManager :: getBlankTilePosition(PackedState state) {
    PackedState mask = INITIAL_MASK;

    for (int i = 0; i < numberOfTiles*numberOfTiles; i++) {
        uint64_t value = state & mask;
        short shortValue = value >> 4*i;
        if (shortValue == BLANK)
            return i;
        mask = mask << 4;
    }
}

vector<int> StateManager :: getNeighborsPositions(int blankPosition) {
    vector<int> neighbors;
    if (blankPosition < numberOfTiles*(numberOfTiles-1))
        neighbors.insert(neighbors.begin(), blankPosition+numberOfTiles);
    if ((blankPosition+1) % numberOfTiles != 0)
        neighbors.insert(neighbors.begin(), blankPosition+1);
    if (blankPosition % numberOfTiles != 0)
        neighbors.insert(neighbors.begin(), blankPosition-1);
    if (blankPosition > numberOfTiles-1)
        neighbors.insert(neighbors.begin(), blankPosition-numberOfTiles);
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