#ifndef IDAStar_H
#define IDAStar_H

#include "../State.h"
#include "../Result.h"
#include "../Node.h"

class IDAStar {

public:
    IDAStar();
    ~IDAStar();
    Result execute(PackedState initialState);

private:
    Result* result;
    int f(Node node);
    Node buildNode(State state, int cost);
    Node buildInitialNode(State state);
    typedef struct Solution{
        bool isSolution;
        unsigned long long int cost;
        unsigned long long int limit;
    } Solution;
    Solution recursiveSearch(Node state, PackedState parent, int fLimit);

};

#endif