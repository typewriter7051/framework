#pragma once

#include <fstream>
#include <memory>
#include <string>
#include "nn_module.h"

class NeuralNetwork {
public:
    const std::vector<float>* runNeuralNetwork(const std::vector<float>* inputs);
    float getCost(const std::vector<float>* inputs, const std::vector<float>* expectedOutputs);
    void trainNeuralNetwork(const std::vector<float>* inputs, const std::vector<float>* expectedOutputs, float stepSize);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

protected:
    void initialize(std::vector<NNModule*> modules, float min, float max);

private:
    // Order of modules run first to last.
    // For backprop this vector can simply be reversed.
    std::vector<NNModule*> moduleOrder;
};
