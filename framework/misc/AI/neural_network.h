#include <fstream>
#include <string>
#include "nn_module.h"

class NeuralNetwork {
public:
    std::vector<float> runNeuralNetwork();
    float getCost(std::vector<float> expectedOutputs);

    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);

private:
    std::vector<NNModule> modules;
    // Holds the output/input neurons to pass between modules.
    std::vector<float> profile;
};