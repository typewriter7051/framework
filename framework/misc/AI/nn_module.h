#include <fstream>
#include <string>
#include <vector>
#include <xmmintrin.h> // SIMD functionality.

class NNModule {
public:
    int getNumInputs();
    int getNumOutputs();

    // Draws values from inputs, does some neural network magic, then writes result to outputs.
    void updateValues();
    // derivs is a list containing the derivative of the cost function to each output neuron.
    virtual void trainModule(std::vector<float>* derivs);
    void callReset();
    
    virtual void saveToFile(std::ofstream* file);
    virtual void readFromFile(std::ifstream* file);

protected:
    // Checks if the CPU supports SSE.
    bool SSEsupport();
    // This is where the actual processing is done.
    virtual void process();
    // Gets called at the beginning of every sample.
    // Use this to prepare your module for processing the next sample.
    virtual void reset();
    // Comes with a collection of predefined SIMD-ized activation functions.
    void SIMDActivationFunction(activationfunction_enum);
    std::vector<float>* inputs, outputs;
    std::vector<NNModule*> connectedModules;
    // Just keeps track if the module was already run for the current sample.
    bool alreadyUpdated;

private:
};