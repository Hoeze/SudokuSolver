//
// Created by hoelzlwimmerf on 21.05.18.
//

#include "Matrix.h"

Matrix *readFileToMatrix(string filename) {
    ifstream infile(filename);
    if (infile.fail()) {
        throw "Could not open file!";
    }
    auto *retval = new Matrix();
    int y = 0;
    for (string line; getline(infile, line);) {
        vector<string> linesplit = split(line, " ");

        int x = 0;
        for (const auto &elem : linesplit) {
            int val = stoi(elem);
            if (val < 0) {
                val = 0;
            }
            retval->setPos(x, y, val, false);
            x++;
        }
        y++;
    }
    return retval;
}


Matrix::Matrix() {
    for (int i = 0; i < COLNUM; i++) {
        for (int j = 0; j < ROWNUM; j++) {
            this->storage[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {

}

vector<int> Matrix::getPossibleNumbers(int x, int y) {
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


bool Matrix::checkPos(int x, int y, int number) {
    if (number < 0 || number > 9)
        return false;

    uint16_t val = this->storage[x][y];
    val = val >> (number - 1);
    val = val & (uint16_t) 0x1;
    return val == (uint16_t) 1;
}

void Matrix::setPos(int x, int y, int number, bool unset) {
    if (number < 0 || number > 9)
        return;

    uint16_t mask = 1;
    mask = mask << (number - 1);
    if (unset) {
        mask = ~mask;
        this->storage[x][y] &= mask;
    } else {
        this->storage[x][y] |= mask;
    }
}

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

Matrix Matrix::copy() {
    return Matrix();
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
