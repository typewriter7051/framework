#include "dense_nn.h"
//==============================================================================

DenseNeuralNetwork::DenseNeuralNetwork(std::vector<int> sizes) {
    neurons = std::vector<std::vector<float>>(sizes.size());
    weights = std::vector<std::vector<float>>(sizes.size() - 1);
    biases = std::vector<std::vector<int>>(sizes.size());

    for (int i = 0; i < sizes.size(); i++) {
        neurons[i].resize(sizes[i]);
        biases[i].resize(sizes[i]);
    }
    for (int i = 0; i < sizes.size() - 1; i++) {
        weights[i].resize(sizes[i] * sizes[i + 1]);
    }
}
//==============================================================================

void DenseNeuralNetwork::process(std::vector<float>* inputs) {
    // For each layer except the last.
    for (int l = 0; l < weights.size() - 1; l++) {
        // Multiply layer l to layer l+1.

        // Run activation function on layer l+1.
    }
    // Preform multiplication on last layer and store result to outputs.

    // Run activation function on outputs.
}
//==============================================================================

void DenseNeuralNetwork::trainModule(std::vector<float>* derivs) {

}
//==============================================================================

void DenseNeuralNetwork::saveToFile(std::ofstream* file) {

}

void DenseNeuralNetwork::readFromFile(std::ifstream* file) {

}
//==============================================================================

void DenseNeuralNetwork::multiplyLayers(int l) {
    
}
//==============================================================================

void DenseNeuralNetwork::activationFunction(int l) {
    
}