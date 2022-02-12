#include <iostream>
#include "matrix.h"

//================================================================================
// Class Definition

Matrix::Matrix() {

}

Matrix::Matrix(unsigned short yp, unsigned short xp) {

    x = xp;
    y = yp;

    float e[y][x];
    elements = e;

}

Matrix::Matrix(unsigned short dims[]) {

    x = dims[1];
    y = dims[0];

    float e[y][x];
    elements = e;

}

float Matrix::get(unsigned short yp, unsigned short xp) {

    if (!checkInBounds(yp, xp)) return -1;

    return elements[y][x];

}

// Returns a 2 element array with y and x dimensions.
unsigned short[] Matrix::getDimensions() {

    unsigned short d[2];
    d[0] = y;
    d[1] = x;

    return d;

}

void Matrix::set(unsigned short yp, unsigned short xp, float val) {

    if (checkInBounds(yp, xp))
        elements[yp][xp] = val;

}

bool Matrix::checkInBounds(unsigned short yp, unsigned short xp) {

    if (yp >= y || yp < 0 || xp >= x || xp < 0) {

        std::cout << "\nMATRIX INDEX OUT OF BOUNDS!\n";
        return false;

    }

    else
        return true;

}

//================================================================================
// Basic operations.

bool sameDimensions(Matrix &a, Matrix &b) {

    unsigned short adim = a.getDimensions();
    unsigned short bdim = b.getDimensions();

    if (adim[0] == bdim[0] && adim[1] == bdim[1])
        return true;

    else {

        std::cout << "\nDIMENSIONS DO NOT MATCH!\n";
        return false;

    }

}

Matrix add(Matrix &a, Matrix &b) {

    if (!sameDimensions(a, b)) return;

    Matrix m(a.getDimensions());
    unsigned short temp = 0;

    for (int i = 0; i < a.getDimensions()[0]; i++) {
        for (int j = 0; j < a.getDimensions()[1]) {

            temp = a.get(i, j) + b.get(i, j);
            m.set(i, j, temp);

        }
    }

    return m;

}

Matrix subtract(Matrix &a, Matrix &b) {

    if (!sameDimensions(a, b)) return;

    Matrix m(a.getDimensions());
    unsigned short temp = 0;

    for (int i = 0; i < a.getDimensions()[0]; i++) {
        for (int j = 0; j < a.getDimensions()[1]) {

            temp = a.get(i, j) - b.get(i, j);
            m.set(i, j, temp);

        }
    }

    return m;

}

Matrix multiply(Matrix &a, Matrix &b) {

    unsigned short adim = a.getDimensions();
    unsigned short bdim = b.getDimensions();

    if (adim[1] != bdim[0]) {

        std::cout << "\nDIMENSIONS DO NOT MATCH!\n";
        return;

    }

    Matrix m(adim[0], bdim[1]);

    // Number of elements in each dot product.
    unsigned short dotSize = adim[1];

    for (int i = 0; i < adim[0]; i++) {
        for (int j = 0; j < bdim[1]; j++) {

            float temp = 0;

            // Preform dot product.
            for (int d = 0; d < dotSize; d++) {

                temp += a.get(i, d) * b.get(d, j);

            }

            m.set(i, j, temp);

        }
    }

    return m;

}

Matrix transpose(Matrix &a) {

    if (a.getDimensions()[0] != a.getDimensions()[1]) {

        std::cout << "\nDIMENSIONS DO NOT MATCH!\n";
        return;

    }

    for (int i = 0; i < a.getDimensions()[0]; i++) {



    }

}
