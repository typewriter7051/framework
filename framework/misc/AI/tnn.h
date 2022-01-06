#include "nn.h"
#include "tneuron.h"

class TrainingNeuralNetwork : public NeuralNetwork {
public:

	TrainingNeuralNetwork();

	std::vector<float> captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::string fileName, TrainingNeuron* neuron, unsigned int sampleSize, int minRes);

	//--------------------------------------------------------------------------------
	// Neuron setup.

	TrainingNeuron* getNeuron(unsigned int index);

	void setNeurons(unsigned int i, unsigned int o, unsigned int h) {

		NeuralNetwork::setNeurons(i, o, h);

	}

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

	//void exportToFile(std::string fileName, bool IDComp, );

private:

	// Runs the neural network without resetting input values.
	std::vector<float> rerunNeuralNetwork();

	float getCostP(std::vector<float>* foutputs);

	float findMinAV(Neuron* neuron, TrainingNeuralNetwork& loadState, int minRes);

	void getSamplePoints(Neuron* neuron, TrainingNeuralNetwork& loadState, int minRes, std::ifstream& file);

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
	// and outputs (neuron AV) to form a plane of best fit.
	std::vector<float> samplePoints;

};