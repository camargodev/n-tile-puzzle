#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
 
using namespace std;

const short BLANK = 0;
const short NUMBER_OF_TILES = 3;

using State3x3 = std::array<std::array<int, 3>, 3>;

void printState3x3(State3x3 state) {
    for (int i = 0; i < NUMBER_OF_TILES; i++) { 
        for (int j = 0; j < NUMBER_OF_TILES; j++) { 
            cout << state[i][j] << " ";
        }
        cout << "\n";
    }

}

class Position {

private:
    int x;
    int y;

public:
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class ManhattanDistance {

public:

    int calculate(State3x3 state) {
        int distance = 0;
        for (int i = 0; i < NUMBER_OF_TILES; i++) {
            for (int j = 0; j < NUMBER_OF_TILES; j++) {
                Position expectedPosition = getExpectedPositionForNumber(state[i][j]);
                distance += abs(i - expectedPosition.getX());
                distance += abs(j - expectedPosition.getY());
            }
        }
        return distance;
    }
    
private:

    // given a number, returns the position where the number should be
    Position getExpectedPositionForNumber(int number) {
        int x = (int) floor(number/NUMBER_OF_TILES);
        int y = number - NUMBER_OF_TILES*x;
        return Position(x, y);
    }

};

class StateManager {

public:

    vector<State3x3> produceNextStates(State3x3 state) {;
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

private:

    Position getBlankTilePosition(State3x3 state) {
        for (int i = 0; i < NUMBER_OF_TILES; i++) 
            for (int j = 0; j < NUMBER_OF_TILES; j++) 
                if (state[i][j] == BLANK)
                    return Position(i, j);
    }

    State3x3 swapByIndexes(State3x3 state, Position pos1, Position pos2) {
        State3x3 newState = state;
        int firstValue = newState[pos1.getX()][pos1.getY()];
        newState[pos1.getX()][pos1.getY()] = newState[pos2.getX()][pos2.getY()];
        newState[pos2.getX()][pos2.getY()] = firstValue;
        return newState;
    }

};

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
