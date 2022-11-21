#pragma once

#include <fstream>
#include <string>
#include <vector>

class NNModule {
public:
    NNModule() {}

    virtual const std::vector<float>* getOutputs() = 0;
    // Randomizes weights to a random number between min and max.
    virtual void initializeParameters(float min, float max) = 0;

    // This is where the actual processing is done. Draw input values from the inputs vector
    // then store the result in the outputs vector. 
    virtual void process(const std::vector<float>* inputs) = 0;
    // Take the output derivatives, then preform back-propogation and pass the 
    // derivative with respect to the input neurons (before activation function) to the inputs vector.
    virtual const std::vector<float>* train(const std::vector<float>* inputs, float stepSize) = 0;

    virtual void saveToFile(std::ofstream* file) = 0;
    virtual void readFromFile(std::ifstream* file) = 0;
};
