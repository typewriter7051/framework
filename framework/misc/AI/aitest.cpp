#include <iostream>
#include <vector>
#include <cstdlib>
#include "tnn.h"
#include "templates.h"

float planeFunction(float x, float y) {

    float z = 3 * x + 1.3 * y;
    return z;

}

int main() {

    TrainingNeuralNetwork nn;

    // Literally just 2 input nodes connected to an output node.
    // Resembles a 3D plane with x and y as inptus and z as output.
    nn = createConvolutionalNetwork(2, 1, 0, 0);

    nn.saveToFile("plane");
    nn.loadFromFile("plane");

    nn.startRecording("plane");
    for (int i = 0; i < 1000; i++) {

        srand(i);
        float x = rand() % 1000 / (float)100;
        float y = rand() % 1000 / (float)100;
        float z = planeFunction(x, y);

        std::vector<float> inputs = {x, y};
        std::vector<float> outputs = {z};

        nn.captureNeuralNetwork(&inputs, &outputs);

    }
    nn.stopRecording();

    std::vector<float> inputs = {3, 4};
    std::vector<float> outputs = {planeFunction(3, 4)};
    std::cout << nn.getCost(&inputs, &outputs) << std::endl;
    nn.trainNeuralNetwork("plane", nn.getNeuron(2), 1000, 10);
    std::cout << nn.getCost(&inputs, &outputs) << std::endl;

    return 0;

}
