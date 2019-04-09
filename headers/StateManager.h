#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"
#include <vector>

class StateManager {

public:

    int getNumberOfTiles(PackedState state);
    void printPackedState(PackedState state);
    void printUnpackedState(UnpackedState state);
    bool isGoalState(PackedState state);
    PackedState pack(UnpackedState state);
    UnpackedState unpack(PackedState state);
    std::vector<PackedState> produceNextStates(PackedState state);
    bool is3TileState(PackedState state);

private:
  
    const short BLANK = 0;
    const PackedState INITIAL_MASK = 15;
    vector<int> getNeighborsPositions(short numberOfTiles, int blankPosition);
    PackedState swapValuesByPositions(PackedState state, int pos1, int pos2);
    int getBlankTilePosition(PackedState state);

};

#endif