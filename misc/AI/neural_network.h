#pragma once

#include <fstream>
#include <memory>
#include <string>
#include "nn_module.h"

class NeuralNetwork {
public:

    c_vecp runNeuralNetwork(c_vecp inputs);
    std::vector<float> getResiduals(c_vecp inputs, c_vecp expectedOutputs);
    // Takes in a vector of residuals instead of inputs and expectedOutputs so that
    // you can get both residuals and cost by only running the neural net once.
    float getCost(c_vecp residuals);
    void trainNeuralNetwork(c_vecp inputs, c_vecp expectedOutputs, float stepSize);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

protected:
    void initialize(std::vector<NNModule*> modules, float min, float max);

private:
    // Order of modules run first to last.
    // For backprop this vector can simply be reversed.
    std::vector<NNModule*> moduleOrder;
};
