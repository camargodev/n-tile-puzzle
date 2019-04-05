#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "State.h"
#include "Position.h"

class ManhattanDistance {

private:
    int numberOfTiles;

public:
    int getExpectedPositionForNumber(int number);
    ManhattanDistance(short numberOfTiles);
    int calculate(PackedState state);
    int calculateDistanceBeetwenPositions(int pos1, int pos2);
};

#endif