#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"
#include "Position.h"
#include <vector>

class StateManager {

public:

    const short BLANK = 0;
    int getNumberOfTiles();
    void printPackedState(PackedState state);
    void printUnpackedState(UnpackedState state);
    bool isGoalState(PackedState state);
    PackedState getPackedState(UnpackedState state);
    UnpackedState getUnpackedState(PackedState state);
    std::vector<PackedState> produceNextStates(PackedState state);
    int getBlankTilePosition(PackedState state);
    vector<int> getNeighborsPosition(int blankPosition);
    
private:

    const PackedState INITIAL_MASK = 15;
    PackedState swapByIndexes(PackedState state, Position pos1, Position pos2);
    int numberOfTiles;

};

#endif