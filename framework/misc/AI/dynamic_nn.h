#pragma once
#include "dynamic_neuron.h"
#include <vector>
#include <string>

class DynamicNeuralNetwork {
public:
	//--------------------------------------------------------------------------------
	//Constructors.

	DynamicNeuralNetwork();

	//--------------------------------------------------------------------------------
	// Getters.

	// Returns the pointer to input and output neuron lists.
	std::vector<DynamicNeuron*> getInputs();
	std::vector<DynamicNeuron*> getOutputs();
	std::vector<DynamicNeuron*> getNeurons();

	int getNumHiddenNeurons();
	int getNumUnhiddenNeurons();
	int getNumNeurons();

	DynamicNeuron* getNeuron(unsigned int index);
	std::vector<DynamicNeuron*> getArray(unsigned int start, unsigned int end);

	// Runs the neural network and returns the outputs in a list.
	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	//--------------------------------------------------------------------------------
	// Training.

	void trainNeuralNetwork(std::vector<float> samples, float stepSize);

	//Neuron* getNeuron(unsigned int index);

	//--------------------------------------------------------------------------------
	// Network wrangling.

	void setNeurons(unsigned int i, unsigned int o, unsigned int h);

	// Randomizes the weights.
	void setupWeights(float min, float max);

	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(std::vector<DynamicNeuron*> layerB, std::vector<DynamicNeuron*> layerA);

	void setActivationFunction(std::vector<DynamicNeuron*> neurons, ActivationFunction::NonLinearMethod method);

	// Trims the neuron with the lowest cost derivative.
	void dropout();

	// Trims `num` number of the lowest valued connections.
	void trimDeadConnections(unsigned int num);

	// NOTE: liquid neural networks require numerical differentiation
	// since we have no idea which connections are recursive.
	void growNeuron();

	void shrinkToFit();

	//--------------------------------------------------------------------------------
	// File handling.

	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName);

	//void exportToFile(std::string fileName, bool IDComp, );

private:

	void setInputs(std::vector<float>* i);

	// Used for recording the nn state for training.
	// DEPRACATED
	bool recordMode;
	// DEPRACATED
	std::ofstream recordFile;

	// Pointers to the input and output neurons within the previous list.
	std::vector<DynamicNeuron*> inputs, outputs;

	std::vector<DynamicNeuron> neurons;

	//--------------------------------------------------------------------------------
	// Training.

	unsigned int is, os, hn;

	void moveMembers(std::vector<std::vector<float>>* values, float strength);

	// DEPRACATED
	float getCostP(std::vector<float>* foutputs);

	// Runs the neural network without resetting input values.
	std::vector<float> rerunNeuralNetwork();

	// DEPRACATED
	bool readState(DynamicNeuralNetwork* nn, std::ifstream* trainFile);
	// DEPRACATED
	void readState(DynamicNeuralNetwork* nn, DynamicNeuralNetwork* on);

	//--------------------------------------------------------------------------------
	// Network wrangling.

	// Keeps track of which neurons were removed for shinkToFit().
	std::vector<unsigned int> removedNeuronIDs;

};
