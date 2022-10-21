#include "../../nn_module.h"

class DenseNeuralNetwork : public NNModule {
public:
    DenseNeuralNetwork() {}
    DenseNeuralNetwork(std::vector<int> sizes);

    // derivs is a list containing the derivative of the cost function to each output neuron.
    void trainModule(std::vector<float>* derivs) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // This is where the actual processing is done.
    void process(std::vector<float>* inputs) override;
    // Gets called at the beginning of every sample.
    // Use this to prepare your module for processing the next sample.
    void reset() override;

    // Outer dimension is layer index.
    // neurons[layer] = matrixMultiply(neurons[layer - 1], weights[layer]) + biases[layer]
    std::vector<std::vector<float>> neurons;
    std::vector<std::vector<float>> biases;
    std::vector<std::vector<float>> weights;
};