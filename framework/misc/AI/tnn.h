#pragma once
#include "nn.h"
#include "tneuron.h"

class TrainingNeuralNetwork : public NeuralNetwork {
public:

	TrainingNeuralNetwork();

	std::vector<float> runNeuralNetwork(std::vector<float>* finputs);

	std::vector<float> captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::string fileName, TrainingNeuron* neuron, unsigned int sampleSize, float threshold, float strength);

	//Neuron* getNeuron(unsigned int index);

	// Returns the pointer to input and output neuron lists.
	std::vector<TrainingNeuron*> getInputs();
	std::vector<TrainingNeuron*> getOutputs();

	int getNumHiddenNeurons();
	int getNumUnhiddenNeurons();
	int getNumNeurons();

	//--------------------------------------------------------------------------------
	// Neuron setup.

	TrainingNeuron* getNeuron(unsigned int index);
	std::vector<TrainingNeuron*> getArray(unsigned int start, unsigned int end);

	void setNeurons(unsigned int i, unsigned int o, unsigned int h) override;

	// Randomizes the weights.
	void setupWeights(float min, float max);

	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(std::vector<TrainingNeuron*> layerB, std::vector<TrainingNeuron*> layerA);

	//--------------------------------------------------------------------------------
	// Recording.

	void startRecording(std::string fileName);
	void stopRecording();

	//--------------------------------------------------------------------------------
	// File handling.

	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName) override;

	//void exportToFile(std::string fileName, bool IDComp, );

private:

	// Runs the neural network without resetting input values.
	std::vector<float> rerunNeuralNetwork();

	float getCostP(std::vector<float>* foutputs);

	float findMinAV(TrainingNeuron* neuron, TrainingNeuralNetwork* loadState, float threshold);

	std::vector<float> calculateWeights();

	bool getSamplePoints(TrainingNeuron* neuron, TrainingNeuralNetwork* loadState, int minRes, std::ifstream& file);

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

	unsigned int sampleSize;
	std::vector<float> centroid;

	unsigned int is, os, hn;

	// List to hold expected outputs of each state.
	std::vector<float> exout;

	// List of all the points containing the inputs (child nodes)
	// and outputs (neuron AV) to form a cloud of high dimensional points.
	std::vector<float> samplePoints;

};
