#include "dense_nn.h"
// #include <immintrin.h>
//==============================================================================

DenseNeuralNetwork::DenseNeuralNetwork(std::vector<int> sizes) {
    neurons = std::vector<std::vector<float>>(sizes.size());
    weights = std::vector<std::vector<float>>(sizes.size() - 1);
    biases = std::vector<std::vector<float>>(sizes.size());

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

void DenseNeuralNetwork::process(const std::vector<float>* inputs) {
    // SUGGESTION: try copying over the input layer then merging to 1 loop.

    // Multiply input layer to first hidden layer.
    int numINs = inputs->size();
    int numONs = neurons[0].size();
    for (int on = 0; on < numONs; on++) {
        float sum = 0;
        for (int in = 0; in < numINs; in++) {
            sum += inputs->at(in) * weights[0][on * numINs + in];
        }
        neurons[0][on] = sum + biases[0][on];
        // Sigmoid activation.
        neurons[0][on] = 1 / (1 + exp(-neurons[0][on]));
    }

    // For each layer after the first.
    for (int l = 0; l < weights.size() - 1; l++) {
        // Multiply layer l to layer l+1.
        numINs = neurons[l].size();
        numONs = neurons[l + 1].size();
        for (int on = 0; on < numONs; on++) {
            float sum = 0;
            for (int in = 0; in < numINs; in++) {
                sum += neurons[l][in] * weights[l + 1][on * numINs + in];
            }
            neurons[l + 1][on] = sum + biases[l + 1][on];
            // Sigmoid activation.
            activationFunction(neurons[l + 1][on], 0);
        }
    }
}
//==============================================================================

void DenseNeuralNetwork::train(const std::vector<float>* derivs, float stepSize) {

}
//==============================================================================

void DenseNeuralNetwork::saveToFile(std::ofstream* file) {

}

void DenseNeuralNetwork::readFromFile(std::ifstream* file) {

}

//==============================================================================

inline void activationFunction(float& num, int af) {
    switch (af) {
        // Sigmoid
        case (0): num = 1 / (1 + exp(-num)); break;
        // Add more here.
        case (1): break;
        default: break;
    }
}