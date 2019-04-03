#include<iostream>
#include<math.h>  
#include <stdlib.h> 
 
using namespace std;
 
class Position {

private:
    int x;
    int y;

public:
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class ManhattanDistance {

public:

    int calculate(int state[9]) {
        int distance = 0;
        for (int i = 0; i < 9; i++) {
            Position currentPosition = getCurrentPositionForIndex(i);
            Position expectedPosition = getExpectedPositionForNumber(state[i]);
            distance += abs(currentPosition.getX() - expectedPosition.getX());
            distance += abs(currentPosition.getY() - expectedPosition.getY());
        }
        return distance;
    }
    
private:

    // given a number, returns the position where the number is on S*
    Position getExpectedPositionForNumber(int number) {
        int x = (int) floor(number/3);
        int y = number - 3*x;
        return Position(x, y);
    }

    // given an index, returns the position in a 3x3 matrix
    // for example: 0 -> 0,0; 1 -> 0,1; ... 5 -> 1,2; ... 8 -> 2,2;
    Position getCurrentPositionForIndex(int index) {
        int y = index % 3;
        int x = (int) (index-y)/3;
        return Position(x, y);
    }
};


 
int main()
{
    ManhattanDistance manhattanDistance;
    int state[9] = {8, 1, 2, 3, 4, 5, 6, 7, 0};
    int distance = manhattanDistance.calculate(state);
    cout << "Distance for state is " << distance << "\n";
    return 0;
}
