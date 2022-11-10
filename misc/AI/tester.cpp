#include <cassert>
#include "neural_network.h"
#include "nn_modules/test_module/test_module.h"

class TestNeuralNetwork : public NeuralNetwork {
public:
    TestNeuralNetwork(int size) {
        m1 = new TestModule(size);
        m2 = new TestModule(size);
        m3 = new TestModule(size);

        std::vector<NNModule*> moduleOrder {
            m1, m2, m3
        };
        initialize(moduleOrder);
    }
    
    ~TestNeuralNetwork() {
	delete m1;
	delete m2;
	delete m3;
    }

private:
    TestModule *m1, *m2, *m3;
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
