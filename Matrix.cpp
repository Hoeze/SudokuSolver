//
// Created by hoelzlwimmerf on 21.05.18.
//

#include "Matrix.h"

ostream &operator<<(ostream &os, Matrix &m) {
    for (int row = 0; row < ROWNUM; row++) {
        for (int column = 0; column < COLNUM; column++) {
            vector<int> numbers = m.getPossibleNumbers(column, row);
            if (numbers.size() != 1)
                os << "  ";
            else
                os << numbers[0] << " ";
            if (column == 2 || column == 5)
                os << "|";
        }
        if (row == 2 || row == 5)
            os << endl << "------+------+------";
        os << endl;
    }
    os << endl;
    return os;
}

void readFileToMatrix(Matrix &m, string filename) {
    ifstream infile(filename);
    if (infile.fail()) {
        throw string("Could not open file!");
    }
    int y = 0;
    for (string line; getline(infile, line);) {
        vector<string> linesplit = split(line, " ");

        int x = 0;
        for (const auto &elem : linesplit) {
            int val = stoi(elem);
            if (val > 0) {
                m.setExclusiveNumber(x, y, val);
            }
            x++;
        }
        y++;
    }
}

BitMatrix::BitMatrix() {
    for (int i = 0; i < COLNUM; i++) {
        for (int j = 0; j < ROWNUM; j++) {
            this->storage[i][j] = 0x1FF;
            this->unsetSpots.insert(Coordinate{i, j});
        }
    }
}

vector<int> BitMatrix::getPossibleNumbers(int x, int y) {
    vector<int> retval;

    uint16_t val = this->storage[x][y];
    for (int i = 0; i < 9; i++) {
        uint16_t temp = val;
        temp = temp & (uint16_t) 0x1;
        if (temp == (uint16_t) 1) {
            retval.push_back(i + 1);
        }

        val = val >> 1;
    }
    return retval;
}


bool BitMatrix::checkPos(int x, int y, int number) {
    if (number < 0 || number > 9)
        return false;

    uint16_t val = this->storage[x][y];
    val = val >> (number - 1);
    val = val & (uint16_t) 0x1;
    return val == (uint16_t) 1;
}

void BitMatrix::addNumber(int x, int y, int number) {
    if (number < 0 || number > 9)
        return;

    uint16_t mask = 1;
    mask = mask << (number - 1);
    this->storage[x][y] |= mask;
    this->updateUnsetSpots(x, y);
}


void BitMatrix::removeNumber(int x, int y, int number) {
    if (number < 0 || number > 9)
        return;
    //cout << "del: " << x << ", " << y << ": " << number << endl;
    uint16_t mask = 1;
    mask = mask << (number - 1);
    mask = ~mask;
    this->storage[x][y] &= mask;
    this->updateUnsetSpots(x, y);
}

void BitMatrix::setExclusiveNumber(int x, int y, int number) {
    this->storage[x][y] = 0;
    this->addNumber(x, y, number);
}

set<Coordinate> BitMatrix::getUnsetSpots() {
    return unsetSpots;
}

set<Coordinate> BitMatrix::getSetSpots() {
    return setSpots;
}

Matrix *BitMatrix::copy() {
    BitMatrix *retval = new BitMatrix();
    for (int x = 1; x <= 9; x++) {
        for (int y = 1; y <= 9; y++) {
            retval->storage[x][y] = this->storage[x][y];
        }
    }
    retval->unsetSpots.merge(this->unsetSpots);
    return retval;
}

void BitMatrix::updateUnsetSpots(int x, int y) {
    if (this->getPossibleNumbers(x, y).size() != 1) {
        this->unsetSpots.insert(Coordinate{x, y});
        this->setSpots.erase(Coordinate{x, y});
    } else {
        this->unsetSpots.erase(Coordinate{x, y});
        this->setSpots.insert(Coordinate{x, y});
    }
}

vector<string> split(string line, string delim) {
    vector<string> retval;
    size_t oldPos = 0;
    for (size_t pos = line.find(' ', oldPos); pos != string::npos; pos = line.find(' ', oldPos)) {
        string substr = line.substr(oldPos, pos - oldPos);
        retval.push_back(substr);

        oldPos = pos + 1;
    }
    string lastElem = line.substr(oldPos);
    retval.push_back(lastElem);
    return retval;
}