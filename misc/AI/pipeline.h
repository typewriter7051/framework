#pragma once

#include <fstream>
#include <memory>
#include <string>
#include "module.h"

class Pipeline {
public:
    void run(float* inputs, float* outputs);
    std::vector<float> getResiduals(float* inputs, float* expectedOutputs);
    // Takes in a vector of residuals instead of inputs and expectedOutputs so that
    // you can get both residuals and cost by only running the neural net once.
    float getCost(c_vecp residuals);
    void trainNeuralNetwork(float* inputs, float* expectedOutputs, float stepSize);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

protected:
    // Allocates memory for layers and derivLayers.
    void reserve(std::vector<int> sizes);
    void initialize(std::vector<Module*> modules, float min, float max);

    // Order of modules run first to last.
    // For backprop this vector can simply be reversed.
    std::vector<Module*> moduleOrder;

    std::vector<std::vector<float>> layers, derivLayers;
};

/*

class DemoPipeline : public Pipeline {
public:
    DemoPipeline() {
        reserve(std::vector<int> {10, 5, 10});

        connect(l1, layers[0], layers[1]);
        connect(l2, layers[1], layers[2]);
        connect(l2, layers[0], layers[2]);

        intialize(std::vector<Module*> {l1, l2, l3});
    }

private:
    Layer l1, l2, l3;
}

*/