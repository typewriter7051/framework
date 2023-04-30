#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include "neural_network.h"
#include "nn_modules/test_module/test_module.h"
#include "nn_modules/dense_nn/dense_nn.h"
#include "nn_modules/zipper/zipper_module.h"

class TestNeuralNetwork : public NeuralNetwork {
public:
    TestNeuralNetwork(int size) {
        int comp = 16;

	    d1 = DenseNeuralNetwork(std::vector<int> {
			size,
			size
		});

        zip = ZipperModule(size, true, 1);
        unzip = ZipperModule(size, false, 1);

        /*
        m1 = TestModule(size / comp);
        m2 = TestModule(size / comp);
        m3 = TestModule(size / comp);

	    d2 = DenseNeuralNetwork(std::vector<int> {
			size / comp,
			size
		});
        */

        // Run the pipeline from first to last.
        std::vector<NNModule*> moduleOrder {
            &zip,
            &d1,
            &unzip
        };
        initialize(moduleOrder, -1, 1);
    }
    
private:
    TestModule m1, m2, m3;
    DenseNeuralNetwork d1, d2;
    ZipperModule zip, unzip;
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

void trainPipeline(int size, float stepSize, int updateRate, float threshold) {
    TestNeuralNetwork nn(size);
    std::vector<float> inputs = generateData(size);

    std::cout << "Size (" << size << ", " << size << ") neural network\n";
    // Print residuals.
    auto resids = nn.getResiduals(&inputs, &inputs);
    std::cout << "Cost before training: " << nn.getCost(&resids) << "\n";

    float cost = nn.getCost(&resids);
    float prevCost = cost + 100;
    int i = 1;
    while (prevCost - cost > threshold) {
        nn.trainNeuralNetwork(&inputs, &inputs, stepSize);

        // Print status update.
        if (i % updateRate == 0) {
            std::cout << "iteration " << i << std::endl;

            resids = nn.getResiduals(&inputs, &inputs);
            prevCost = cost;
            cost = nn.getCost(&resids);
            std::cout << "new cost: " << cost << std::endl;
        }
        i++;
    }

    // Print residuals.
    resids = nn.getResiduals(&inputs, &inputs);
    std::cout << "Cost after training: " << nn.getCost(&resids) << "\n";

    nn.saveToFile("test.nn");
}
//==============================================================================
int main() {
    std::cout << std::endl;
    //runPipeline();
    trainPipeline(64 * 64, 1, 1, 0.0001);

    return 0;
}
