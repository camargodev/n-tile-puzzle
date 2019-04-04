#ifndef MANHATTAN_H
#define MANHATTAN_H

#include "State.h"
#include "Position.h"

class ManhattanDistance {

private:
    Position getExpectedPositionForNumber(int number);

public:
    int calculate(State3x3 state);

};

#endif