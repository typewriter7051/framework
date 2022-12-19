#include <iostream>
#include <cassert>
#include <random>
#include <vector>
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
        // Run the pipeline from first to last.
        std::vector<NNModule*> moduleOrder {
            &m1, &m2, &m3, &d1
        };
        initialize(moduleOrder, -1, 1);
    }
    
private:
    TestModule m1, m2, m3;
    DenseNeuralNetwork d1;
};
//==============================================================================
std::vector<float> generateData(int n) {
    std::mt19937 mt;
    //std::uniform_real_distribution<> dist(0, 1);
    std::normal_distribution<> dist(0, 100);

    std::vector<float> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = dist(mt);
    }

    return data;
}

//==============================================================================

void runPipeline() {
    int size = 256;
    TestNeuralNetwork nn(size);

    std::vector<float> inputs = generateData(size);
    for (int i = 0; i < 64 * 64; i++) {
        nn.runNeuralNetwork(&inputs);
    }
    const std::vector<float>* outputs = nn.runNeuralNetwork(&inputs);

//    for (int i = 0; i < inputs->size(); i++) {
//        std::cout << inputs->at(i) << " to " << outputs->at(i) << std::endl;
//    }
    std::cout << inputs[0] << " and " << outputs->at(0) << std::endl;
}
//==============================================================================

void trainPipeline() {
    int size = 256;
    TestNeuralNetwork nn(size);

    std::vector<float> inputs = generateData(size);
    for (int i = 0; i < 64 * 64; i++) {
        nn.trainNeuralNetwork(&inputs, &inputs, 0.1);
    }
}
//==============================================================================
int main() {
    //runPipeline();
    trainPipeline();

    return 0;
}
