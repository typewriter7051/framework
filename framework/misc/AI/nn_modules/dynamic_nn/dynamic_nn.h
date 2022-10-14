#pragma once
#include "dynamic_neuron.h"
#include <vector>
#include <string>

class DynamicNeuralNetwork : public NNModule {
public:
	//--------------------------------------------------------------------------------
	// Constructors.

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
	std::vector<float> runNeuralNetwork(std::vector<float>* finputs, int profile);
	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs, int profile);
	//--------------------------------------------------------------------------------
	// Profiles.

	void addProfile();
	unsigned int getNumProfiles();
	void setNumProfiles(unsigned int n);
	//--------------------------------------------------------------------------------
	// Training.

	void refreshNumParents();

	void trainNeuralNetwork(std::vector<float>* samples, float stepSize, int profile);
	//Neuron* getNeuron(unsigned int index);
	//--------------------------------------------------------------------------------
	// Network wrangling.

	void setNeurons(unsigned int i, unsigned int o, unsigned int h);
	// Randomizes the weights.
	void setupWeights(float min, float max);
	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(
		std::vector<DynamicNeuron*> layerB,
		std::vector<DynamicNeuron*> layerA);
	void connectNeurons(int indexB, int indexA, bool isRecursive);
	void setActivationFunction(
		std::vector<DynamicNeuron*> neurons,
		ActivationFunction::NonLinearMethod method);

	void removeNeuron(unsigned int ID);
	// Removes any neurons or connections below (average value across network) * threshold.
	void trimDead(float threshold, int profile);
	// NOTE: liquid neural networks require numerical differentiation
	// since we have no idea which connections are recursive.
	void growNeuron();
	//--------------------------------------------------------------------------------
	// File handling.

	void saveToFile(std::string fileName, bool compressIDs, bool useHalfFloats);
	void loadFromFile(std::string fileName);
	
private:
	// Pointers to the input and output neurons within the previous list.
	std::vector<DynamicNeuron*> inputs, outputs;
	std::vector<DynamicNeuron> neurons;
	// Stores different profiles so you don't need to create a copy of the network for multiple tasks.
	std::vector<std::vector<float>> profiles;
	//--------------------------------------------------------------------------------
	// Training.

	unsigned int is, os, hn;

	void moveMembers(std::vector<std::vector<float>>* values, float strength);
};
