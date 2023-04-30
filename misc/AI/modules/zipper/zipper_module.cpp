#include "zipper_module.h"
//==============================================================================

void ZipperModule::initializeParameters(float min, float max) {
    // Nothing to do here...
}
//==============================================================================
void ZipperModule::zipVector(float* _inputs, float* _outputs, bool z, int n) {
    int blockSize = size / n;

    for (int s = 0; s < blockSize; s++) {
        for (int b = 0; b < n; b++) {
            int index1 = s * n + b;
            int index2 = b * blockSize + s;
            // Swap the indeces if unzip.
            if (!z) {
                int temp = index1;
                index1 = index2;
                index2 = temp;
            }
            _outputs[index1] += _inputs[index2];
        }
    }
}

void ZipperModule::process() {
    zipVector(inputs, outputs, zip, numBlocks);
}
//==============================================================================

void ZipperModule::train(float stepSize) {
    // Inverse zip (opposite of whatever zip is set to)
    // from outputs back to inputs.
    zipVector(derivOutputs, derivInputs, !zip, numBlocks);
}
//==============================================================================

void ZipperModule::saveToFile(std::ofstream* file) {
    // Nothing to do here...
}

void ZipperModule::readFromFile(std::ifstream* file) {
    // Nothing to do here...
}
