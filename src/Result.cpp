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

void Result :: printResult() {
    cout << "\nDuration: " << this->duration;
    cout << "\nNumber of expanded nodes: " << this->expandedNodes;
    cout << "\nLength of otimal solution: " << this->optimalSolutionLenght;
}