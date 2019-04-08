#ifndef BFS_H
#define BFS_H

#include "State.h"
#include "Result.h"

class BFS {

public:

    BFS(int numberOfTiles);
    Result execute(PackedState initialState);

private:

    int numberOfTiles;

};

#endif