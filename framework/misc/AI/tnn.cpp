#include <cmath>
#include "tnn.h"

//================================================================================
// Constructors.

TrainingNeuralNetwork::TrainingNeuralNetwork() {

	recordMode = false;
	is = 0;
	os = 0;
	hn = 0;
	sampleSize = 0;

}

//================================================================================
// Getters.

float TrainingNeuralNetwork::getCost(std::vector<float>* finputs, std::vector<float>* foutputs) {

	std::vector<float> actualOutput = NeuralNetwork::runNeuralNetwork(finputs);

	if (foutputs->size() != actualOutput.size()) {

		std::cout << "\nEXPECTED OUTPUTS SIZE DOESNT MATCH NN OUTPUT SIZE";
		std::cout << " outputs passed (" << foutputs->size() << ") expected (" << actualOutput.size() << ")";
		return 1;

	}

	// Calculate standard deviation from expected output (cost).

	float sd = 0;

	for (int i = 0; i < actualOutput.size(); i++) {

		sd += (actualOutput.at(i) - foutputs->at(i)) * (actualOutput.at(i) - foutputs->at(i));
		std::cout << "Expected output vs actual output: " << foutputs->at(i) << ", " << actualOutput.at(i) << std::endl;

	}

	sd = sqrt(sd) / float(actualOutput.size());

	return sd;

}

float TrainingNeuralNetwork::getCostP(std::vector<float>* foutputs) {

	std::vector<float> actualOutput = rerunNeuralNetwork();

	if (foutputs->size() != actualOutput.size()) {

		std::cout << "\nEXPECTED OUTPUTS SIZE DOESNT MATCH NN OUTPUT SIZE";
		std::cout << " outputs passed (" << foutputs->size() << ") expected (" << actualOutput.size() << ")";
		return 1;

	}

	// Calculate standard deviation from expected output (cost).

	float sd = 0;

	for (int i = 0; i < actualOutput.size(); i++) {

		sd += (actualOutput.at(i) - foutputs->at(i)) * (actualOutput.at(i) - foutputs->at(i));

	}

	sd = sqrt(sd) / float(actualOutput.size());

	return sd;

}

// Runs the neural network without resetting input values.
std::vector<float> TrainingNeuralNetwork::rerunNeuralNetwork() {

	// Set inputs to be done.
	for (Neuron* n : inputs) n->setDone();

	// Vector to be returned.
	std::vector<float> rv;

	// Call getValue() for all output neurons and copy results to returnVector.
	for (Neuron* n : outputs) {

		rv.push_back(n->getValue());

	}

	// Clear finished status for all neurons.
	// This is done afterwards becuase we don't want to reset the
	// manually set done status of neurons before running.
	for (int n = 0; n < neurons.size(); n++)
		neurons[n].setUndone();

	return rv;

}

//================================================================================
// Setters.

TrainingNeuron* TrainingNeuralNetwork::getNeuron(unsigned int index) {

	return &neurons.at(index);

}

std::vector<Neuron*> TrainingNeuralNetwork::getArray(unsigned int start, unsigned int end) {

	std::vector<Neuron*> temp(end - start + 1);

	for (int i = 0; i <= end - start; i++) {

		temp.at(i) = &neurons.at(start + i);

	}

	return temp;

}

// Sets up the input and output nodes.
void TrainingNeuralNetwork::setNeurons(unsigned int numInputs, unsigned int numOutputs, unsigned int h) {

	// Completely clear the network and reset neuron ID counter.
	neurons.clear();
	inputs.clear();
	outputs.clear();
	Neuron::resetIDCounter();

	// Reset and re-initialize the input/output pointer lists.
	neurons.resize(numInputs + numOutputs + h);

	for (int i = 0; i < numInputs; i++) { inputs.push_back(&neurons[i]); }
	for (int o = 0; o < numOutputs; o++) { outputs.push_back(&neurons[numInputs + o]); }

}

void TrainingNeuralNetwork::setupWeights(float min, float max) {

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].setupAverageConnections(min, max);

	}

}

void TrainingNeuralNetwork::fullyConnectNeurons(std::vector<Neuron*> layerB, std::vector<Neuron*> layerA) {

	for (Neuron* b : layerB) {
		for (Neuron* a : layerA) {

			b->addConnection(a);

		}
	}

}

//================================================================================
// Recording and Training.

void TrainingNeuralNetwork::startRecording(std::string fileName) {

	recordMode = true;

	fileName += ".nnr";
	recordFile.open(fileName, std::ios_base::app | std::ios::binary);

}

void TrainingNeuralNetwork::stopRecording() {

	recordFile.close();
	recordMode = false;

}

//--------------------------------------------------------------------------------

