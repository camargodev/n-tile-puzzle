#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <deque>
#include <math.h>
#include <unordered_set>
#include <algorithm>
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
#include "headers/Node.h"
#include "headers/Result.h"
#include "headers/Input.h"
#include "headers/Input.h"
#include "headers/algorithms/BFS.h"
#include "headers/algorithms/GreedyBestFirstSearch.h"
#include "headers/algorithms/AStar.h"
#include "headers/algorithms/IDFS.h"
#include "headers/algorithms/IDAStar.h"
#include <ctime>
 
using namespace std;

Result processAlgorithm(int algorithmId, PackedState initialState) {
    switch (algorithmId) {
        case InputReader::BFS_ID:
            return BFS().execute(initialState);
        case InputReader::GREEDY_ID:
            return GreedyBestFirstSearch().execute(initialState);
        case InputReader::ASTAR_ID:
            return AStar().execute(initialState);
        case InputReader::IDFS_ID:
            return IDFS().execute(initialState);
        case InputReader::IDASTAR_ID:
            return IDAStar().execute(initialState);
    }
}

string currentTime(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y-%H", &tstruct);
    string str(buf);
    for(int i = 0; i < str.length(); i++){
        if(str.at(i) == ':')
            str.at(i) = '_';
    }
    return str;
}

int main(int argc, char** argv)
{   
    StateManager manager;
    InputReader reader;
    Input input = reader.parseInput(argc, argv);

    string fileName = currentTime() + argv[1] + ".csv";

    for (auto unpackedState : input.states) {
        PackedState state = manager.pack(unpackedState);
        Result result = processAlgorithm(input.algorithm, state);
        result.printResult(); 
        result.writeResult(fileName);
    }
    return 0;
    
}


