#include "RubiksCube.h"


int main(){
    Cube c;

    c.readFile();
    c.writeCons();
    c.toSolve();
    c.writeCons();

    return 0;
}
