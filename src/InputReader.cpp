#include <iostream>
#include <fstream>
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

const string InputReader :: parseStatesToString(int argc, char** argv, bool isTxt) {
    string stringStates;
    if(isTxt){
        ifstream ifs(argv[argc-1]);
        stringStates.assign( (istreambuf_iterator<char>(ifs) ),
                (istreambuf_iterator<char>()    ) );
    }
    else{
        stringStates = "";
        for (int i = ALGORITHM_INDEX+1; i < argc-1; i++) {
            stringStates = stringStates + argv[i] + " ";
        }
        stringStates = stringStates + argv[argc-1];
    }    
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

vector<UnpackedState> InputReader :: parseStates(int argc, char** argv, bool isTxt) {
    string input = parseStatesToString(argc, argv, isTxt);
    vector<string> strStates;
    if(isTxt){
        strStates = split(input, '\n');
    }
    else{
        strStates = split(input, ',');
    }
    vector<UnpackedState> states;
    for (auto state : strStates) 
        states.push_back(getStateFromString(state));
    return states;
}

Input InputReader :: parseInput(int argc, char** argv) {
    Input input;

    string teste = "";
    teste = teste + argv[argc-1];
    std::size_t found = teste.find(".txt");
    bool isTxt = false;
    if(found!=std::string::npos){
        isTxt = true;
    }

    input.algorithm = getAlgorithmId(argv[ALGORITHM_INDEX]);
    input.states = parseStates(argc, argv, isTxt);
    return input;
}