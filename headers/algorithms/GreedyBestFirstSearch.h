#ifndef GREEDY_H
#define GREEDY_H

#include "../State.h"
#include "../Result.h"

class GreedyBestFirstSearch {

public:

    GreedyBestFirstSearch(short numberOfTiles);
    Result execute(PackedState initialState);

private:

    short numberOfTiles;

};

#endif