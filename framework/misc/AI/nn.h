#pragma once
#include <vector>
#include <string>
#include "neuron.h"

class NeuralNetwork {
public:
	//--------------------------------------------------------------------------------
	//Constructors.

	NeuralNetwork();

	//--------------------------------------------------------------------------------
	// Getters.

	// Returns the pointer to input and output neuron lists.
	std::vector<Neuron*> getInputs();
	std::vector<Neuron*> getOutputs();

	std::vector<Neuron*> getArray(unsigned int start, unsigned int end);
	Neuron* getNeuron(unsigned int index);

	// Runs the neural network and returns the outputs in a list.
	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	//--------------------------------------------------------------------------------
	// Neuron creation and handling.

	// Establishes the list of neurons given a set number of input, output, and hidden neurons.
	void setNeurons(unsigned int i, unsigned int o, unsigned int h);

	// Randomizes the weights.
	void setupWeights(float min, float max);

	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(std::vector<Neuron*> layerB, std::vector<Neuron*> layerA);

	//--------------------------------------------------------------------------------
	// File handling.

	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName);

	//--------------------------------------------------------------------------------
	// Recording.

	void startRecording(std::string fileName);
	void stopRecording();

	std::vector<float> captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::string fileName, Neuron* neuron, unsigned int sampleSize, int minRes);

private:

	float getCostP(std::vector<float>* foutputs);

	float findMinAV(Neuron* neuron);

	void getSamplePoints(Neuron* neuron, std::vector<float>* centroid, std::vector<float>* samplePoints, std::ifstream& file);

	// Runs the neural network without resetting input values.
	std::vector<float> runNeuralNetwork();

	void readState(NeuralNetwork* nn, std::ifstream* trainFile);
	void readState(NeuralNetwork* nn, NeuralNetwork* on);

	// Used for recording the nn state for training.
	bool recordMode;
	std::ofstream recordFile;

	// Holds all the neurons including inputs and outputs.
	std::vector<Neuron> neurons;

	// Pointers to the input and output neurons within the previous list.
	std::vector<Neuron*> inputs, outputs;

};
