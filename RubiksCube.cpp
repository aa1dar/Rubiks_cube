#include <iostream>
#include "RubiksCube.h"
#include "algorithm.hpp"
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <fstream>


using namespace std;

Cube::Cube() : front(new Face(Color::W)),
               back(new Face(Color::Y)),
               left(new Face(Color::G)),
               right(new Face(Color::B)),
               up(new Face(Color::O)),
               down(new Face(Color::R)) {

    mainCube.push_back(front);
    mainCube.push_back(back);
    mainCube.push_back(left);
    mainCube.push_back(right);
    mainCube.push_back(up);
    mainCube.push_back(down);

    command = vector<string>{"U1", "U2", "U3", "D1", "D2", "D3", "F1", "F2", "F3", "L1", "L2", "L3", "R1", "R2", "R3"};

    translateCom["U1"] = &Cube::upCW;
    translateCom["U2"] = &Cube::upCW;
    translateCom["U3"] = &Cube::upCCW;

    translateCom["D1"] = &Cube::downCW;
    translateCom["D2"] = &Cube::downCW;
    translateCom["D3"] = &Cube::downCCW;

    translateCom["F1"] = &Cube::frontCW;
    translateCom["F2"] = &Cube::frontCW;
    translateCom["F3"] = &Cube::frontCCW;

    translateCom["B1"] = &Cube::backCW;
    translateCom["B2"] = &Cube::backCW;
    translateCom["B3"] = &Cube::backCCW;

    translateCom["L1"] = &Cube::leftCW;
    translateCom["L2"] = &Cube::leftCW;
    translateCom["L3"] = &Cube::leftCCW;

    translateCom["R1"] = &Cube::rightCW;
    translateCom["R2"] = &Cube::rightCW;
    translateCom["R3"] = &Cube::rightCCW;


    translateAlgorithm['4'] = 'U';
    translateAlgorithm['1'] = 'B';
    translateAlgorithm['0'] = 'F';
    translateAlgorithm['5'] = 'D';
    translateAlgorithm['2'] = 'L';
    translateAlgorithm['3'] = 'R';


}

void Cube::transformCube(const string &command) {
    int val = 1;
    if (command[1] == '2')
        val = 2;
    (this->*translateCom[command])(val);

}

bool Cube::isValid() const {
    bool center = true;
    vector<bool> corrCenter;


    for (auto &&i: mainCube) {
        if (i->isCenterCorrect())
            corrCenter.push_back(true);
        else
            corrCenter.push_back(false);
    }

    for (auto i:corrCenter)
        center *= i;

    vector<int> vecOfCountOfCol(7);

    for (auto &&i: mainCube) {
        for (auto &&j: i->getCell()) {
            vecOfCountOfCol[(*j).getCol()] += 1;
        }
    }


    int countOfCol = count(vecOfCountOfCol.begin() + 1, vecOfCountOfCol.end(), 9);

    return center && (countOfCol == 6);

}

bool Cube::isSolved() const {
    vector<bool> vecOfSolvedFaces;

    transform(mainCube.begin(), mainCube.end(),
              std::back_inserter(vecOfSolvedFaces),
              [](Face *f) { return f->isSolved(); });

    bool ans = true;
    for (auto i:vecOfSolvedFaces)
        ans *= i;

    return ans;
}

void Cube::scramble(int steps) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 12);


    for (int i = 0; i < steps; i++)
        transformCube(command[dis(gen) - 1]);

}

vector<Sticker> Cube::swith(vector<Sticker> s) {
    Sticker tmp = s[0];
    s[0] = s[2];
    s[2] = tmp;
    return s;
}


void Cube::frontCW(int i) {
    for (int k = 0; k < i; k++) {
        front->rotateCw();

        vector<Sticker> oldVec = up->getRow(3);
        up->setRow(3, swith(left->getColumn(3)));
        left->setColumn(3, down->getRow(1));
        down->setRow(1, swith(right->getColumn(1)));
        right->setColumn(1, oldVec);
    }
};

void Cube::frontCCW(int i) {
    front->rotateCCw();

    vector<Sticker> oldVec = up->getRow(3);
    up->setRow(3, right->getColumn(1));
    right->setColumn(1, swith(down->getRow(1)));
    down->setRow(1, left->getColumn(3));
    left->setColumn(3, swith(oldVec));
}

void Cube::backCW(int i) {
    for (int k = 0; k < i; k++) {
        back->rotateCw();

        vector<Sticker> oldVec = up->getRow(1);
        up->setRow(1, right->getColumn(3));
        right->setColumn(3, swith(down->getRow(3)));
        down->setRow(3, left->getColumn(1));
        left->setColumn(1, swith(oldVec));
    }
}