std::vector<float> TrainingNeuralNetwork::captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs) {

	std::vector<float> rv = NeuralNetwork::runNeuralNetwork(finputs);

	unsigned int a = 0;

	// Ok to use for-each since the neurons aren't being altered.
	for (Neuron n : neurons) {

		//recordFile << n.getValue() << "\n";
		float value = n.getValue();
		recordFile.write((char*)&value, sizeof(float));
		a += sizeof(float);

	}

	for (float f : *foutputs) {

		//recordFile << f << "\n";
		recordFile.write((char*)&f, sizeof(float));
		a += sizeof(float);

	}

	return rv;

}

//--------------------------------------------------------------------------------

bool TrainingNeuralNetwork::readState(TrainingNeuralNetwork* nn, std::ifstream* trainFile) {

	for (int neuron = 0; neuron < nn->neurons.size(); neuron++) {

		float av = 0;
		trainFile->read((char*)&av, sizeof(float));

		if (trainFile->eof()) {

			trainFile->close();
			return false;

		}

		nn->neurons.at(neuron).setValue(av);

	}

	return true;

}

void TrainingNeuralNetwork::readState(TrainingNeuralNetwork* nn, TrainingNeuralNetwork* on) {

	if (nn->neurons.size() != on->neurons.size()) {

		std::cout << "ATTEMPTED TO COPY STATE OF UNIDENTICAL NETWORKS!";
		return;

	}

	for (int neuron = 0; neuron < nn->neurons.size(); neuron++) {

		float av = on->neurons.at(neuron).getValue();
		nn->neurons.at(neuron).setValue(av);

	}

}

// NOTE: Returns raw value BEFORE nonlinear function is applied. This is to
// help the backpropogation algorithm.
float TrainingNeuralNetwork::findMinAV(Neuron* neuron, TrainingNeuralNetwork* loadState, int minRes) {

	float minCost = 1000;
	float minCostAV = 0;

	for (int i = 0; i < minRes + 1; i++) {

		// Set loadstate from load state before running the nn again.
		readState(this, loadState);

		float avSamplePoint = -1 + 2 * i / float(minRes);
		neuron->setValue(avSamplePoint);
		float curCost = this->getCostP(&exout);

		if (curCost < minCost) {

			minCost = curCost;
			minCostAV = avSamplePoint;

		}

	}

	// "Undo" nonlinear function since we want to return raw value.
	return TrainingNeuron::inverseNonlinear(minCostAV);
	//return minCostAV;

}

//--------------------------------------------------------------------------------

// `samplePoints` is formatted as a list containing a series of samples.
// Each sample is comprised of a bunch of inputs and the ideal AV (output).
// For example {input, input, output, input, input, output, ...}
bool TrainingNeuralNetwork::getSamplePoints(Neuron* neuron, TrainingNeuralNetwork* loadState, int minRes, std::ifstream& file) {

	// Iterate through sampleSize samples and calculate the centroid.
	for (int s = 0; s < sampleSize; s++) {

		// Read the next loadstate from file.
		if (!readState(loadState, &file)) return false;

		// Read the expected output data.
		file.read((char*)exout.data(), sizeof(float) * os);

		// NOTE: does not check for EOF after reading expected output.

		//---Find the optimal neuron av and calculate weight/bias of best fit.---

		float minCostAV = findMinAV(neuron, loadState, minRes);

		//--------------------------------------------------------------------------------
		// Update the centroid.

		// Get the list of pointers to its connected neurons (inputs).
		std::vector<Neuron*> connections = neuron->getConnections();

		for (int n = 0; n < connections.size(); n++) {

			connections.at(n)->setDone(); // Just for efficeincy. No need to re-calculate the child node values.
			float childNeuronAV = connections.at(n)->getValue();
			centroid.at(n) = (centroid.at(n) * s + childNeuronAV) / float(s + 1);
			samplePoints.push_back(childNeuronAV);

		}

		centroid.back() = (centroid.back() * s + minCostAV) / float(s + 1);
		samplePoints.push_back(minCostAV);

	}

	return true;

}

