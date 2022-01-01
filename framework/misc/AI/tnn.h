#include "nn.h"

class TrainingNeuralNetwork : public NeuralNetwork {
public:

	TrainingNeuralNetwork();

	std::vector<float> captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs);

	float getCost(std::vector<float>* finputs, std::vector<float>* foutputs);

	void trainNeuralNetwork(std::string fileName, Neuron* neuron, unsigned int sampleSize, int minRes);

	//--------------------------------------------------------------------------------
	// Neuron setup.

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
	std::vector<float> runNeuralNetwork();

	float getCostP(std::vector<float>* foutputs);

	float findMinAV(Neuron* neuron, TrainingNeuralNetwork& loadState, int minRes);

	void getSamplePoints(Neuron* neuron, std::vector<float>* centroid, std::vector<float>* samplePoints, int minRes, std::ifstream& file);

	void readState(TrainingNeuralNetwork* nn, std::ifstream* trainFile);
	void readState(TrainingNeuralNetwork* nn, TrainingNeuralNetwork* on);

	// Used for recording the nn state for training.
	bool recordMode;
	std::ofstream recordFile;

	//--------------------------------------------------------------------------------
	// Training.

	TrainingNeuralNetwork loadState;
	unsigned int sampleSize;
	std::vector<float> centroid;

	// List of all the points containing the inputs (child nodes)
	// and outputs (neuron AV) to form a plane of best fit.
	std::vector<float> samplePoints;

};