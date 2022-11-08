#include "neural_network.h"
#include <fstream>
#include <cmath>
//==============================================================================

const std::vector<float>* NeuralNetwork::runNeuralNetwork(const std::vector<float>* inputs) {
    // Manually run the first module.
    moduleOrder[0]->process(inputs);

    // Run the rest of the modules passing the output of the previous into the next.
    for (int m = 1; m < moduleOrder.size(); m++) {
        moduleOrder[m]->process(moduleOrder[m - 1]->getOuptuts());
    }

    // Finally return the output of the last module.
    return moduleOrder.back()->getOuptuts();
}
//==============================================================================

float NeuralNetwork::getCost(const std::vector<float>* inputs, const std::vector<float>* expectedOutputs) {
    // Run the network first.
    const std::vector<float>* outputs = runNeuralNetwork(inputs);

    // Residual sum of squares.
    float cost = 0;
    for (int f = 0; f < outputs->size(); f++) {
        float temp = outputs->at(f) - expectedOutputs->at(f);
        cost += temp * temp;
    }
    cost /= outputs->size();
    return sqrt(cost);
}
//==============================================================================

void NeuralNetwork::trainNeuralNetwork(const std::vector<float>* inputs, const std::vector<float>* expectedOutputs, float stepSize) {
    float cost = getCost(inputs, expectedOutputs);

    // Calculate cost with respect to each output neuron.

    // Assign the costs to the output neurons of the last module.

    // Train all except the first module.
    for (float m = moduleOrder.size() - 1; m > 0; m--) {
        moduleOrder[m]->train(moduleOrder[m - 1]->getOuptuts(), stepSize);
    }

    // Train the first module.
    std::vector<float> dummyList(inputs->size());
    moduleOrder[0]->train(&dummyList, stepSize);
}
//==============================================================================

void NeuralNetwork::initialize(std::vector<NNModule*> modules) {
    moduleOrder = modules;
}
//==============================================================================

void NeuralNetwork::saveToFile(std::string fileName) {
    std::ofstream file;
    file.open(fileName);

    for (NNModule* cm : moduleOrder) {
        cm->saveToFile(&file);
    }
}
//==============================================================================

void NeuralNetwork::loadFromFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);

    for (NNModule* cm : moduleOrder) {
        cm->readFromFile(&file);
    }
}