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
#include <set>

using namespace std;

vector<string> split(string line, string delim);

struct Coordinate {
    int x;
    int y;
};

inline bool operator<(const Coordinate &lhs, const Coordinate &rhs) {
    if (lhs.x < rhs.x) {
        return true;
    }
    if (lhs.x == rhs.x) {
        if (lhs.y < rhs.y) {
            return true;
        }
    }
    return false;
}

class Matrix {
public:
    virtual vector<int> getPossibleNumbers(int x, int y)=0;

    virtual bool checkPos(int x, int y, int number)=0;

    /**
     * Modify this matrix at a given position
     * @param x the x coordinate
     * @param y the y coordinate
     * @param number the number to modify
     * @param unset should this number be set or deleted (unset=true)
     */
    virtual void addNumber(int x, int y, int number)=0;

    virtual void removeNumber(int x, int y, int number)=0;

    virtual void setExclusiveNumber(int x, int y, int number)=0;

    virtual set<Coordinate> getUnsetSpots()=0;

    virtual set<Coordinate> getSetSpots()=0;

    friend ostream &operator<<(ostream &os, Matrix &m);

    virtual Matrix *copy()=0;

    string str();
};

void readFileToMatrix(Matrix &m, string filename);

class BitMatrix : public Matrix {
public:
    BitMatrix();

    virtual vector<int> getPossibleNumbers(int x, int y);

    virtual bool checkPos(int x, int y, int number);

    /**
     * Modify this matrix at a given position
     * @param x the x coordinate
     * @param y the y coordinate
     * @param number the number to modify
     * @param unset should this number be set or deleted (unset=true)
     */
    virtual void addNumber(int x, int y, int number);

    virtual void removeNumber(int x, int y, int number);

    virtual void setExclusiveNumber(int x, int y, int number);

    virtual set<Coordinate> getUnsetSpots();

    virtual set<Coordinate> getSetSpots();

    virtual Matrix *copy();

protected:
    void updateUnsetSpots(int x, int y);

private:
    uint16_t storage[COLNUM][ROWNUM];

    set<Coordinate> unsetSpots;
    set<Coordinate> setSpots;
};

#endif //SUDOKUSOLVER_MATRIX_H

