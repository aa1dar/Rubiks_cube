#ifndef C___FACE_H
#define C___FACE_H

#include "Sticker.h"
#include <vector>

using namespace std;

class Face {
private:

    vector<Sticker *> cells;
    Sticker *cub11;
    Sticker *cub12;
    Sticker *cub13;
    Sticker *cub21;
    Sticker *cub22;
    Sticker *cub23;
    Sticker *cub31;
    Sticker *cub32;
    Sticker *cub33;
    Color centerCol_;

public:


    Face(Color col);

    void paint(const Color &);


    bool isCenterCorrect() const;

    bool isSolved() const;

    vector<Sticker *> &getCell();


    vector<Sticker> swith(vector<Sticker>);


    void rotateCw();

    void rotateCCw();

    vector<Sticker> getColumn(int);

    void setColumn(int, const vector<Sticker> &);

    const vector<Sticker> getRow(int);

    void setRow(int, const vector<Sticker> &);
};

#endif //C___FACE_H
