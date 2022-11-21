#include <iostream>
#include <cassert>
#include "neural_network.h"
#include "nn_modules/test_module/test_module.h"
#include "nn_modules/dense_nn/dense_nn.h"

class TestNeuralNetwork : public NeuralNetwork {
public:
    TestNeuralNetwork(int size) {
        m1 = TestModule(size);
        m2 = TestModule(size);
        m3 = TestModule(size);

	d1 = DenseNeuralNetwork(std::vector<int> {
			size,
			size,
			size,
			size
			});

        std::vector<NNModule*> moduleOrder {
            &m1, &m2, &m3, &d1
        };
        initialize(moduleOrder, -0.1, 0.1);
    }
    
private:
    TestModule m1, m2, m3;
    DenseNeuralNetwork d1;
};
//==============================================================================

bool outputsEqualsInputs(TestNeuralNetwork* nn, std::vector<float>* inputs) {
    const std::vector<float>* outputs = nn->runNeuralNetwork(inputs);

    for (int i = 0; i < inputs->size(); i++) {
	std::cout << inputs->at(i) << " to " << outputs->at(i) << std::endl;
    }

    return (&outputs == &inputs);
}
//==============================================================================

int main() {
    TestNeuralNetwork nn(1024);
    std::vector<float> inputs(1024, 0.9);

    outputsEqualsInputs(&nn, &inputs);

    return 0;
}
