#include <fstream>
#include <memory>
#include <string>
#include "nn_module.h"

class NeuralNetwork {
public:
    void runNeuralNetwork(const std::vector<float>* inputs, std::vector<float>* outputs);
    float getCost(const std::vector<float>* expectedOutputs);

    void setNumModules(int n);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

private:
    std::vector<std::unique_ptr<NNModule>> modules;
    // Holds the output/input neurons to pass between modules.
    std::vector<float> profile;
};