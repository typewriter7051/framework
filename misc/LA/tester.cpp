#include <iostream>
#include "matrix.h"
using namespace LA;

int main() {
    float data[16] = {
        1,  2,  3,  4,
        6,  6,  7,  8,
        9,  11, 11, 12,
        13, 14, 18, 16
    };
    float data2[9] = {
        1, 3, 6,
        0, 2, 9,
        0, 0, 1
    };
    Matrix m(4, 4, data);

    //m.removeRowAndCol(1, 1).printMatrix(1);
    m.printMatrix(1);
    std::cout << "\n inverting matrix.\n";
    m.getInverse().printMatrix(1);

    return 0;
}