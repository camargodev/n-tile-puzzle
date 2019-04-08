#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <deque>

class Node {

public:

    Node(PackedState state, int cost);
    Node(PackedState state, int cost, int index);
    PackedState getState();
    int getCost();
    int getIndex();

private:

    PackedState state;
    int cost;
    int index;
};

#endif