#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include "StateManager.h"
 
using namespace std;

  vector<State3x3> StateManager :: produceNextStates(State3x3 state) {;
        vector<State3x3> states;
        Position blankTilePosition = getBlankTilePosition(state);
        if (blankTilePosition.getY() > 0) {
            Position tileToSwapPosition(blankTilePosition.getX()-1, blankTilePosition.getY());
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.getX() > 0) {
            Position tileToSwapPosition(blankTilePosition.getX(), blankTilePosition.getY()-1);
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.getY() < NUMBER_OF_TILES-1) {
            Position tileToSwapPosition(blankTilePosition.getX()+1, blankTilePosition.getY());
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        if (blankTilePosition.getX() < NUMBER_OF_TILES-1) {
            Position tileToSwapPosition(blankTilePosition.getX(), blankTilePosition.getY()+1);
            State3x3 newState = swapByIndexes(state, blankTilePosition, tileToSwapPosition);
            states.insert(states.end(), newState);
        }
        return states;
    }

    Position StateManager :: getBlankTilePosition(State3x3 state) {
        for (int i = 0; i < NUMBER_OF_TILES; i++) 
            for (int j = 0; j < NUMBER_OF_TILES; j++) 
                if (state[i][j] == BLANK)
                    return Position(i, j);
    }

    State3x3 StateManager :: swapByIndexes(State3x3 state, Position pos1, Position pos2) {
        State3x3 newState = state;
        int firstValue = newState[pos1.getX()][pos1.getY()];
        newState[pos1.getX()][pos1.getY()] = newState[pos2.getX()][pos2.getY()];
        newState[pos2.getX()][pos2.getY()] = firstValue;
        return newState;
    }