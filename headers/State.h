#ifndef STATE_H
#define STATE_H

#include <vector>
#include <cstdint>
#include <unordered_set>

using namespace std;

using Line = vector<short>;
using UnpackedState = vector<Line>;
using PackedState = uint64_t;
using ClosedSet = unordered_set<PackedState>;

const PackedState GOAL_3x3 = 305419896;
const PackedState GOAL_4x4 = 81985529216486895;

struct State {
    PackedState value;
    int heuristic;
};

#endif