#include "test_module.h"
//==============================================================================

void DenseNeuralNetwork::trainModule(std::vector<float>* derivs) {

}
//==============================================================================

void DenseNeuralNetwork::saveToFile(std::ofstream* file) {

}

void DenseNeuralNetwork::readFromFile(std::ifstream* file) {

}
//==============================================================================

void DenseNeuralNetwork::process(std::vector<float>* inputs) {
    for (int i = 0; i < inputs.size() i++) {
        outputs[i] = inputs->at(i);
    }
}