#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include "../headers/StateManager.h"
 
using namespace std;

  bool StateManager :: isObjectiveState(State3x3 state) {
    for (int i = 0; i < NUMBER_OF_TILES; i++) 
        for (int j = 0; j < NUMBER_OF_TILES; j++)
            if (state[i][j] != 3*i+j) 
                return false;
    return true;          
  }

  vector<State3x3> StateManager :: produceNextStates(State3x3 state) {;
        vector<State3x3> states;
        Position blankTilePosition = getBlankTilePosition(state);
        Position tileToSwapPosition;
        if (blankTilePosition.y > 0) {
            tileToSwapPosition.x = blankTilePosition.x;
            tileToSwapPosition.y = blankTilePosition.y - 1;
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.x > 0) {
            tileToSwapPosition.x = blankTilePosition.x - 1;
            tileToSwapPosition.y = blankTilePosition.y;
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.y < NUMBER_OF_TILES-1) {
            tileToSwapPosition.x = blankTilePosition.x;
            tileToSwapPosition.y = blankTilePosition.y + 1;
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.x < NUMBER_OF_TILES-1) {
            tileToSwapPosition.x = blankTilePosition.x + 1;
            tileToSwapPosition.y = blankTilePosition.y;
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        return states;
    }

    Position StateManager :: getBlankTilePosition(State3x3 state) {
        Position blankTilePosition;
        for (int i = 0; i < NUMBER_OF_TILES; i++) 
            for (int j = 0; j < NUMBER_OF_TILES; j++) 
                if (state[i][j] == BLANK) {
                    blankTilePosition.x = i;
                    blankTilePosition.y = j;
                }
        return blankTilePosition;
    }

    State3x3 StateManager :: swapByIndexes(State3x3 state, Position pos1, Position pos2) {
        State3x3 newState = state;
        int firstValue = newState[pos1.x][pos1.y];
        newState[pos1.x][pos1.y] = newState[pos2.x][pos2.y];
        newState[pos2.x][pos2.y] = firstValue;
        return newState;
    }