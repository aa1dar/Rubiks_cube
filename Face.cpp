#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Face.h"


using namespace std;


Face::Face(Color col) :
        cub11(new Sticker(col)),
        cub12(new Sticker(col)),
        cub13(new Sticker(col)),
        cub21(new Sticker(col)),
        cub22(new Sticker(col)),
        cub23(new Sticker(col)),
        cub31(new Sticker(col)),
        cub32(new Sticker(col)),
        cub33(new Sticker(col)) {
    cells.push_back(cub11);
    cells.push_back(cub12);
    cells.push_back(cub13);
    cells.push_back(cub21);
    cells.push_back(cub22);
    cells.push_back(cub23);
    cells.push_back(cub31);
    cells.push_back(cub32);
    cells.push_back(cub33);


    centerCol_ = col;
};

void Face::paint(const Color &col) {
    for (auto i: cells) {
        i->setCol(col);
    }
}

bool Face::isCenterCorrect() const {
    return cub22->getCol() == centerCol_;
}

bool Face::isSolved() const {
    std::vector<bool> isTrue;

    std::transform(cells.begin(), cells.end(),
                   std::back_inserter(isTrue), [this](Sticker *c) { return c->getCol() == centerCol_; });
    bool solved = true;

    for (auto i:isTrue) {
        solved *= i;
    }
    return solved;
}

vector<Sticker *> &Face::getCell() {
    return cells;

}


vector<Sticker> Face::swith(vector<Sticker> s) {
    Sticker tmp = s[0];
    s[0] = s[2];
    s[2] = tmp;
    return s;
}


void Face::rotateCw() {
    vector<Sticker> coll1 = getColumn(1);

    setColumn(1, getRow(3));
    setRow(3, swith(getColumn(3)));
    setColumn(3, getRow(1));
    setRow(1, swith(coll1));
}

void Face::rotateCCw() {
    vector<Sticker> coll1 = getColumn(1);

    setColumn(1, swith(getRow(1)));
    setRow(1, getColumn(3));
    setColumn(3, swith(getRow(3)));
    setRow(3, coll1);
}

vector<Sticker> Face::getColumn(int i) {
    switch (i) {
        case 1:
            return vector<Sticker>{*cub11, *cub21, *cub31};
        case 2:
            return vector<Sticker>{*cub12, *cub22, *cub32};
        case 3:
            return vector<Sticker>{*cub13, *cub23, *cub33};
        default:
            return vector<Sticker>{};
    }
}

void Face::setColumn(int i, const vector<Sticker> &column) {
    switch (i) {
        case 1:
            cub11->setCol(column.at(0).getCol());
            cub21->setCol(column.at(1).getCol());
            cub31->setCol(column.at(2).getCol());
            break;
        case 2:
            cub12->setCol(column.at(0).getCol());
            cub22->setCol(column.at(1).getCol());
            cub32->setCol(column.at(2).getCol());
            break;
        case 3:
            cub13->setCol(column.at(0).getCol());
            cub23->setCol(column.at(1).getCol());
            cub33->setCol(column.at(2).getCol());
            break;
        default:
            return;
    }
}

const vector<Sticker> Face::getRow(int i) {
    switch (i) {
        case 1:
            return vector<Sticker>{*cub11, *cub12, *cub13};
        case 2:
            return vector<Sticker>{*cub21, *cub22, *cub23};
        case 3:
            return vector<Sticker>{*cub31, *cub32, *cub33};

        default:
            return vector<Sticker>{};
    }
}

void Face::setRow(int i, const vector<Sticker> &column) {
    switch (i) {
        case 1:
            cub11->setCol(column.at(0).getCol());
            cub12->setCol(column.at(1).getCol());
            cub13->setCol(column.at(2).getCol());
            break;
        case 2:
            cub21->setCol(column.at(0).getCol());
            cub22->setCol(column.at(1).getCol());
            cub23->setCol(column.at(2).getCol());
            break;
        case 3:
            cub31->setCol(column.at(0).getCol());
            cub32->setCol(column.at(1).getCol());
            cub33->setCol(column.at(2).getCol());
            break;
        default:
            return;
    }
}











