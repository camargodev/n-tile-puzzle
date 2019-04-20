#ifndef IDFS_H
#define IDFS_H

#include "../State.h"
#include "../Result.h"
#include "../ManhattanDistance.h"

class IDFS {

public:
    IDFS();
    ~IDFS();
    Result execute(PackedState initialState);

private:
    Result* result;
    typedef struct Solution{
        bool isSolution;
        unsigned long long int cost;
    } Solution;
    Solution depthLimitedSearch(PackedState state, PackedState parent, int depthLimit);
    
};

#endif