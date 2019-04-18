#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <deque>

struct Node {
    State state;
    int cost;
    int index;
};

#endif