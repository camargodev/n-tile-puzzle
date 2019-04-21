#include <iostream>
#include "../headers/Result.h"

using namespace std;

void Result :: increaseExpandedNodes() {
    this->expandedNodes++;
}

void Result :: increaseGeneratedNodes() {
    this->generatedNodes++;
}

void Result :: stopCountingTime() {
    this->duration = float(clock() - this->startMoment)/CLOCKS_PER_SEC;
}

void Result :: startCountingTime() {
    this->startMoment = clock();
}

void Result :: setOptimalSolutionLenght(int length) {
    this->optimalSolutionLenght = length;
}

void Result :: setInitialHeuristicValue(int hValue) {
    this->initialHeuristicValue = hValue;
}

void Result :: increaseTotalHeuristicValue(int hValue) {
    this->totalHValue += hValue;
}


void Result :: setTotalHeuristicValue(int hValue){
    this->totalHValue = hValue;
}

void Result :: printResult() {
    string strResult = "\n";
    strResult += to_string(this->expandedNodes) + ",";
    strResult += to_string(this->optimalSolutionLenght) + ",";
    strResult += to_string(this->duration) + ",";
    strResult += to_string(this->totalHValue/max(this->expandedNodes, 1)) + ",";
    strResult += to_string(this->initialHeuristicValue);
    cout << strResult;
}

void Result :: writeResult(string fileName) {
    ofstream outFile;
    outFile.open(fileName, std::ios_base::app);

    string strResult = "";
    strResult += to_string(this->expandedNodes) + ",";
    strResult += to_string(this->optimalSolutionLenght) + ",";
    strResult += to_string(this->duration) + ",";
    strResult += to_string(this->totalHValue/max(this->expandedNodes, 1)) + ",";
    strResult += to_string(this->initialHeuristicValue);
    outFile << strResult + "\n";

    outFile.close();
}