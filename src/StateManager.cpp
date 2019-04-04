#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include <bitset>
#include "../headers/StateManager.h"
 
using namespace std;

  int StateManager :: getNumberOfTiles() {
      return this->numberOfTiles;
  }

  void StateManager :: printPackedState(PackedState pState) {
      cout << "\nPackedState = " << bitset<64>(pState);
}

void StateManager :: printUnpackedState(UnpackedState uState) {
      cout << "\nUnpackedState = ";
      for(int i = 0; i < numberOfTiles; i++) {
        cout << "\n";
            for(int j = 0; j < numberOfTiles; j++) {
                cout << uState[i][j] << " ";
            }
        }     
}

  bool StateManager :: isGoalState(PackedState state) {
    // for (int i = 0; i < NUMBER_OF_TILES; i++) 
    //     for (int j = 0; j < NUMBER_OF_TILES; j++)
    //         if (state[i][j] != 3*i+j) 
    //             return false;
    return true;          
  }

  PackedState StateManager :: getPackedState(UnpackedState state) {
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

UnpackedState StateManager :: getUnpackedState(PackedState state) {
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
        vector<PackedState> states;
        // Position blankTilePosition = getBlankTilePosition(state);
        // Position tileToSwapPosition;
        // if (blankTilePosition.y > 0) {
        //     tileToSwapPosition.x = blankTilePosition.x;
        //     tileToSwapPosition.y = blankTilePosition.y - 1;
        //     State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
        //     states.insert(states.end(), newState);
        // }
        // if (blankTilePosition.x > 0) {
        //     tileToSwapPosition.x = blankTilePosition.x - 1;
        //     tileToSwapPosition.y = blankTilePosition.y;
        //     State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
        //     states.insert(states.end(), newState);
        // }
        // if (blankTilePosition.y < NUMBER_OF_TILES-1) {
        //     tileToSwapPosition.x = blankTilePosition.x;
        //     tileToSwapPosition.y = blankTilePosition.y + 1;
        //     State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
        //     states.insert(states.end(), newState);
        // }
        // if (blankTilePosition.x < NUMBER_OF_TILES-1) {
        //     tileToSwapPosition.x = blankTilePosition.x + 1;
        //     tileToSwapPosition.y = blankTilePosition.y;
        //     State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
        //     states.insert(states.end(), newState);
        // }
        // return states;
    }

    int StateManager :: getBlankTilePosition(PackedState state) {
        Position blankTilePosition;
        PackedState mask = INITIAL_MASK;

        for (int i = 0; i < numberOfTiles*numberOfTiles; i++) {
            uint64_t value = state & mask;
            short shortValue = value >> 4*i;
            if (shortValue == BLANK)
                return i;
            mask = mask << 4;
        }
    }

    
    vector<int> StateManager :: getNeighborsPosition(int blankPosition) {

    }

    PackedState StateManager :: swapByIndexes(PackedState state, Position pos1, Position pos2) {
        PackedState newState = state;
        // int firstValue = newState[pos1.x][pos1.y];
        // newState[pos1.x][pos1.y] = newState[pos2.x][pos2.y];
        // newState[pos2.x][pos2.y] = firstValue;
        // return newState;
    }