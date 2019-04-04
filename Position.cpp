#include "Position.h"
 
using namespace std;

Position :: Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position :: getX() {
    return x;
}

int Position :: getY() {
    return y;
}
