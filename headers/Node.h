#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <vector>

class Node {

public:

    Node(PackedState state, int cost);
    PackedState getState();
    int getCost();

private:

    PackedState state;
    int cost;

};

#endif