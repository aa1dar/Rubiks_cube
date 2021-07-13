#ifndef C___RUBIKSCUBE_H
#define C___RUBIKSCUBE_H


#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "Face.h"

using namespace std;



class Cube {
public:

private:
    Face *front;
    Face *back;
    Face *left;
    Face *right;
    Face *up;
    Face *down;
    map<string, void (Cube::*)(int)> translateCom;

    map<char, string> translateAlgorithm;

    vector<Face *> mainCube;

    vector<string> wayToAns;
    vector<string> command;


public:

    Cube();

    void transformCube(const string &);

    bool isValid() const;

    bool isSolved() const;

    void scramble(int);

    vector<Sticker> swith(vector<Sticker>);


    void frontCW(int  = 1);

    void frontCCW(int  = 0);

    void backCW(int = 1);

    void backCCW(int = 0);

    void leftCW(int = 1);

    void leftCCW(int = 0);

    void rightCW(int = 1);

    void rightCCW(int = 0);

    void upCW(int = 1);

    void upCCW(int = 0);


    void downCW(int = 1);

    void downCCW(int = 0);


    stringstream stateOfCube();


    void toSolve();


    const vector<Color> getState() const;

    void setState(vector<Color> &state);

    void writeFile();

    void writeCons();

    void readFile();


};


#endif //C___RUBIKSCUBE_H
