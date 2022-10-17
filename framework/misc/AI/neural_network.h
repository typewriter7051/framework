#include <fstream>
#include <memory>
#include <string>
#include "nn_module.h"

class NeuralNetwork {
public:
    void runNeuralNetwork(const std::vector<float>* inputs, std::vector<float>* outputs);
    float getCost(std::vector<float> expectedOutputs);

    void setNumModules(int n);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

private:
    std::vector<std::unique_ptr<NNModule>> modules;
    // Holds the output/input neurons to pass between modules.
    std::vector<float> profile;
};

// Target syntax will be something like this.
/*
NeuralNetwork nn;
nn.setNumModules(10);

nn.modules[4] = DenseNeuralNetwork(std::vector<int> {128, 64, 64, 128});
nn.modules[3] = DynamicNeuralNetwork(args);

nn.modules[4].addConnection(&nn.modules[3]);
.
.
.

std::vector<std::vector<float>> data;
...

nn.trainNeuralNetwork(data, stepSize);
nn.saveToFile("CoolNeuralNetwork"); // Saves to "CoolNeuralNetwork.nn"
*/

/*
NeuralNetwork nn;
nn.loadFromFile("CoolNeuralNetwork");
.
.
.

{
    std::vector<float> inputs, outputs;
    ...
    nn.runNeuralNetwork(&inputs, &outputs);
    ...
}
*/