void Cube::backCCW(int i) {
    back->rotateCCw();

    vector<Sticker> oldVec = up->getRow(1);
    up->setRow(1, swith(left->getColumn(1)));
    left->setColumn(1, down->getRow(3));
    down->setRow(3, swith(right->getColumn(3)));
    right->setColumn(3, oldVec);
}

void Cube::leftCW(int i) {
    for (int k = 0; k < i; k++) {
        left->rotateCw();

        vector<Sticker> oldVec = up->getColumn(1);
        up->setColumn(1, swith(back->getColumn(3)));
        back->setColumn(3, swith(down->getColumn(1)));
        down->setColumn(1, front->getColumn(1));
        front->setColumn(1, oldVec);
    }
}

void Cube::leftCCW(int i) {
    left->rotateCCw();

    vector<Sticker> oldVec = up->getColumn(1);
    up->setColumn(1, front->getColumn(1));
    front->setColumn(1, down->getColumn(1));
    down->setColumn(1, swith(back->getColumn(3)));
    back->setColumn(3, swith(oldVec));
}

void Cube::rightCW(int i) {
    for (int k = 0; k < i; k++) {
        right->rotateCw();

        vector<Sticker> oldVec = up->getColumn(3);
        up->setColumn(3, front->getColumn(3));
        front->setColumn(3, down->getColumn(3));
        down->setColumn(3, swith(back->getColumn(1)));
        back->setColumn(1, swith(oldVec));
    }
}

void Cube::rightCCW(int i) {
    right->rotateCCw();

    vector<Sticker> oldVec = up->getColumn(3);
    up->setColumn(3, swith(back->getColumn(1)));
    back->setColumn(1, swith(down->getColumn(3)));
    down->setColumn(3, front->getColumn(3));
    front->setColumn(3, oldVec);
}

void Cube::upCW(int i) {
    for (int k = 0; k < i; k++) {
        up->rotateCw();

        vector<Sticker> oldVec = front->getRow(1);
        front->setRow(1, right->getRow(1));
        right->setRow(1, back->getRow(1));
        back->setRow(1, left->getRow(1));
        left->setRow(1, oldVec);
    }
}

void Cube::upCCW(int i) {
    up->rotateCCw();

    vector<Sticker> oldVec = front->getRow(1);
    front->setRow(1, left->getRow(1));
    left->setRow(1, back->getRow(1));
    back->setRow(1, right->getRow(1));
    right->setRow(1, oldVec);
}


void Cube::downCW(int i) {
    for (int k = 0; k < i; k++) {
        down->rotateCw();

        vector<Sticker> oldVec = front->getRow(3);
        front->setRow(3, left->getRow(3));
        left->setRow(3, back->getRow(3));
        back->setRow(3, right->getRow(3));
        right->setRow(3, oldVec);
    }
}

void Cube::downCCW(int i) {
    down->rotateCCw();

    vector<Sticker> oldVec = front->getRow(3);
    front->setRow(3, right->getRow(3));
    right->setRow(3, back->getRow(3));
    back->setRow(3, left->getRow(3));
    left->setRow(3, oldVec);
}


