#include <iostream>
#include <string>
#include <exception>

#include <queue>
#include "Matrix.h"

using namespace std;

class NoPossibilitiesException : public exception {
public:
    const int X;
    const int Y;

    NoPossibilitiesException(int x, int y) : X(x), Y(y) {
    }

    const char *what() const noexcept {
        stringstream ss;
        ss << "No more possibilities for field " << this->X << ", " << this->Y;
        char *cstr = &ss.str()[0u];
        return cstr;
    }

};

void checkPosition(Matrix &m, queue<Coordinate> &coords, int x, int y) {
    vector<int> possibleNumbers = m.getPossibleNumbers(x, y);
    if (possibleNumbers.empty()) {
        throw NoPossibilitiesException(x, y);
    } else if (possibleNumbers.size() == 1) {
        for (int i = 0; i < 9; i++) {
            if (i != x) {
                if (m.checkPos(i, y, possibleNumbers[0])) {
                    m.removeNumber(i, y, possibleNumbers[0]);
                    //recursive_delete(m, i, y, possibleNumbers[0]);

                    coords.push(Coordinate{i, y});
                }
            }
        }

        for (int j = 0; j < 9; j++) {
            if (j != y) {
                if (m.checkPos(x, j, possibleNumbers[0])) {
                    m.removeNumber(x, j, possibleNumbers[0]);
                    //recursive_delete(m, x, j, possibleNumbers[0]);

                    coords.push(Coordinate{x, j});
                }
            }
        }

        int blockX = (x / 3) * 3;
        int blockY = (y / 3) * 3;

        for (int i = blockX; i < blockX + 3; i++) {
            for (int j = blockY; j < blockY + 3; j++) {
                if (i != x && j != y) {
                    if (m.checkPos(i, j, possibleNumbers[0])) {
                        m.removeNumber(i, j, possibleNumbers[0]);
                        //recursive_delete(m, i, j, possibleNumbers[0]);


                        coords.push(Coordinate{i, j});
                    }
                }
            }
        }
    }
}

void recursive_delete(Matrix &m, queue<Coordinate> &coords) {
    while (!coords.empty()) {
        Coordinate coord = coords.front();
        coords.pop();

        // cout << "next run: " << coord.x << ", " << coord.y << endl;
        checkPosition(m, coords, coord.x, coord.y);
    }


}

void solveKnown(Matrix &m) {
    set<Coordinate> *toVisit = new set<Coordinate>(m.getSetSpots());
    for (Coordinate c: *toVisit) {
        if (!m.getUnsetSpots().empty()) {
            vector<int> possibleNumbers = m.getPossibleNumbers(c.x, c.y);
            if (possibleNumbers.size() == 1) {
                auto coords = new queue<Coordinate>();

                coords->push(Coordinate{c.x, c.y});
                recursive_delete(m, *coords);

                delete coords;
            }
        } else {
            return;
        }
    }
    delete (toVisit);
}

Matrix *solve(Matrix &m) {
    try {
        solveKnown(m);
    }
    catch (NoPossibilitiesException &e) {
        throw e;
    }

    if (!m.getUnsetSpots().empty()) {
        Coordinate c = *m.getUnsetSpots().begin();
        vector<int> possibleNumbers = m.getPossibleNumbers(c.x, c.y);
        for (int i: possibleNumbers) {
            Matrix *temp = m.copy();

            temp->setExclusiveNumber(c.x, c.y, i);
            try {
                temp = solve(*temp);
            }
            catch (NoPossibilitiesException &e) {
                m.removeNumber(c.x, c.y, i);
                delete (temp);
                continue;
            }
            return temp;
        }
        throw NoPossibilitiesException(c.x, c.y);
    } else {
        return &m;
    }
}

void solveFile(string file){
    cout << "========= Solving " << file << " =========" << endl << endl;
    Matrix *m = new BitMatrix();

    try {
        readFileToMatrix(*m, file);
    } catch (string fail) {
        cout << fail << endl;
    }
    cout << *m << endl;
    try {
        m = solve(*m);
    }
    catch (string fail) {
        cout << fail << endl;
    }
    cout << "| | | | | | | | | |" << endl;
    cout << "v v v v v v v v v v" << endl << endl << endl;
    cout << *m << endl;
}

int main() {
    solveFile("Sudoku_leicht.txt");
    solveFile("Sudoku_schwer.txt");
    solveFile("Sudoku_nonsense.txt");

    return 0;
}