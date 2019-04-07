#include <iostream>
#include "../headers/Result.h"

using namespace std;

void Result :: increaseExpandedNodes() {
    this->expandedNodes++;
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

void Result :: printResult() {
    cout << "\nNumber of expanded nodes: " << this->expandedNodes;
    cout << "\nLength of otimal solution: " << this->optimalSolutionLenght;
    cout << "\nDuration: " << this->duration;
    cout << "\nInitial state heuristic value: " << this->initialHeuristicValue;
    cout << "\nAverage heuristic value: " << (float) this->totalHValue/this->expandedNodes;
}