stringstream Cube::stateOfCube() {
    stringstream ss;
    vector<string> way;

    way.push_back(to_string(up->getColumn(2)[2].getCol()) + to_string(front->getColumn(2)[0].getCol()));

    way.push_back(to_string(up->getRow(2)[2].getCol()) + to_string(right->getColumn(2)[0].getCol()));

    way.push_back(to_string(up->getColumn(2)[0].getCol()) + to_string(back->getColumn(2)[0].getCol()));

    way.push_back(to_string(up->getRow(2)[0].getCol()) + to_string(left->getColumn(2)[0].getCol()));

    way.push_back(to_string(down->getColumn(2)[0].getCol()) + to_string(front->getColumn(2)[2].getCol()));

    way.push_back(to_string(down->getRow(2)[2].getCol()) + to_string(right->getColumn(2)[2].getCol()));

    way.push_back(to_string(down->getColumn(2)[2].getCol()) + to_string(back->getColumn(2)[2].getCol()));

    way.push_back(to_string(down->getRow(2)[0].getCol()) + to_string(left->getColumn(2)[2].getCol()));

    way.push_back(to_string(front->getRow(2)[2].getCol()) + to_string(right->getRow(2)[0].getCol()));

    way.push_back(to_string(front->getRow(2)[0].getCol()) + to_string(left->getRow(2)[2].getCol()));

    way.push_back(to_string(back->getRow(2)[0].getCol()) + to_string(right->getRow(2)[2].getCol()));
    way.push_back(to_string(back->getRow(2)[2].getCol()) + to_string(left->getRow(2)[0].getCol()));

    way.push_back(to_string(up->getColumn(3)[2].getCol()) + to_string(front->getColumn(3)[0].getCol()) +
                  to_string(right->getColumn(1)[0].getCol())); //ufr

    way.push_back(to_string(up->getColumn(3)[0].getCol()) + to_string(right->getColumn(3)[0].getCol()) +
                  to_string(back->getColumn(1)[0].getCol())); //urb

    way.push_back(to_string(up->getColumn(1)[0].getCol()) + to_string(back->getColumn(3)[0].getCol()) +
                  to_string(left->getColumn(1)[0].getCol())); //ubl

    way.push_back(to_string(up->getColumn(1)[2].getCol()) + to_string(left->getColumn(3)[0].getCol()) +
                  to_string(front->getColumn(1)[0].getCol())); //ulf

    way.push_back(to_string(down->getColumn(3)[0].getCol()) + to_string(right->getColumn(1)[2].getCol()) +
                  to_string(front->getColumn(3)[2].getCol())); //drf

    way.push_back(to_string(down->getColumn(1)[0].getCol()) + to_string(front->getColumn(1)[2].getCol()) +
                  to_string(left->getColumn(3)[2].getCol())); //dfl

    way.push_back(to_string(down->getColumn(1)[2].getCol()) + to_string(left->getColumn(1)[2].getCol()) +
                  to_string(back->getColumn(3)[2].getCol())); //dlb

    way.push_back(to_string(down->getColumn(3)[2].getCol()) + to_string(back->getColumn(1)[2].getCol()) +
                  to_string(right->getColumn(3)[2].getCol())); //dbr

    for (const string &t: way) {
        for (char i: t) {
            ss << translateAlgorithm[i];

        }
        ss << " ";

    }
    return ss;
}


void Cube::toSolve() {
    stringstream is = stateOfCube();

    stringstream os = findAnswer(is);

    string buffer;

    while (os >> buffer) {
        wayToAns.push_back(buffer);
        transformCube(buffer);
        cout << buffer << " ";
    }
    cout << endl;


}


const vector<Color> Cube::getState() const {


    vector<Color> state;
    for (auto &&f : mainCube) {
        for (auto &&c : f->getCell()) {
            state.push_back((*c).getCol());
        }
    }

    return state;


}

void Cube::setState(vector<Color> &state) {
    auto it = state.begin();

    for (auto &&f : mainCube) {
        for (auto &&c : f->getCell()) {
            (*c).setCol(*(it++));
        }
    }


}

void Cube::writeFile() {

    ofstream fout("state.txt");
    vector<Color> state = getState();
    vector<string> side = {"F", "B", "L", "R", "U", "D"};
    int k = 0;
    int l = 0;
    auto t = side.begin();
    fout << (*t) << endl;
    for (auto i:state) {
        k += 1;
        fout << i << ' ';

        if (k == 3) {
            fout << endl;
            k = 0;
            l += 1;
        }
        if (l == 3) {
            l = 0;
            fout << endl;
            if ((++t) != side.end())
                fout << (*t) << endl;
        }

    }
    fout.close();

}

void Cube::writeCons() {


    vector<Color> state = getState();
    vector<string> side = {"F", "B", "L", "R", "U", "D"};
    int k = 0;
    int l = 0;
    auto t = side.begin();
    cout << (*t) << endl;
    for (auto i:state) {
        k += 1;
        cout << i << ' ';

        if (k == 3) {
            cout << endl;
            k = 0;
            l += 1;
        }
        if (l == 3) {
            l = 0;
            cout << endl;
            if ((++t) != side.end())
                cout << (*t) << endl;
        }

    }


}

void Cube::readFile() {
    ifstream fin("../gits/homework6/state1.txt");
    vector<Color> state;

    fin.seekg(0);
    int k = 0;
    string buf;
    fin >> buf;
    int col;
    for (int i = 0; i < 54; i++) {
        k += 1;

        fin >> col;
        state.push_back(Color(col));

        if (k == 3) {
            k = 0;
        }
        if ((i + 1) % 9 == 0) {
            fin >> buf;
        }

    }
    setState(state);

    fin.close();
}




