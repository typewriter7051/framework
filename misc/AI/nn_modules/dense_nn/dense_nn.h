#include "../../nn_module.h"

class DenseNeuralNetwork : public NNModule {
public:
    DenseNeuralNetwork() {}
    DenseNeuralNetwork(std::vector<int> sizes);

    const std::vector<float>* getOutputs() override;
    void initializeParameters(float min, float max) override;

    // This is where the actual processing is done.
    void process(const std::vector<float>* inputs) override;
    // derivs is a list containing the derivative of the cost function to each output neuron.
    const std::vector<float>* train(const std::vector<float>* derivs, float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    // Outer dimension is layer index.
    std::vector<std::vector<float>>
    neurons, dervis,
    biases, weights;

    std::vector<float> inputDerivs;
};
