#pragma once

#include <fstream>
#include <string>
#include <vector>

typedef const std::vector<float>* c_vecp;

class Module {
public:
    Module() : inputs(NULL),      outputs(NULL),
               derivInputs(NULL), derivOutputs(NULL) {}

    // Randomizes weights/hidden parameters to a random number between min and max.
    virtual void initializeParameters(float min, float max) = 0;

    REMEMBER TO SET DERIV_INPUTS TOO.
    void setInputs(float* i) { inputs = i; }
    void setOutputs(float* o) { outputs = o; }

    // This is where the actual processing is done.
    // Draw input values from the inputs vector then ADD the result to the outputs vector.
    // The adding is crucial for modules with intersecting(aliasing) outputs.
    virtual void process() = 0;

    // Take the output derivatives, then preform back-propogation (for neural nets at least) and pass the 
    // derivative with respect to the input neurons (before activation function) to the inputs vector.
    // Addition is yet again required for this. DO NOT overwrite the inputs vector, ADD ontop of it.
    virtual void train(float stepSize) = 0;

    virtual void saveToFile(std::ofstream* file) = 0;
    virtual void readFromFile(std::ifstream* file) = 0;

protected:
    // derivOutputs points to the cost derivative of the output layer, which
    // is actually taken as input for backprop. Then after using chain rule the
    // cost derivative of the input layer is sent to derivInputs.
    float *inputs, *outputs, *derivInputs, *derivOutputs;
};
