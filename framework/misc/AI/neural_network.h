#include "nn_module.h"

class NeuralNetwork {
public:
    std::vector<float> runNeuralNetwork();
    float getCost();

private:
    std::vector<NNModule> modules;
};