//
// Created by hoelzlwimmerf on 21.05.18.
//
#ifndef COLNUM
#define COLNUM 9
#endif

#ifndef ROWNUM
#define ROWNUM 9
#endif

#ifndef SUDOKUSOLVER_MATRIX_H
#define SUDOKUSOLVER_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

vector<string> split(string line, string delim);

class Matrix {
public:
    Matrix();

    virtual ~Matrix();

    vector<int> getPossibleNumbers(int x, int y);

    bool checkPos(int x, int y, int number);

    /**
     * Modify this matrix at a given position
     * @param x the x coordinate
     * @param y the y coordinate
     * @param number the number to modify
     * @param unset should this number be set or deleted (unset=true)
     */
    void setPos(int x, int y, int number, bool unset);
    friend ostream &operator<<(ostream &os, Matrix &m);

    Matrix copy();

private:
    uint16_t storage[COLNUM][ROWNUM];
};


Matrix * readFileToMatrix(string filename);

#endif //SUDOKUSOLVER_MATRIX_H


