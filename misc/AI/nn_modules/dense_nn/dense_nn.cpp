#include <cmath>
#include <random>
#include "dense_nn.h"
#include <iostream>
// #include <immintrin.h>
//==============================================================================

DenseNeuralNetwork::DenseNeuralNetwork(std::vector<int> sizes) {
    inputDerivs = std::vector<float>(sizes[0]);
    neurons = std::vector<std::vector<float>>(sizes.size() - 1);
    weights = neurons;

    for (int i = 0; i < sizes.size() - 1; i++) {
        weights[i].resize(sizes[i] * sizes[i + 1]);
        neurons[i].resize(sizes[i + 1]);
    }

    // derisv and biases have the exact same structure as neurons.
    derivs = neurons;
    biases = neurons;
}
//==============================================================================

const std::vector<float>* DenseNeuralNetwork::getOutputs() {
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

    // Randomize biases.
    for (int l = 0; l < biases.size(); l++) {
        for (int b = 0; b < biases[l].size(); b++) {
	    biases[l][b] = dist(mt);
	}
    }
}

inline void activationFunction(float&, int);
inline void activationFunctionDerivative(float&, int);
void DenseNeuralNetwork::process(const std::vector<float>* inputs) {
    // SUGGESTION: try copying over the input layer then merging to 1 loop.

    // Multiply input layer to first hidden layer.
    size_t numINs = inputs->size();
    size_t numONs = neurons[0].size();
    for (int on = 0; on < numONs; on++) {
        float sum = 0;
        for (int in = 0; in < numINs; in++) {
            sum += inputs->at(in) * weights[0][on * numINs + in];
        }
	// Add bias.
        neurons[0][on] = sum + biases[0][on];
    }
    // Activation function.
    for (int on = 0; on < numONs; on++) {
        activationFunction(neurons[0][on], 0);
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
	    // Add bias.
            neurons[l + 1][on] = sum + biases[l + 1][on];
        }
	// Activation function.
	for (int on = 0; on < numONs; on++) {
            activationFunction(neurons[l + 1][on], 0);
	}
    }
}
//==============================================================================

const std::vector<float>* DenseNeuralNetwork::train(const std::vector<float>* d, float stepSize) {
    // Need to copy derivs to last layer.
    derivs[derivs.size() - 1] = d;

    // Reset derivs to 0.
    for (int l = 0; l < derivs.size(); l++) {
	std::fill(derivs[l].begin(), derivs[l].end(), 0);
    }
    std::fill(inputDerivs.begin(), inputDerivs.end(), 0);

    for (int l = weights.size() - 1; l > 0; l--) {
        int numONs = neurons[l].size();
        int numINs = neurons[l - 1].size();

        for (int on = 0; on < numONs; on++) {
	    // Move weights
	    for (int in = 0; in < numINs; in++) {
		weights[l][on * numINs + in] -= derivs[l][on] * neurons[l - 1][in] * stepSize;
	    }
	    // Move biases
            biases[l][on] -= derivs[l - 1][on] * stepSize;
	    // Calculate derivatives for next layer.
	    for (int in = 0; in < numINs; in++) {
		derivs[l - 1][in] += derivs[l][on] * weights[l][on * numINs + in];
	    }
        }
	
	// Finish the calculation for next layer derivatives.
	for (int in = 0; in < numINs; in++ {
            activationFunctionDerivative(derivs[l - 1][in]);
	}
    }	

    // Multiply first hidden layer to input layer.
    int numINs = inputDerivs.size();
    for (int on = 0; on < neurons[0].size(); on++) {
        for (int in = 0; in < numINs; in++) {
	    inputDerivs[in] += derivs[0][on] * weights[0][on * numINs + in];
	}
    }

    for (int in = 0; in < inputDerivs.size(); in++) {
        activationFunctionDerivative(inputDerivs[in]);
    }
    // Return new derivatives vector for the next module.
    return inputDerivs;
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
        case 0: num = 1 / (1 + exp(-num)); break;
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
