#include <iostream>
#include <math.h>
#include "../headers/Input.h"

using namespace std;

const vector<string> InputReader :: split(const string& input, const char& delimiter) {
	string buffer{""};
	vector<string> parts;
	
	for(auto character : input) {
		if(character != delimiter) {
            buffer += character; 
        } else if(character == delimiter && buffer != "") { 
            parts.push_back(buffer); 
            buffer = ""; 
        }
	}
	if(buffer != "") 
        parts.push_back(buffer);
	
	return parts;
}

int InputReader :: getAlgorithmId(const string& algorithm) {
    if (algorithm == "-bfs")
        return BFS_ID;
    if (algorithm == "-gbfs")
        return GREEDY_ID;
    if (algorithm == "-astar")
        return ASTAR_ID;
    if (algorithm == "-idfs")
        return IDFS_ID;
    if (algorithm == "-idastar")
        return IDASTAR_ID;
    return INVALID_ID;
}

const string InputReader :: parseStatesToString(int argc, char** argv) {
    string stringStates = "";
    for (int i = ALGORITHM_INDEX+1; i < argc-1; i++) {
        stringStates = stringStates + argv[i] + " ";
    }
    stringStates = stringStates + argv[argc-1];
    return stringStates;
} 

const UnpackedState InputReader :: getStateFromString(string str) {
    vector<string> values = split(str, ' ');
    UnpackedState state;
    Line stateLine;
    int numOfTiles = sqrt(values.size()); 
    int counter = 1;
    for (auto value : values) {
        stateLine.push_back(stoi(value));
        if (counter == numOfTiles) {
            state.push_back(stateLine);
            counter = 0;
            stateLine.clear();
        }
        counter++;
    }
    return state;
}

vector<UnpackedState> InputReader :: parseStates(int argc, char** argv) {
    string input = parseStatesToString(argc, argv);
    vector<string> strStates = split(input, ',');
    vector<UnpackedState> states;
    for (auto state : strStates) 
        states.push_back(getStateFromString(state));
    return states;
}

Input InputReader :: parseInput(int argc, char** argv) {
    Input input;
    input.algorithm = getAlgorithmId(argv[ALGORITHM_INDEX]);
    input.states = parseStates(argc, argv);
    return input;
}