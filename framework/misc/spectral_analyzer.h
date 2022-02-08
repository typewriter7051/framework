#include <vector>

class SpectralAnalyzer {
public:

    //--------------------------------------------------------------------------------
    // Getters

    unsigned int getBufferSize();

    unsigned int getStackSize();

    //--------------------------------------------------------------------------------
    // Setters

    bool setBufferSize(unsigned int bs);

    void setStackSize();

    void addBuffer();

private:

    // bufferSize is the size of each buffer getting added to the stack.
    // The stack is the larger pool of samples to be analyzed.
    unsigned int bufferSize, stackSize;

    

};
