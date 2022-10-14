#include <vector>
#include <xmmintrin.h> // SIMD functionality.

class NNModule {
public:
    // Draws values from inputs, does some neural network magic, then writes result to outputs.
    virtual getValues();
    // derivs is a list containing the derivative of the cost function to each output neuron.
    virtual trainModule(std::vector<float>* derivs);

protected:
    // Checks if the CPU supports SSE.
    bool SSEsupport();
    // Comes with a collection of predefined SIMD-ized activation functions.
    void SIMDActivationFunction(activationfunction_enum);
    std::vector<float>* inputs, outputs;

private:
};