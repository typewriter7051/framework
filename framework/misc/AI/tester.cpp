#include <iostream>
#include <cassert>
#include "neural_network.h"
#include "test_module/test_module.h"

class TestNeuralNetwork : public NeuralNetwork {
    TestNeuralNetwork::TestNeuralNetwork(int size) {
        m1 = TestModule(size);
        m2 = TestModule(size);
        m3 = TestModule(size);

        initialize(std::vector<NNModule*>{
            m1, m2, m3
        }); 
    }

private:
    TestModule m1, m2, m3;
}
//==============================================================================

bool OutputsEqualsInputs(TestNeuralNetwork* nn, std::vector<float>* inputs) {
    std::vector<float>* outputs = nn->runNeuralNetwork(inputs);

    return (&outputs == &inputs);
}
//==============================================================================

int main() {
    TestNeuralNetwork nn(10);
    std::vector<float> inputs(10, 0.5);

    assert(OutputsEqualsInputs(&nn, &inputs));

    return 0;
}