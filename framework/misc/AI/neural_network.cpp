#include "neural_network.h"
#include <fstream>
//==============================================================================

std::vector<float>* NeuralNetwork::runNeuralNetwork(const std::vector<float>* inputs) {
    moduleOrder[0]->process(inputs);

    for (int m = 1; m < moduleOrder.size(); m++) {
        moduleOrder[m]->process(moduleOrder[m - 1].getOuptuts());
    }

    return moduleOrder.back()->getOuptuts();
}
//==============================================================================

float NeuralNetwork::getCost(std::vector<float>* inputs, std::vector<float>* expectedOutputs) {
    std::vector<float>* outputs = runNeuralNetwork(inputs);

    cost = 0;
    for (int f = 0; f < outputs->size(); f++) {
        float temp = outputs->at(f) - expectedOutputs->at(f);
        cost += temp * temp;
    }

    cost /= outputs->size();
    return sqrt(cost);
}
//==============================================================================

void NeuralNetwork::trainNeuralNetwork(std::vector<float>* inputs, std::vector<float>* expectedOutputs, float stepSize) {
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