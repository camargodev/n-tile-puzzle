#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"
#include "Node.h"
#include "ManhattanDistance.h"
#include <vector>

class StateManager {

public:

    int getNumberOfTiles(PackedState state);
    void printPackedState(PackedState state);
    void printUnpackedState(UnpackedState state);
    bool isGoalState(PackedState state);
    PackedState pack(UnpackedState state);
    UnpackedState unpack(PackedState state);
    std::vector<State> produceNextStates(State state);
    std::vector<PackedState> produceNextPackedStates(PackedState state);
    vector<int> getNeighborsPositions(short numberOfTiles, int blankPosition);
    bool is3TileState(PackedState state);
    vector<pair<int, int>> getNeighborsPositionsAndHeuristics(State state);
    int calculateHeuristic(PackedState state);

private:
  
    const short BLANK = 0;
    const PackedState INITIAL_MASK = 15;
    ManhattanDistance heuristicCalculator;
    PackedState swapValuesByPositions(PackedState state, int pos1, int pos2);
    int getBlankTilePosition(PackedState state);

};

#endif