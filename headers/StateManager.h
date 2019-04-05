#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"
#include <vector>

class StateManager {

public:

    const short BLANK = 0;
    const uint64_t ALL_ONES = ~0;
    int getNumberOfTiles();
    void printPackedState(PackedState state);
    void printUnpackedState(UnpackedState state);
    bool isGoalState(PackedState state);
    PackedState pack(UnpackedState state);
    UnpackedState unpack(PackedState state);
    std::vector<PackedState> produceNextStates(PackedState state);
    int getBlankTilePosition(PackedState state);

private:

    const PackedState INITIAL_MASK = 15;
    int numberOfTiles;
    vector<int> getNeighborsPositions(int blankPosition);
    PackedState swapValuesByPositions(PackedState state, int pos1, int pos2);

};

#endif