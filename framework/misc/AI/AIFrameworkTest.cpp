#include <iostream>
#include "nn.h"
#include "../profiler.h"

int main() {

    //--------------------------------------------------------------------------------
    // Setup.

    NeuralNetwork nn;

    Profiler profiler;

    profiler.addMark("begin");

    ///*
    nn.setNeurons(100, 100, 100);

    std::vector<Neuron*> ml = nn.getArray(200, 299);

    //nn.fullyConnectNeurons(nn.getOutputs(), ml);
    //nn.fullyConnectNeurons(ml, nn.getInputs());
    nn.fullyConnectNeurons(nn.getOutputs(), nn.getInputs());

    nn.setupWeights(-0.1, 0.1);
    //*/

    profiler.addMark("nn creation");

    //--------------------------------------------------------------------------------
    // Save/load.

    nn.saveToFile("poo");
    profiler.addMark("saving");

    nn.loadFromFile("poo");
    profiler.addMark("loading");

    std::vector<float> inputs;
    for (int i = 0; i < nn.getInputs().size(); i++) inputs.push_back(1);
    profiler.addMark("setup inputs");


    //--------------------------------------------------------------------------------
    // Benchmarking.

    std::vector<float> outputs = nn.runNeuralNetwork(&inputs);

    for (int i = 0; i < 44; i++) nn.runNeuralNetwork(&inputs);

    profiler.addMark("nn run time");

    //--------------------------------------------------------------------------------
    // Recording.

    /*
    nn.startRecording("poo");
    for (int i = 0; i < 1; i++) {

        for (float f = 0; f < outputs.size(); f++) outputs[f] = 0;
        nn.captureNeuralNetwork(&inputs, &outputs);

    }
    nn.stopRecording();
    //*/

    std::cout << nn.getCost(&inputs, &outputs) << std::endl;

    for (Neuron* n : nn.getOutputs()) {

        nn.trainNeuralNetwork("poo", n, 1, 10);

    }

    std::cout << nn.getCost(&inputs, &outputs) << std::endl;

    nn.saveToFile("pee");

    profiler.addMark("recording");

    profiler.printProfile(false);

    int poo;
    std::cin >> poo;

    return 0;
}
