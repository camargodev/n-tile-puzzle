#ifndef INPUT_H
#define INPUT_H

#include "State.h"

using namespace std;

struct Input {
    vector<UnpackedState> states;
    int algorithm;
};

class InputReader {
private:
    const int ALGORITHM_INDEX = 1;
    const vector<string> split(const string& input, const char& delimiter);
    const string parseStatesToString(int argc, char** argv, bool isTxt);
    const UnpackedState getStateFromString(string str);
    vector<UnpackedState> parseStates(int argc, char** argv, bool isTxt);
    int getAlgorithmId(const string& algorithm);

public:
    Input parseInput(int argc, char** argv);
    static const int BFS_ID = 0;
    static const int GREEDY_ID = 1;
    static const int ASTAR_ID = 2;
    static const int IDFS_ID = 3;
    static const int IDASTAR_ID = 4;
    static const int INVALID_ID = -1;

};

#endif