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
        int comp = 16;

	    d1 = DenseNeuralNetwork(std::vector<int> {
			size,
			size / comp
		});

        m1 = TestModule(size / comp);
        m2 = TestModule(size / comp);
        m3 = TestModule(size / comp);

	    d2 = DenseNeuralNetwork(std::vector<int> {
			size / comp,
			size
		});

        // Run the pipeline from first to last.
        std::vector<NNModule*> moduleOrder {
            &d1, &m1, &m2, &m3, &d2
        };
        initialize(moduleOrder, -1, 1);
    }
    
private:
    TestModule m1, m2, m3;
    DenseNeuralNetwork d1, d2;
};
//==============================================================================
std::vector<float> generateData(int n) {
    std::mt19937 mt;
    std::uniform_real_distribution<> dist(0, 1);
    //std::normal_distribution<> dist(0, 1);

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
    for (int i = 0; i < 16 * 16; i++) {
        nn.runNeuralNetwork(&inputs);
    }
    const std::vector<float>* outputs = nn.runNeuralNetwork(&inputs);

//    for (int i = 0; i < inputs->size(); i++) {
//        std::cout << inputs->at(i) << " to " << outputs->at(i) << std::endl;
//    }
    std::cout << inputs[0] << " and " << outputs->at(0) << std::endl;
}
//==============================================================================

void trainPipeline(int size, int iters) {
    TestNeuralNetwork nn(size);
    std::vector<float> inputs = generateData(size);

    std::cout << "Size (" << size << ", " << size << ") neural network\n";
    // Print residuals.
    auto resids = nn.getResiduals(&inputs, &inputs);
    std::cout << "Cost before training: " << nn.getCost(&resids) << "\n";
    std::cout << "Training " << iters << " iterations...\n";
    for (int i = 0; i < iters; i++) {
        nn.trainNeuralNetwork(&inputs, &inputs, 1);
    }

    // Print residuals.
    resids = nn.getResiduals(&inputs, &inputs);
    std::cout << "Cost after training: " << nn.getCost(&resids) << "\n";
}
//==============================================================================
int main() {
    std::cout << std::endl;
    //runPipeline();
    trainPipeline(64, 100);

    return 0;
}
