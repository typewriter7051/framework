#pragma once
#include "tneuron.h"
#include <vector>
#include <string>

class TrainingNeuralNetwork {
public:

	TrainingNeuralNetwork();

	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::vector<float> samples, float stepSize, float strength);

	//Neuron* getNeuron(unsigned int index);

	// Returns the pointer to input and output neuron lists.
	std::vector<TrainingNeuron*> getInputs();
	std::vector<TrainingNeuron*> getOutputs();
	std::vector<TrainingNeuron*> getNeurons();

	int getNumHiddenNeurons();
	int getNumUnhiddenNeurons();
	int getNumNeurons();

	//--------------------------------------------------------------------------------
	// Neuron setup.

	TrainingNeuron* getNeuron(unsigned int index);
	std::vector<TrainingNeuron*> getArray(unsigned int start, unsigned int end);

	void setNeurons(unsigned int i, unsigned int o, unsigned int h);

	// Randomizes the weights.
	void setupWeights(float min, float max);

	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(std::vector<TrainingNeuron*> layerB, std::vector<TrainingNeuron*> layerA);

	void setActivationFunction(std::vector<TrainingNeuron*> neurons, ActivationFunction::NonLinearMethod method);

	//--------------------------------------------------------------------------------
	// Network Trimming.

	// Trims the neuron with the lowest cost derivative.
	void dropout();

	// Trims `num` number of the lowest valued connections.
	void trimDeadConnections(unsigned int num);

	// NOTE: liquid neural networks require numerical differentiation
	// since we have no idea which connections are recursive.
	void growNeuron();

	//--------------------------------------------------------------------------------
	// File handling.

	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName);

	//void exportToFile(std::string fileName, bool IDComp, );

private:

	// Runs the neural network without resetting input values.
	std::vector<float> rerunNeuralNetwork();

	float getCostP(std::vector<float>* foutputs);

	void setInputs(std::vector<float>* i);

	void moveMembers(std::vector<std::vector<float>>* values, float strength);

	bool readState(TrainingNeuralNetwork* nn, std::ifstream* trainFile);
	void readState(TrainingNeuralNetwork* nn, TrainingNeuralNetwork* on);

	// Used for recording the nn state for training.
	bool recordMode;
	std::ofstream recordFile;

	// Pointers to the input and output neurons within the previous list.
	std::vector<TrainingNeuron*> inputs, outputs;

	std::vector<TrainingNeuron> neurons;

	//--------------------------------------------------------------------------------
	// Training.

	unsigned int is, os, hn;

};
