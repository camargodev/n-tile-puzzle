#ifndef BFS_H
#define BFS_H

#include "../State.h"
#include "../Result.h"

class BFS {

public:

    BFS(short numberOfTiles);
    Result execute(PackedState initialState);

private:

    short numberOfTiles;

};

#endif