#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "State.h"

class ManhattanDistance {

private:
    int numberOfTiles;
    int getExpectedPositionForNumber(int number);
    int calculateDistanceBeetwenPositions(int pos1, int pos2);

public:
    ManhattanDistance(short numberOfTiles);
    int calculate(PackedState state);
};

#endif