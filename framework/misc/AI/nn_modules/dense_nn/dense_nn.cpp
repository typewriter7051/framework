#include "dense_nn.h"
#include <immintrin.h>
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

    // Run activation function on first hidden layer.

    // For each layer after the first.
    for (int l = 0; l < weights.size() - 1; l++) {
        // Multiply layer l to layer l+1.
        
        // Run activation function on layer l+1.
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
// l = 0 would be the first hidden layer.
// l < neurons.size() - 1.
void DenseNeuralNetwork::multiplyLayers(int l) {
    int size = neurons[l].size();
    for (int on = 0; on < neurons[l + 1].size(); on++) {
        // Neurons, Weights, temp, Sum.
        __m256 n, w, t, s;

        // Dot product of the 8 value chunk.
        int weightsIndex = size * on;
        for (int in = 0; in < size; in += 8) {
            n = _mm256_load_ps(&neurons[l][in]);
            w = _mm256_load_ps(&weights[l + 1][weightsIndex + in]);
            // _mm256_dp_ps is not optimal for large arrays.
            t = _mm256_mult_ps(n, w);
            s = _mm256_add_ps(s, t);
        }

        float hSum = 0;
        // sum of all values in s.
        neurons[l + 1][on] = hSum;
    }
}
//==============================================================================

void DenseNeuralNetwork::activationFunction(int l) {
    for (int n = 0; n < neurons[l].size(); n += 8) {
        // Default is sigmoid.
    }
}