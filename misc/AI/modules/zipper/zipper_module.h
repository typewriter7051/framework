#include "../../module.h"

class ZipperModule : public Module {
public:
    ZipperModule() : zip(false), numBlocks(1), size(0) {}
    ZipperModule(int _size, bool z, int n) : zip(z), numBlocks(n), size(_size) {}

    void initializeParameters(float min, float max) override;

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    void zipVector(float*  inputs, float* outputs, bool z, int n);

    // This is where the actual processing is done.
    void process() override;

    // Settings.
    bool zip; // true if zipping up and false if unzipping.
    int numBlocks; // Number of folds to zip up from.
    int size; // Size of input and output layer.
};