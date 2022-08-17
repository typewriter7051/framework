#pragma once
#include "static_neuron.h"
#include <vector>
#include <string>

class StaticNeuralNetwork {
public:
	//--------------------------------------------------------------------------------
	//Constructors.

	StaticNeuralNetwork() {}

	//--------------------------------------------------------------------------------
	// Getters.

	// Returns the pointer to input and output neuron lists.
	std::vector<StaticNeuron*> getInputs();
	std::vector<StaticNeuron*> getOutputs();


	StaticNeuron* getNeuron(unsigned int index);
	std::vector<StaticNeuron*> getArray(unsigned int start, unsigned int end);

	// Runs the neural network and returns the outputs in a list.
	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	//--------------------------------------------------------------------------------
	// File handling.

	void loadFromFile(std::string fileName);

private:

	// Establishes the list of neurons given a set number of input, output, and hidden neurons.
	void setNeurons(unsigned int i, unsigned int o, unsigned int h);

	// Pointers to the input and output neurons within the previous list.
	std::vector<StaticNeuron*> inputs, outputs;

	// Holds all the neurons including inputs and outputs.
	std::vector<StaticNeuron> neurons;

};
