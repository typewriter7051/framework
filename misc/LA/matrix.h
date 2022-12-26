#include <iostream> // These are just for
#include <iomanip>  // printing the matrix.
#include <vector>

namespace LA {

class Matrix {
public:
    //==========================================================================
    // Constructors.
    Matrix() {}

    Matrix(int i, int j) {
        elements.resize(i * j);
        nrows = i;
        ncols = j;
    }

    Matrix(int i, int j, float* data) {
        elements.resize(i * j);
        nrows = i;
        ncols = j;

        for (int m = 0; m < i; m++) {
            for (int n = 0; n < j; n++) {
                int index = i * m + n;
                elements[index] = data[index];
            }
        }
    }
    //==========================================================================
    // Element-wise operator overloads.

    Matrix operator + (float c) {
        return operation(c, 'a');
    }

    Matrix operator - (float c) {
        return operation(c, 's');
    }

    Matrix operator * (float c) {
        return operation(c, 'm');
    }

    Matrix operator / (float c) {
        return operation(c, 'd');
    }

    // Access operator overload.
    float& operator () (int row, int col) {
        // Use std::vector<>::at() for bounds checking.
        return elements.at(row * ncols + col);
    }
    //==========================================================================
    // Operations.

    // Returns 2 numbers [# of rows, # of cols]
    std::vector<int> getSize() {
        std::vector<int> size = {nrows, ncols};
        return size;
    }

    void printMatrix(int precision) {
        std::cout << std::setprecision(precision);
        std::cout << std::fixed << std::endl;
        for (int r = 0; r < nrows; r++) {
            std::cout << " ";
            for (int c = 0; c < ncols; c++) {
                 std::cout << (*this)(r, c) << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix getTranspose() {
        std::vector<int> size = getSize();
        // Create a matrix with inverted dimensions.
        Matrix A(size[1], size[0]);

        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                A(j, i) = (*this)(i, j);
            }
        }

        return A;
    }

    Matrix removeRowAndCol(int r, int c) {
        std::vector<int> size = getSize();
        Matrix A(size[0] - 1, size[1] - 1);

        for (int i = 0; i < size[0] - 1; i++) {
            for(int j = 0; j < size[1] - 1; j++) {
                int row = i + (i >= r);
                int col = j + (j >= c);
                A(i, j) = (*this)(row, col);
            }
        }

        return A;
    }

    // Assumes matrix of at least 2x2.
    float determinant() {
        // Size check.
        if (nrows != ncols) {return 0;}
        // Base case.
        if (nrows == 2) {
            return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
        }

        float sum = 0;
        int row = 0; // Dummy variable to hold the row.
        int sgn = -1;
        for (int col = 0; col < ncols; col++) {
            // Update the sign.
            sgn *= -1;
            float minor = removeRowAndCol(row, col).determinant();
            sum += (*this)(row, col) * sgn * minor;
        }

        return sum;
    }

    Matrix getAdjugateMatrix() {
        // Switch row and col because its a transposed matrix.
        Matrix A(ncols, nrows);

        int sgn = -1;
        for (int row = 0; row < nrows; row++) {
            for (int col = 0; col < ncols; col++) {
                // Update the sign.
                sgn *= -1;

                A(col, row) = sgn * removeRowAndCol(row, col).determinant();
            }
        }

        return A;
    }

    Matrix getInverse() {
        float det = determinant();
        // If the matrix is singular return an empty matrix.
        if (det == 0) {
            return Matrix(0, 0);
        }
        
        return getAdjugateMatrix() / det;
    }

    // Add scalar*row1 onto row2.
    void type3(float scalar, int row1, int row2) {
        for (int col = 0; col < ncols; col++) {
            (*this)(row2, col) += scalar * (*this)(row1, col);
        }
    }

    Matrix rowEchelon() {
        Matrix A = *this;

        return A;
    }

private:
    std::vector<float> elements;
    int nrows, ncols;
    // Helper function intended to be compiled with optimization to trim out 
    // the switch statement (and vectorize).
    inline Matrix operation(float c, const char mode) {
        Matrix A = *this;
        auto size = getSize();

        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                switch(mode) {
                case 'a':
                    A(i, j) += c;
                    break;
                case 's':
                    A(i, j) -= c;
                    break;
                case 'm':
                    A(i, j) *= c;
                    break;
                case 'd':
                    A(i, j) /= c;
                    break;
                }
            }
        }

        return A;
    }
};

}