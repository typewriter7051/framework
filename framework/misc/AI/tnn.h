#pragma once
#include "nn.h"
#include "tneuron.h"

class TrainingNeuralNetwork : public NeuralNetwork {
public:

	TrainingNeuralNetwork();

	std::vector<float> captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::string fileName, TrainingNeuron* neuron, unsigned int sampleSize, int minRes);

	//Neuron* getNeuron(unsigned int index);

	//--------------------------------------------------------------------------------
	// Neuron setup.

	TrainingNeuron* getNeuron(unsigned int index);
	std::vector<Neuron*> getArray(unsigned int start, unsigned int end) override;

	void setNeurons(unsigned int i, unsigned int o, unsigned int h) override;

	// Randomizes the weights.
	void setupWeights(float min, float max);

	// Fully connects the 2 lists of neurons (B is ending layer, A is starting layer).
	void fullyConnectNeurons(std::vector<Neuron*> layerB, std::vector<Neuron*> layerA);

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

	float findMinAV(Neuron* neuron, TrainingNeuralNetwork& loadState, int minRes);

	std::vector<float> calculateWeights();

	bool getSamplePoints(Neuron* neuron, TrainingNeuralNetwork& loadState, int minRes, std::ifstream& file);

	void readState(TrainingNeuralNetwork* nn, std::ifstream* trainFile);
	void readState(TrainingNeuralNetwork* nn, TrainingNeuralNetwork* on);

	// Used for recording the nn state for training.
	bool recordMode;
	std::ofstream recordFile;

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
