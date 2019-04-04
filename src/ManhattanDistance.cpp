#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include "../headers/ManhattanDistance.h"
 
using namespace std;

ManhattanDistance :: ManhattanDistance(short numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
}

int ManhattanDistance :: calculate(PackedState state) {
    int distance = 0;
    for (int i = 0; i < numberOfTiles; i++) {
        for (int j = 0; j < numberOfTiles; j++) {
            // if (state[i][j] != 0) {
            //     Position expectedPosition = getExpectedPositionForNumber(state[i][j]);
            //     distance += abs(i - expectedPosition.x);
            //     distance += abs(j - expectedPosition.y);
            // }
        }
    }
    return distance;
}

// given a number, returns the position where the number should be
Position ManhattanDistance :: getExpectedPositionForNumber(int number) {
    Position expectedPosition;
    expectedPosition.x = (int) floor(number/numberOfTiles);
    expectedPosition.y = number - numberOfTiles*expectedPosition.x;
    return expectedPosition;
}
