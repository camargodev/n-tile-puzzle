#ifndef STATE_H
#define STATE_H

#include <vector>
#include <cstdint>

using namespace std;

using Line = vector<short>;
using UnpackedState = vector<Line>;
using PackedState = uint64_t;
using ClosedSet = vector<PackedState>;

const PackedState GOAL_3x3 = 305419896;
const PackedState GOAL_4x4 = 81985529216486895;

#endif