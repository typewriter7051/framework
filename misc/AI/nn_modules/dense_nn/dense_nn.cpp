#include <cmath>
#include <random>
#include "dense_nn.h"
#include <iostream>
// #include <immintrin.h>
//==============================================================================

/*
neurons is a vector of vectors that holds the values of each neuron in
a neural network, in addition to a 1 at the end for bias.
[y1, y2, ..., ym, 1]
[x1, x2, ..., xn, 1]
...

derivs stores the derivative of the cost w/ respect to each neuron (before applying activation function)
and has almost the same structure except it does not hold a 1's column.

weights is a vector of vectors that holds the weights for each layer as well as bias.
Each layer looks like the following where wij is the weight connecting the ith
output neuron to the jth input neuron and bi is the bias for the ith neuron.
[w11, w12, ..., w1n, b1, w21, w22, ..., w2n, b2, ..., wmn, bm]
*/
DenseNeuralNetwork::DenseNeuralNetwork(std::vector<int> sizes) {
    neurons = std::vector<std::vector<float>>(sizes.size());
    derivs = neurons;
    weights = std::vector<std::vector<float>>(sizes.size() - 1);

    for (int i = 0; i < sizes.size(); i++) {
        // Resize and add 1's column.
        neurons[i].resize(sizes[i] + 1);
        neurons[i][sizes[i]] = 1;

        derivs[i].resize(sizes[i]);
    }
    // Erase the 1 element in the output layer.
    int lastIndex = sizes.size() - 1;
    neurons[lastIndex].erase(neurons[lastIndex].end() - 1);

    for (int i = 0; i < sizes.size() - 1; i++) {
        weights[i].resize((sizes[i] + 1) * sizes[i + 1]);
    }
}
//==============================================================================
c_vecp DenseNeuralNetwork::getOutputs() {
    return &neurons.back();
}

void DenseNeuralNetwork::initializeParameters(float min, float max) {
    std::mt19937 mt;
    std::uniform_real_distribution<> dist(min, max);
    //std::normal_distribution<> (args);
    //std::poisson_distribution<> (args);
    // ...

    // Randomize weights.
    for (int l = 0; l < weights.size(); l++) {
        for (int w = 0; w < weights[l].size(); w++) {
            weights[l][w] = dist(mt);
        }
    }
}

inline void activationFunction(float&, int);
inline void activationFunctionDerivative(float&, int);
///*
void DenseNeuralNetwork::process(c_vecp inputs) {
    // Copy the input vector to the array.
    neurons[0] = *inputs;
    neurons[0].push_back(1); // Re-add the 1's column after copying the inputs vector.

    // For each layer.
    for (int l = 0; l < neurons.size() - 1; l++) {
        // Multiply layer l to layer l+1.
        int numINs = neurons[l].size();         // Include the 1's column in input layer.
        int numONs = neurons[l + 1].size() - 1; // -1 to ignore 1's column in output layer.

        // Reset the values in output layer from previous run.
        std::fill(neurons[l + 1].begin(), neurons[l + 1].end() - 1, 0);
        // Matrix multiplication to output layer.
        for (int on = 0; on < numONs; on++) {
            for (int in = 0; in < numINs; in++) {
                neurons[l + 1][on] += neurons[l][in] * weights[l][on * numINs + in];
            }
        }
        // Activation function.
        for (int on = 0; on < numONs; on++) {
            activationFunction(neurons[l + 1][on], 0);
        }
    }
}
//*/
//==============================================================================

inline void DenseNeuralNetwork::processLayer(int l, float stepSize) {
    int numONs = neurons[l].size() - 1; // Ignore the 1's column in output layer
    int numINs = neurons[l - 1].size(); // but not the input layer.
    
    for (int on = 0; on < numONs; on++) {
        // Calculate derivatives for next layer.
        for (int in = 0; in < numINs - 1; in++) {
            derivs[l - 1][in] += derivs[l][on] * weights[l - 1][on * numINs + in];

        }
        // Move weights (and bias)
        for (int in = 0; in < numINs; in++) {
            weights[l - 1][on * numINs + in] -= derivs[l][on] * neurons[l - 1][in] * stepSize;
        }
    }

    // Finish the calculation for next layer derivatives.
    // (Don't run activation function on input layer)
    if (l > 1)
    for (int in = 0; in < numINs - 1; in++) {
        activationFunctionDerivative(derivs[l - 1][in], 0);
    }
}

c_vecp DenseNeuralNetwork::train(c_vecp d, float stepSize) {
    // Copy derivs to last layer and calculate derivative
    // before activation function.
    derivs[derivs.size() - 1] = *d;
    for (int i = 0; i < d->size(); i++) {
        activationFunctionDerivative(derivs[derivs.size() - 1][i], 0);
    }

    // Reset derivs of hidden layers to 0, but don't erase the
    // newly copied last layer derivs.
    for (int l = 0; l < derivs.size() - 1; l++) {
        std::fill(derivs[l].begin(), derivs[l].end(), 0);
    }

    // Number of layers (excluding input layer).
    int numLayers = neurons.size();
    for (int l = numLayers - 1; l > 0; l--) {
        // Calculate derivative for next layer, then move weights and biases.
        processLayer(l, stepSize);
    }	

    // Return new derivatives vector for the next module.
    return &derivs[0];
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
        case 0: num = 2 / (1 + exp(-2 * num)) - 1; break;
        // Add more here.
        case 1: break;
        default: break;
    }
}

inline void activationFunctionDerivative(float& num, int af) {
    switch (af) {
        // Sigmoid
        case 0: break;
        // Add more here.
        case 1: break;
        default: break;
    }
}
