#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "State.h"
#include "Position.h"

class ManhattanDistance {

private:
    Position getExpectedPositionForNumber(int number);
    int numberOfTiles;

public:
    ManhattanDistance(short numberOfTiles);
    int calculate(PackedState state);

};

#endif