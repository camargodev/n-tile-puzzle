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
    
private:

    Position getBlankTilePosition(PackedState state);
    PackedState swapByIndexes(PackedState state, Position pos1, Position pos2);
    int numberOfTiles;

};

#endif