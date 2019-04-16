#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <deque>

struct Node {
    PackedState state;
    int cost;
    int index;
    int heuristicValue;
};

#endif