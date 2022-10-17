#include "neural_network.h"
#include "dense_nn.cpp"

class DemoNetwork : public NeuralNetwork {
public:
    DemoNetwork::DemoNetwork() {
        n1.initialize(std::vector<int> {128, 64, 32, 16});
        n2.initialize(std::vector<int> {16, 16, 16, 16, 16});
        n3.initialize(std::vector<int> {16, 32, 64, 128});

        n3.addConnection(&n2);
        n2.addConnection(&n1);

        // Only supply first and last modules.
        initialize(&n1, &n3);
    }

private:
    DenseNeuralNetwork n1, n2, n3;
}

/*
...
In neural_network.h
...
*/
// Used for saving/loading. Don't need to specify type if each save()/load() is in the right order.
// Use this function for runNeuralNetwork and trainNeuralNetwork too.
std::vector<NNModule*> generateModulesList() {
    // Calculate order of modules to be run.
    return list;
}

void initialize(firstNN, lastNN) {
    profile[0].resize(firstNN.getNumInputs());
    profile[-1].resize(lastNN.getNumOutputs());
    // Generate profile somehow...
}

/*
...
Some main function.
...
*/

{
    DemoNetwork network;

    data = ...
    network.trainNeuralNetwork(data);
    network.saveToFile("myNeuralNetwork.DemoNetwork");
}

{
    DemoNetwork network;
    network.loadFromFile("myNeuralNetwork.DemoNetwork");

    data = ...
    network.runNeuralNetwork(data);
}