#include "../../nn_module.h"

class DenseNeuralNetwork : public NNModule {
public:
    DenseNeuralNetwork() {}
    DenseNeuralNetwork(std::vector<int> sizes);

    // This is where the actual processing is done.
    void process(const std::vector<float>* inputs) override;
    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(const std::vector<float>* derivs, float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // Outer dimension is layer index.
    // neurons[layer] = matrixMultiply(neurons[layer - 1], weights[layer]) + biases[layer]
    std::vector<std::vector<float>> neurons;
    std::vector<std::vector<float>> biases;
    std::vector<std::vector<float>> weights;
};