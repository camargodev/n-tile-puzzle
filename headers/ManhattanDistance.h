#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "State.h"

class ManhattanDistance {

private:
    int numberOfTiles;

public:
    int calculate(PackedState state);
    void setNumberOfTiles(int numberOfTiles);
    int getExpectedPositionForNumber(int number);
    int calculateDistanceBeetwenPositions(int pos1, int pos2);
};

#endif