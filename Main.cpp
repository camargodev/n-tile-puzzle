#include<iostream>
#include <stdlib.h> 
#include <vector>
#include <deque>
#include <bitset>
#include "headers/ManhattanDistance.h"
#include "headers/StateManager.h"
 
using namespace std;

int main()
{
    StateManager stateManager;
    ManhattanDistance manhattanCalculator3x3(3);
    ManhattanDistance manhattanCalculator4x4(4);

    deque<PackedState> states;
    states.push_back(1);
    states.push_back(2);
    states.push_back(3);
    states.push_back(4);
    for (auto state : states)
        cout << state;

    states.pop_front();
    for (auto state : states)
        cout << state;
    cout << "\n\n";
    return 0;
    
}


