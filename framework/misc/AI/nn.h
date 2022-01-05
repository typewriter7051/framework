#pragma once
#include <vector>
#include <string>
#include "neuron.h"

class NeuralNetwork {
public:
	//--------------------------------------------------------------------------------
	//Constructors.

	NeuralNetwork() {}

	//--------------------------------------------------------------------------------
	// Getters.

	// Returns the pointer to input and output neuron lists.
	std::vector<Neuron*> getInputs();
	std::vector<Neuron*> getOutputs();

	std::vector<Neuron*> getArray(unsigned int start, unsigned int end);
	Neuron* getNeuron(unsigned int index);

	// Runs the neural network and returns the outputs in a list.
	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	//--------------------------------------------------------------------------------
	// File handling.

	void loadFromFile(std::string fileName);

protected:

	// Establishes the list of neurons given a set number of input, output, and hidden neurons.
	void setNeurons(unsigned int i, unsigned int o, unsigned int h);

	// Pointers to the input and output neurons within the previous list.
	std::vector<Neuron*> inputs, outputs;

private:

	// Holds all the neurons including inputs and outputs.
	std::vector<Neuron> neurons;

};
