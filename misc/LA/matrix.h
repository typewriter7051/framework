namespace LA {

class Matrix {
public:
    float elements[][];

    //==========================================================================
    // Constructors.
    Matrix() {}

    Matrix(int i, int j) {
        elements = float[i][j];
    }

    Matrix(float data[][]) {
        elements = data;
    }

    Matrix(int m, int n, float* data) {
        elements = float[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                elements[i][j] = data[m * i + j];
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
    //==========================================================================
    // Operations.

    // Returns 2 numbers [# of rows, # of cols]
    int[] getSize() {
        int size[2];
        size[0] = sizeof(A) / sizeof(A[0]);
        size[1] = sizeof(A[0]) / sizeof(A[0][0]);

        return size;
    }

    Matrix getTranspose() {
        int[] size = getSize();
        // Create a matrix with inverted dimensions.
        Matrix A(size[1], size[0]);

        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                A[j][i] = elements[i][j];
            }
        }

        return A;
    }

    Matrix removeRowAndCol(int r, int c) {
        int size[] = getSize();
        Matrix A(size[0] - 1, size[1] - 1);

        for (int i = 0; i < size[0] - 1; i++) {
            for(int j = 0; j < size[1] - 1; j++) {
                A[i][j] = elements[i + (i >= r)][j + (j >= c)];
            }
        }

        return A;
    }

    // If checkZeros is true, the matrix will be searched to see which row/col
    // has the most 0's to iterate through. This can save some time in sparse matrices.
    float determinant(bool checkZeros) {
        int[] size = getSize();
        // iterpos keeps track of which row/col to iterate through.
        // This is how each row/col is mapped to index in a m by n matrix.
        /*
          m . . . m+n-1
        0
        .   .     .
        .     .   .
        .       . .
      m-1   . . .
        */
        int iterpos = 0;
        if (checkZeros) {
            // Keep track of how many zeros in each row/col.
            int numZeros[size[0] + size[1]];

            for (int i = 0; i < size[0]; i++) {
                for (int j = 0; j < size[1]; j++) {
                    bool isZero = (elements[i][j] == 0);
                    numZeros[i] += isZero;
                    numZeros[size[0] + j] += isZero;
                }
            }

            // Set interpos to the row/col with the most 0's.
            int maxIdx = 0;
            for (int i = 0; i < size[0] + size[1]; i++) {
                if (numZeros[i] > numZeros[maxIdx]) {
                    maxIdx = i;
                }
            }
            iterpos = maxIdx;
        }

        if (iterpos < size[0]) {
            // Iterate along row iterpos.
        } else {
            // Iterate along column iterpos - m.
        }
    }


private:
    // Helper function intended to be compiled with optimization to trim out 
    // the switch statement (and vectorize).
    inline Matrix operation(float c, const char mode) {
        Matrix A = *this;
        int[] size = getSize();

        for (int i = 0; i < size[0]; i++) {
            for (int j = 0; j < size[1]; j++) {
                switch(mode):
                case 'a':
                    A[i][j] += c;
                    break;
                case 's':
                    A[i][j] -= c;
                    break;
                case 'm':
                    A[i][j] *= c;
                    break;
                case 'd':
                    A[i][j] /= c;
                    break;
            }
        }

        return A;
    }
};

}