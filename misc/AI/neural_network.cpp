#include "neural_network.h"
#include <fstream>
#include <cmath>
//==============================================================================

c_vecp NeuralNetwork::runNeuralNetwork(c_vecp inputs) {
    // Manually run the first module.
    moduleOrder[0]->process(inputs);

    // Run the rest of the modules passing the output of the previous into the next.
    for (int m = 1; m < moduleOrder.size(); m++) {
        moduleOrder[m]->process(moduleOrder[m - 1]->getOutputs());
    }

    // Finally return the output of the last module.
    return moduleOrder.back()->getOutputs();
}
//==============================================================================

std::vector<float> NeuralNetwork::getResiduals(c_vecp inputs, c_vecp expectedOutputs) {
    // Run the network first.
    c_vecp outputs = runNeuralNetwork(inputs);
    
    std::vector<float> residuals(outputs->size());
    for (int i = 0; i < outputs->size(); i++) {
        residuals[i] = outputs->at(i) - expectedOutputs->at(i);
    }

    return residuals;
}
//==============================================================================

float NeuralNetwork::getCost(c_vecp residuals) {
    // Sum of squares.
    float cost = 0;
    for (int i = 0; i < residuals->size(); i++) {
        cost += residuals->at(i) * residuals->at(i);
    }
    cost /= residuals->size();

    return sqrt(cost);
}
//==============================================================================

void NeuralNetwork::trainNeuralNetwork(c_vecp inputs, c_vecp expectedOutputs, float stepSize) {
    std::vector<float> residuals = getResiduals(inputs, expectedOutputs);
    float cost = getCost(&residuals);

    // Calculate cost with respect to each output neuron.
    auto n = inputs->size();
    std::vector<float> costDerivs(n);
    for (int i = 0; i < n; i++) {
        costDerivs[n] =  residuals[i] / (cost * n);
    }

    // Train the last module.
    c_vecp derivs = moduleOrder[moduleOrder.size() - 1]->train(&costDerivs, stepSize);
    // Train the rest of the modules, constantly updating the derivatives pointer.
    for (int m = moduleOrder.size() - 2; m >= 0; m--) {
        derivs = moduleOrder[m]->train(derivs, stepSize);
    }
}
//==============================================================================

void NeuralNetwork::initialize(std::vector<NNModule*> modules, float min, float max) {
    moduleOrder = modules;
    for (NNModule* m : modules) {
        m->initializeParameters(min, max);
    }
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
