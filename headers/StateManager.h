#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"
#include "Position.h"
#include <vector>

class StateManager {

public:

    const short BLANK = 0;
    std::vector<State3x3> produceNextStates(State3x3 state);
    bool isObjectiveState(State3x3 state);

private:

    Position getBlankTilePosition(State3x3 state);
    State3x3 swapByIndexes(State3x3 state, Position pos1, Position pos2);

};

#endif