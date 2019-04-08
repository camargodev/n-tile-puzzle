#ifndef A_STAR_H
#define A_STAR_H

#include "State.h"
#include "Result.h"

class AStar {

public:

    AStar(short numberOfTiles);
    Result execute(PackedState initialState);

private:

    int numberOfTiles;

};

#endif