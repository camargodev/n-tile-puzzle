#ifndef IDFS_H
#define IDFS_H

#include "../State.h"
#include "../Result.h"
#include "../ManhattanDistance.h"



typedef struct Solution{
    bool isSolution;
    unsigned long int cost;
} Solution;

class IDFS {

public:
    Result execute(PackedState initialState);

private:
    Solution depthLimitedSearch(PackedState state, PackedState parent, int depthLimit, Result* result, ManhattanDistance* heuristic);

};

#endif