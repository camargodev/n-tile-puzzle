#ifndef GREEDY_H
#define GREEDY_H

#include "State.h"
#include "Result.h"

class GreedyBestFirstSearch {

public:

    GreedyBestFirstSearch(int numberOfTiles);
    Result execute(PackedState initialState);

private:

    int numberOfTiles;

};

#endif