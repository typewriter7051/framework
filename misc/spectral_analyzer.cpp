#include "spectral_analyzer.h"

//================================================================================
// Getters

unsigned int SpectralAnalyzer::getBufferSize() {

    return bufferSize;

}

unsigned int SpectralAnalyzer::getStackSize() {

    return stackSize;

}

//================================================================================
// Setters

bool SpectralAnalyzer::setBufferSize(unsigned int bs) {

    // If given buffer size is a power of 2.
    if (bs != 0 && (bs & (bs - 1)) == 0) {

        bufferSize = bs;
        return true;

    }
    else {

        // If bs is not a power of 2 then do not assign and return false;
        return false;

    }

}

bool SpectralAnalyzer::setStackSize(unsigned int s) {

    // If given buffer size is a power of 2.
    if (s != 0 && (s & (s - 1)) == 0) {

        stackSize = s;
        return true;

    }
    else {

        // If s is not a power of 2 then do not assign and return false;
        return false;

    }

}
