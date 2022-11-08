//================================================================================
// Class Definition

class Matrix {
public:

    Matrix();
    Matrix(unsigned short, unsigned short);
    Matrix(unsigned short[]);

    float get(unsigned short yp, unsigned short xp);
    float getDimensions();

    void set(unsigned short yp, unsigned short xp, float val);

private:

    bool checkInBounds(unsigned short yp, unsigned short xp);

    float elements[][];
    unsigned short x, y;

}

//================================================================================
// Basic operations.

bool sameDimensions(Matrix &a, Matrix &b);
bool isSquare(Matrix &a);

Matrix add(Matrix &a, Matrix &b);
Matrix subtract(Matrix &a, Matrix &b);
Matrix multiply(Matrix &a, Matrix &b);

Matrix transpose(Matrix &a);

//================================================================================
// Selection based operations.

// Returns a matrix containing the selection within a larger matrix.
Matrix getSubmatrix(Matrix &a, int bounds[]);

// Overwrites a subregion within the matrix with another smaller matrix.
void pasteSubmatrix(Matrix &a, Matrix &b, int pos[]);

Matrix addSubmatrix(Matrix &a, Matrix &b, int pos[]);
Matrix subtractSubmatrix(Matrix &a, Matrix &b, int pos[]);
Matrix multiplySubmatrix(Matrix &a, Matrix &b, int pos[]);

//================================================================================
// Wait what?

Matrix exp(Matrix a);