std::vector<float> TrainingNeuralNetwork::calculateWeights() {

	int numDimensions = centroid.size();

	// If there's something wrong with samplePoints then abort.
	if (samplePoints.size() / numDimensions != sampleSize) {

		std::cout << "\nSAMPLEPOINTS VECTOR DOESNT MATCH SAMPLESIZE\n";
		return std::vector<float>();

	}

	std::vector<float> weights(numDimensions - 1); // List of weights to be returned.
	std::vector<float> ndist(numDimensions - 1);
	std::vector<float> ddist(numDimensions - 1);
	int index = 0; // For use within the for loops.

	// For each sample.
	for (int s = 0; s < sampleSize; s++) {

		// Index of the ideal AV (output) of the current sample.
		int outputIndex = (s + 1) * numDimensions - 1;

		// For each dimension (input) within a sample.
		// The -1 in the range is because we don't need to include
		// the output dimension.
		for (int d = 0; d < numDimensions - 1; d++) {

			// Index within the entire list of sample points.
			index = s * numDimensions + d;

			// Slope of best fit = SUM(xdist * ydist) / SUM(xdist^2)
			// "xdist * ydist"
			ndist.at(d) += (samplePoints.at(index) - centroid.at(d)) *		// X distance
						  (samplePoints.at(outputIndex) - centroid.back()); // Y distance

			// "xdist^2"
			ddist.at(d) += (samplePoints.at(index) - centroid.at(d)) *
						  (samplePoints.at(index) - centroid.at(d));

		}

	}

	// Divide by 0 prevention.
	for (int d = 0; d < numDimensions - 1; d++)
		if (ddist.at(d) == 0) ddist.at(d) = 1;

	// Once the sums are calculated simply divide the two to get weights.
	for (int d = 0; d < numDimensions - 1; d++) {

		weights.at(d) = ndist.at(d) / ddist.at(d);
		weights.at(d) /= float(numDimensions - 1); // Normalization.

		//std::cout << "Weight #" << d << ": " << weights.at(d) << std::endl;

	}

	return weights;

}

void TrainingNeuralNetwork::trainNeuralNetwork(std::string fileName,
	TrainingNeuron* neuron, unsigned int samSize, int minRes, float strength) {

	sampleSize = samSize;
	std::ifstream file;
	TrainingNeuralNetwork loadState;

	// Read the nn structure data from partner file.
	std::string nnFile;
	nnFile = fileName + ".nn";
	file.open(nnFile, std::ios::binary);
	file.read((char*)&is, sizeof(unsigned int));
	file.read((char*)&os, sizeof(unsigned int));
	file.read((char*)&hn, sizeof(unsigned int));
	file.close();
	file.clear(); // For safety.

	// Then load the recording file.
	std::string nnrFile;
	nnrFile = fileName + ".nnr";
	file.open(nnrFile, std::ios::binary);

	loadState.loadFromFile(fileName);

	exout.resize(os);

	//std::cout << "\nFile loading success!\n";
	//std::cout << "Starting read nn states phase.\n\n";

	while (!file.eof()) {

		samplePoints.clear();
		centroid.clear();
		// The +1 is for including the neuron output (av) value.
		centroid.resize(neuron->getNumConnections() + 1);

		// Retrives all the neuron sample points and average centroid.
		if (!getSamplePoints(neuron, &loadState, minRes, file))
			break;

		//std::cout << "\tSample points read.\n";
		//std::cout << "\tCalculating md plane of best fit.\n\n";

		// Stores the average plane weights.
		std::vector<float> weights = calculateWeights();

		// Now finally merge the plane of best fit with current weights/bias.
		neuron->setConnections(weights, strength);

		// Quickly find bias (intercept) using new weights and centroid.
		float bias = centroid.back();
		for (int d = 0; d < centroid.size() - 1; d++) {
			bias -= weights.at(d) * centroid.at(d);
		}

		neuron->setBias(bias, strength);

	}

	file.close();

}

//================================================================================
// File handling.

void TrainingNeuralNetwork::loadFromFile(std::string fileName) {

	fileName += ".nn";

	std::ifstream file;
	file.open(fileName, std::ios::binary);

	unsigned int is, os, hn;
	//file >> is >> os >> hn;

	file.read((char*)&is, sizeof(unsigned int));
	file.read((char*)&os, sizeof(unsigned int));
	file.read((char*)&hn, sizeof(unsigned int));

	setNeurons(is, os, hn);

	for (int n = 0; n < neurons.size(); n++) {

		unsigned int numConnections;

		//file >> numConnections;
		file.read((char*)&numConnections, sizeof(int));

		//std::cout << "\nSize: " << numConnections << std::endl;

		for (int c = 0; c < numConnections; c++) {

			unsigned int nID;
			//file >> nID;
			file.read((char*)&nID, sizeof(unsigned int));

			float nWeight;
			//file >> nWeight;
			file.read((char*)&nWeight, sizeof(float));

			//std::cout << "to: " << nID << std::endl;
			//std::cout << "weight: " << nWeight << std::endl;

			neurons[n].addConnection(&neurons[nID], nWeight);

		}

	}

}

void TrainingNeuralNetwork::saveToFile(std::string fileName) {

	fileName += ".nn";

	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);

	unsigned int is, os, hn;
	is = inputs.size();
	os = outputs.size();
	hn = neurons.size() - inputs.size() - outputs.size();

	file.write((char*)&is, sizeof(int));
	file.write((char*)&os, sizeof(int));
	file.write((char*)&hn, sizeof(int));

	//file << inputs.size()  << "\n";
	//file << outputs.size() << "\n";
	//file << neurons.size() - inputs.size() - outputs.size() << "\n";

	for (TrainingNeuron n : neurons) {

		n.saveConnectionsStatus(&file);

	}

	file.close();

}
