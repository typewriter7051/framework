#include <fstream>
#include <string>
#include <vector>
#include <xmmintrin.h> // SIMD functionality.

class NNModule {
public:
    // Draws values from inputs, does some neural network magic, then writes result to outputs.
    virtual std::vectors<float> getValues();
    // derivs is a list containing the derivative of the cost function to each output neuron.
    virtual void trainModule(std::vector<float>* derivs);
    
    virtual void saveToFile(std::ofstream* file);
    virtual void readFromFile(std::ifstream* file);

protected:
    // Checks if the CPU supports SSE.
    bool SSEsupport();
    // Comes with a collection of predefined SIMD-ized activation functions.
    void SIMDActivationFunction(activationfunction_enum);
    std::vector<float>* inputs, outputs;

private:
};