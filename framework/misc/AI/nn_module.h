#include <fstream>
#include <string>
#include <vector>
#include <xmmintrin.h> // SIMD functionality.

class NNModule {
public:
    NNModule();

    const std::vector<float>* getOuptuts();

    // This is where the actual processing is done. Draw input values from the inputs vector
    // then store the result in the outputs vector. 
    virtual void process(const std::vector<float>* inputs);
    // Take the output derivatives, then preform back-propogation and pass the 
    // derivative with respect to the input neurons (before activation function) to the inputs vector.
    virtual void train(const std::vector<float>* inputs, float stepSize);

    virtual void saveToFile(std::ofstream* file);
    virtual void readFromFile(std::ifstream* file);

protected:
    std::vector<float>* inputs, outputs;
};