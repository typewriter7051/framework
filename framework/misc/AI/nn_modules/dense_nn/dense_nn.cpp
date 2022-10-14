#include "dense_nn.h"

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