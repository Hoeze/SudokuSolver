#include <iostream>
#include <string>

#include "Matrix.h"

using namespace std;

int main() {
    Matrix *m;

    try {
        m = readFileToMatrix("Sudoku_leicht.txt");
    } catch (char const *fail) {
        cout << fail << endl;
    }
    cout << *m << endl;

    return 0;
}