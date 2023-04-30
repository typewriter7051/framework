#include "../../module.h"

class DenseNeuralNetwork : public Module {
public:
    DenseNeuralNetwork() {}
    DenseNeuralNetwork(std::vector<int> sizes);

    void initializeParameters(float min, float max) override;

    // This is where the actual processing is done.
    void process() override;
    // derivs is a list containing the derivative of the cost function to each output neuron.
    void train(float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    inline void processLayer(int l, float stepSize);

    // Outer dimension is layer index.
    std::vector<std::vector<float>>
    neurons, derivs, weights;
};
