#include "Sticker.h"


Sticker::Sticker(Color &col) {
    this->color_ = col;
};

void Sticker::setCol(const Color &col) {
    this->color_ = col;
}

const Color &Sticker::getCol() const {
    return this->color_;
}




