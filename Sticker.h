#ifndef C___STICKER_H
#define C___STICKER_H


enum Color {
    W = 0,
    Y = 1,
    G = 2,
    B = 3,
    O = 4,
    R = 5
};

class Sticker {

private:
    Color color_;
public:

    Sticker();

    Sticker(Color &);

    void setCol(const Color &);

    const Color &getCol() const;

};


#endif //C___STICKER_H
