#include "pipeline.h"
#include <fstream>
#include <cmath>
//==============================================================================

void Pipeline::run(float* inputs, float* outputs) {
    // Set input and output destinations.
    moduleOrder[0]->setInputs(inputs);
    moduleOrder.back()->setOutputs(outputs);

    // Run each module in order.
    for (Module* m : moduleOrder) {
        m->process();
    }
}
//==============================================================================

std::vector<float> Pipeline::getResiduals(float* inputs, float* expectedOutputs) {

    // Run the network first.
    float outputs[outputSize];
    run(inputs, outputs);
    
    std::vector<float> residuals(outputs->size());
    for (int i = 0; i < outputs->size(); i++) {
        residuals[i] = outputs->at(i) - expectedOutputs[i];
    }

    return residuals;
}
//==============================================================================

float Pipeline::getCost(c_vecp residuals) {
    // Sum of squares.
    float cost = 0;
    for (int i = 0; i < residuals->size(); i++) {
        cost += residuals->at(i) * residuals->at(i);
    }
    cost /= residuals->size();

    return sqrt(cost);
}
//==============================================================================

void Pipeline::trainNeuralNetwork(float* inputs, float* expectedOutputs, float stepSize) {
    std::vector<float> residuals = getResiduals(inputs, expectedOutputs);
    float cost = getCost(&residuals);

    // Calculate cost with respect to each output neuron.
    int n = sizeof(inputs) / sizeof(float);
    std::vector<float> costDerivs(n);
    for (int i = 0; i < n; i++) {
        costDerivs[i] = residuals[i] / (cost * n);
    }

    // Train the last module.
    c_vecp derivs = moduleOrder[moduleOrder.size() - 1]->train(&costDerivs, stepSize);
    // Train the rest of the modules, constantly updating the derivatives pointer.
    for (int m = moduleOrder.size() - 2; m >= 0; m--) {
        derivs = moduleOrder[m]->train(derivs, stepSize);
    }
}
//==============================================================================

// Clear the hidden layers and resize them appropriately.
void Pipeline::reserve(std::vector<int> sizes) {
    layers.clear();
    derivLayers.clear();

    for (int i : sizes) {
        layers.push_back(std::vector<float>(i));
        derivLayers.push_back(std::vector<float>(i));
    }
}

void Pipeline::initialize(std::vector<Module*> modules, float min, float max) {
    moduleOrder = modules;
    for (Module* m : modules) {
        m->initializeParameters(min, max);
    }
}
//==============================================================================

void Pipeline::saveToFile(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::binary);

    for (Module* cm : moduleOrder) {
        cm->saveToFile(&file);
    }
    file.close();
}
//==============================================================================

void Pipeline::loadFromFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName, std::ios::binary);

    for (Module* cm : moduleOrder) {
        cm->readFromFile(&file);
    }
    file.close();
}
