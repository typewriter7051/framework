#include "../../nn_module.h"

class DenseNeuralNetwork : public NNModule {
public:
    DenseNeuralNetwork() {}
    DenseNeuralNetwork(std::vector<int> sizes);

    c_vecp getOutputs() override;
    void initializeParameters(float min, float max) override;

    // This is where the actual processing is done.
    void process(c_vecp inputs) override;
    // derivs is a list containing the derivative of the cost function to each output neuron.
    c_vecp train(c_vecp derivs, float stepSize) override;

    void saveToFile(std::ofstream* file) override;
    void readFromFile(std::ifstream* file) override;

private:
    inline void processLayer(int l, float stepSize);

    // Outer dimension is layer index.
    std::vector<std::vector<float>>
    neurons, derivs, weights;
};
