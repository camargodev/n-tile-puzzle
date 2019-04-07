#include "../headers/Node.h"

using namespace std;

Node :: Node(PackedState state, int cost) {
    this->state = state;
    this->cost = cost;
}

PackedState Node :: getState() {
    return this->state;
}

int Node :: getCost() {
    return this->cost;
}