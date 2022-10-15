#include <fstream>
#include <string>
#include <vector>
#include <xmmintrin.h> // SIMD functionality.

class NNModule {
public:
    NNModule();

    int getNumInputs();
    int getNumOutputs();

    void setIOPtrs(std::vector<float>* i, std::vector<float> o);

    // Draws values from inputs, does some neural network magic, then writes result to outputs.
    void updateValues();
    // derivs is a list containing the derivative of the cost function to each output neuron.
    void trainModule(std::vector<float>* derivs);
    void callReset();
    
    virtual void saveToFile(std::ofstream* file);
    virtual void readFromFile(std::ifstream* file);

protected:
    // Checks if the CPU supports SSE.
    bool SSEsupport();
    // Returns true if this is the first or last time this module is called.
    bool firstCall();
    bool lastCall();
    // This is where the actual processing is done. Draw input values from the inputs vector
    // then store the result in the outputs vector. 
    virtual void process(std::vector<float>* inputs, std::vector<float>* outputs);
    // Gets called at the beginning of every sample.
    // Use this to prepare your module for processing the next sample.
    virtual void reset();
    // Take the output derivatives, then preform back-propogation and pass the 
    // derivative with respect to the input neurons (before activation function) to the i vector.
    virtual void train(std::vector<float>* derivs, std::vector<float>* i);
    // Comes with a collection of predefined SIMD-ized activation functions.
    void SIMDActivationFunction(activationfunction_enum);

private:
    std::vector<float>* inputs, outputs;
    std::vector<float> inputDerivs, outputDerivs;
    std::vector<NNModule*> childModules;
    // How many times this module has been called by other modules.
    int timesCalled;
    // How many times the module (should be) called when the entire neural network runs once.
    int numParents;
};