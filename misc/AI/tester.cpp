#include <iostream>
#include <cassert>
#include "neural_network.h"
#include "nn_modules/test_module/test_module.h"

class TestNeuralNetwork : public NeuralNetwork {
public:
    TestNeuralNetwork(int size) {
        m1 = TestModule(size);
        m2 = TestModule(size);
        m3 = TestModule(size);

        std::vector<NNModule*> moduleOrder {
            &m1, &m2, &m3
        };
        initialize(moduleOrder);
    }

private:
    TestModule m1, m2, m3;
};
//==============================================================================

bool outputsEqualsInputs(TestNeuralNetwork* nn, std::vector<float>* inputs) {
    const std::vector<float>* outputs = nn->runNeuralNetwork(inputs);

    return (&outputs == &inputs);
}
//==============================================================================

int main() {
    TestNeuralNetwork nn(10);
    std::vector<float> inputs(10, 0.5);

    outputsEqualsInputs(&nn, &inputs);

    return 0;
}
