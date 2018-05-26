#include <iostream>
#include <string>

#include <queue>
#include "Matrix.h"

using namespace std;


void checkPosition(Matrix &m, queue<Coordinate> &coords, int x, int y) {
    vector<int> possibleNumbers = m.getPossibleNumbers(x, y);
    if (possibleNumbers.empty()) {
        stringstream ss;
        ss << "No more possibilities for field " << x << ", " << y;
        std::string s = ss.str();
        throw s;
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

void solve(Matrix &m) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (!m.getUnsetSpots().empty()) {
                vector<int> possibleNumbers = m.getPossibleNumbers(x, y);
                if (possibleNumbers.size() == 1) {
                    auto coords = new queue<Coordinate>();

                    coords->push(Coordinate{x, y});
                    recursive_delete(m, *coords);

                    delete coords;
                }
            }else{
                return;
            }
        }
    }
}

int main() {
    Matrix *m = new BitMatrix();

    try {
        readFileToMatrix(*m, "Sudoku_leicht.txt");
    } catch (string fail) {
        cout << fail << endl;
    }
    cout << *m << endl;
    try {
        solve(*m);
    }
    catch (string fail) {
        cout << fail << endl;
    }
    cout << endl << "--------------------" << endl << endl << endl;
    cout << *m << endl;


    return 0;
}