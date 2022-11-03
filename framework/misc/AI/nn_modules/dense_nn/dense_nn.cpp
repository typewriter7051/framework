#include "dense_nn.h"
// #include <immintrin.h>
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

    outputs = neurons.back();
}
//==============================================================================

void DenseNeuralNetwork::process(std::vector<float>* inputs) {
    // Multiply input layer to first hidden layer.
    int numINs = inputs->size();
    int numONs = neurons[0].size();
    for (int on = 0; on < numONs; on++) {
        float sum = 0;
        for (int in = 0; in < numINs; in++) {
            sum += inputs->at(in) * weights[0][on * numINs + in];
        }
        neurons[0][on] = sum;
    }
    // Run activation function on first hidden layer.

    // For each layer after the first.
    for (int l = 0; l < weights.size() - 1; l++) {
        // Multiply layer l to layer l+1.
        numINs = neurons[l].size();
        numONs = neurons[l + 1].size();
        for (int on = 0; on < numONs; on++) {
            float sum = 0;
            for (int in = 0; in < numINs; in++) {
                sum += neurons[l][in] * weights[l + 1][on * numINS + in];
            }
            neurons[l + 1][on] = sum;
        }

        // Run activation function on layer l+1.
        // ...
    }
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

void DenseNeuralNetwork::activationFunction(int l) {
    for (int n = 0; n < neurons[l].size(); n += 8) {
        // Default is sigmoid.
    }
}