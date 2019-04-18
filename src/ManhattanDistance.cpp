#include<iostream>
#include<math.h>  
#include <stdlib.h> 
#include <vector>
#include <array>
#include "../headers/ManhattanDistance.h"
 
using namespace std;

int ManhattanDistance :: calculate(PackedState state) {
    int distance = 0;
    uint64_t mask = 15;
    for (int i = 0; i < numberOfTiles*numberOfTiles; i++) {
        uint64_t currentNumber = state & mask;
        currentNumber = currentNumber >> 4*i;
        int intNumber = currentNumber;
        if (intNumber > 0) {
            int expectedPosition = getExpectedPositionForNumber(intNumber);
            int currentDistance = calculateDistanceBeetwenPositions(expectedPosition, i);
            distance += currentDistance;
        }
        mask = mask << 4;
    }
    return distance;
}

// given a number, returns the position where the number should be
int ManhattanDistance :: getExpectedPositionForNumber(int number) {
    return (numberOfTiles*numberOfTiles) - number - 1;
}

int ManhattanDistance :: calculateDistanceBeetwenPositions(int pos1, int pos2) {
    int pos1x = (int) floor(pos1/numberOfTiles);
    int pos1y = pos1 - numberOfTiles*pos1x;

    int pos2x = (int) floor(pos2/numberOfTiles);
    int pos2y = pos2 - numberOfTiles*pos2x;

    int horizontalDistance = abs(pos1x - pos2x);
    int verticalDistance = abs(pos1y - pos2y);

    return horizontalDistance + verticalDistance;
}

void ManhattanDistance :: setNumberOfTiles(int numberOfTiles) {
    this->numberOfTiles = numberOfTiles;
}
