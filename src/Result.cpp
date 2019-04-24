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
    this->counter = this->counter + 1;
}


void Result :: setTotalHeuristicValue(int hValue){
    this->totalHValue = hValue;
}

void Result :: printResult() {
    string strResult = "\n";
    this->averageHeuristicValue = this->totalHValue/max(this->counter, 1);
    strResult += to_string(this->expandedNodes) + ",";
    strResult += to_string(this->optimalSolutionLenght) + ",";
    strResult += to_string(this->duration) + ",";
    strResult += to_string(this->averageHeuristicValue) + ",";
    strResult += to_string(this->initialHeuristicValue);
    cout << strResult;
    // cout << "\nXXX: " << averageHeuristicValue;
    // cout << "\nCounter: " << counter;
}

void Result :: writeResult(string fileName) {
    ofstream outFile;
    outFile.open(fileName, std::ios_base::app);

    string strResult = "";
    strResult += to_string(this->expandedNodes) + ",";
    strResult += to_string(this->optimalSolutionLenght) + ",";
    strResult += to_string(this->duration) + ",";
    strResult += to_string(this->totalHValue/max(this->counter, 1)) + ",";
    strResult += to_string(this->initialHeuristicValue);
    outFile << strResult + "\n";

    outFile.close();
}