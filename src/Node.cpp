#include "../headers/Node.h"

using namespace std;

Node :: Node(PackedState state, int cost) {
    this->state = state;
    this->cost = cost;
}

Node :: Node(PackedState state, int cost, int index) {
    this->state = state;
    this->cost = cost;
    this->index = index;
}


PackedState Node :: getState() {
    return this->state;
}

int Node :: getCost() {
    return this->cost;
}

int Node :: getIndex() {
    return this->index;
}