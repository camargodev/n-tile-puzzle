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

vector<PackedState> StateManager :: produceNextStates(PackedState state) {
    vector<PackedState> neighbors;
    int blankPosition = getBlankTilePosition(state);
    short numberOfTiles = getNumberOfTiles(state);
    vector<int> neighborsPositions = getNeighborsPositions(numberOfTiles, blankPosition);
    for (auto neighboorPosition : neighborsPositions) {
        PackedState neighbor = swapValuesByPositions(state, blankPosition, neighboorPosition);
        neighbors.insert(neighbors.begin(), neighbor);
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

vector<int> StateManager :: getNeighborsPositions(short numberOfTiles, int blankPosition) {
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

bool StateManager :: is3TileState(PackedState state) {
    uint64_t mask = INITIAL_MASK;
    uint64_t maskAtPos14 = mask << 4*14;
    uint64_t maskAtPos13 = mask << 4*13;
    uint64_t valAtPos13 = state & maskAtPos13;
    uint64_t valAtPos14 = state & maskAtPos14;
    return valAtPos13 == 0 && valAtPos14 == 0;
}