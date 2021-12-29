#include <fstream>
#include <iostream>
#include <math.h>
#include "nn.h"

//================================================================================
// Constructors.

NeuralNetwork::NeuralNetwork() {

	recordMode = false;

}

//================================================================================
// Getters.

std::vector<Neuron*> NeuralNetwork::getInputs() {

	return inputs;

}

std::vector<Neuron*> NeuralNetwork::getOutputs() {

	return outputs;

}

std::vector<Neuron*> NeuralNetwork::getArray(unsigned int start, unsigned int end) {

	std::vector<Neuron*> temp(end - start + 1);

	for (int i = 0; i <= end - start; i++) {

		temp.at(i) = &neurons.at(start + i);

	}

	return temp;

}

Neuron* NeuralNetwork::getNeuron(unsigned int index) {

	return &neurons.at(index);

}

float NeuralNetwork::getCostP(std::vector<float>* foutputs) {

	std::vector<float> actualOutput = runNeuralNetwork();

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

float NeuralNetwork::getCost(std::vector<float>* finputs, std::vector<float>* foutputs) {

	std::vector<float> actualOutput = runNeuralNetwork(finputs);

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

// Runs the neural network and returns the outputs in a list.
std::vector<float> NeuralNetwork::runNeuralNetwork(std::vector<float>* finputs) {

	if (finputs->size() != inputs.size()) {

		std::cout << "input array doesn't match nn inputs!\n";
		return std::vector<float>(1);

	}

	// Clear finished status for all neurons.
	for (int n = 0; n < neurons.size(); n++)
		neurons[n].setUndone();

	// Set up the input neurons.
	for (int n = 0; n < inputs.size(); n++)
		inputs.at(n)->setValue(finputs->at(n));

	// Vector to be returned.
	std::vector<float> rv;

	// Call getValue() for all output neurons and copy results to returnVector.
	for (Neuron* n : outputs) {

		rv.push_back(n->getValue());

	}

	return rv;

}

// Runs the neural network without resetting input values.
std::vector<float> NeuralNetwork::runNeuralNetwork() {

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
// Neuron creation and handling.

// Sets up the input and output nodes.
void NeuralNetwork::setNeurons(unsigned int numInputs, unsigned int numOutputs, unsigned int h) {

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

void NeuralNetwork::setupWeights(float min, float max) {

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].setupAverageConnections(min, max);

	}

}

void NeuralNetwork::fullyConnectNeurons(std::vector<Neuron*> layerB, std::vector<Neuron*> layerA) {

	for (Neuron* b : layerB) {
		for (Neuron* a : layerA) {

			b->addConnection(a);

		}
	}

}

//================================================================================
// File handling.

void NeuralNetwork::saveToFile(std::string fileName) {

	fileName += ".nn";

	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);

	unsigned int is, os, hn;
	is = inputs.size();
	os = outputs.size();
	hn = neurons.size() - inputs.size() - outputs.size();

	file.write((char*) &is, sizeof(int));
	file.write((char*) &os, sizeof(int));
	file.write((char*) &hn, sizeof(int));

	//file << inputs.size()  << "\n";
	//file << outputs.size() << "\n";
	//file << neurons.size() - inputs.size() - outputs.size() << "\n";

	for (Neuron n : neurons) {

		n.saveConnectionsStatus(&file);

	}

	file.close();

}

void NeuralNetwork::loadFromFile(std::string fileName) {

	fileName += ".nn";

	std::ifstream file;
	file.open(fileName, std::ios::binary);

	unsigned int is, os, hn;
	//file >> is >> os >> hn;

	file.read((char*) &is, sizeof(unsigned int));
	file.read((char*) &os, sizeof(unsigned int));
	file.read((char*) &hn, sizeof(unsigned int));

	setNeurons(is, os, hn);

	for (int n = 0; n < neurons.size(); n++) {

		unsigned int numConnections;

		//file >> numConnections;
		file.read((char*) &numConnections, sizeof(int));

		for (int c = 0; c < numConnections; c++) {

			unsigned int nID;
			//file >> nID;
			file.read((char*) &nID, sizeof(unsigned int));

			float nWeight;
			//file >> nWeight;
			file.read((char*) &nWeight, sizeof(float));

			neurons[n].addConnection(&neurons[nID], nWeight);

		}

	}

}

//================================================================================
// Recording.

void NeuralNetwork::startRecording(std::string fileName) {

	recordMode = true;

	fileName += ".nnr";
	recordFile.open(fileName, std::ios_base::app | std::ios::binary);

}

void NeuralNetwork::stopRecording() {

	recordFile.close();
	recordMode = false;

}

std::vector<float> NeuralNetwork::captureNeuralNetwork(std::vector<float>* finputs, std::vector<float>* foutputs) {

	std::vector<float> rv = runNeuralNetwork(finputs);

	unsigned int a = 0;

	// Ok to use for-each since the neurons aren't being altered.
	for (Neuron n : neurons) {

		//recordFile << n.getValue() << "\n";
		float value = n.getValue();
		recordFile.write((char*) &value, sizeof(float));
		a += sizeof(float);

	}

	for (float f : *foutputs) {

		//recordFile << f << "\n";
		recordFile.write((char*) &f, sizeof(float));
		a += sizeof(float);

	}

	return rv;

}

void NeuralNetwork::readState(NeuralNetwork* nn, std::ifstream* trainFile) {

	// stupid fucking piece of shit one liner.
	//trainFile->read((char*) nn->neurons.data(), sizeof(float) * nn->neurons.size());

	for (int neuron = 0; neuron < nn->neurons.size(); neuron++) {

		float av;
		trainFile->read((char*) &av, sizeof(float));

		nn->neurons.at(neuron).setValue(av);

	}

}
void NeuralNetwork::readState(NeuralNetwork* nn, NeuralNetwork* on) {

	if (nn->neurons.size() != on->neurons.size()) {

		std::cout << "ATTEMPTED TO COPY STATE OF UNIDENTICAL NETWORKS!";
		return;

	}

	for (int neuron = 0; neuron < nn->neurons.size(); neuron++) {

		float av = on->neurons.at(neuron).getValue();
		nn->neurons.at(neuron).setValue(av);

	}

}

void NeuralNetwork::trainNeuralNetwork(std::string fileName, Neuron* neuron, unsigned int sampleSize, int minRes) {

	std::ifstream file;
	unsigned int is, os, hn;

	// Read the nn structure data from partner file.
	std::string nnFile;
	nnFile = fileName + ".nn";
	file.open(nnFile, std::ios::binary);
	file.read((char*) &is, sizeof(unsigned int));
	file.read((char*) &os, sizeof(unsigned int));
	file.read((char*) &hn, sizeof(unsigned int));
	file.close();
	file.clear(); // For safety.

	// Then load the recording file.
	std::string nnrFile;
	nnrFile = fileName + ".nnr";
	file.open(nnrFile, std::ios::binary);

	NeuralNetwork loadState;
	loadState.loadFromFile(fileName);

	// List to hold expected outputs of each state.
	std::vector<float> exout(os);

	while (!file.eof()) {

		// The +1 is for including the neuron output (av) value.
		std::vector<float> centroid(neuron->getNumConnections() + 1);
		unsigned int numSamples = 0;

		std::vector<float> samplePoints;
		// Iterate through sampleSize samples and get average weight change.
		for (int s = 0; s < sampleSize; s++) {

			// Set loadstate from file.
			readState(&loadState, &file);

			if (file.eof()) {

				file.close();
				return;

			}

			// Read the expected output data.
			file.read((char*) exout.data(), sizeof(float) * os);

			//---Find the optimal neuron av and calculate weight/bias of best fit.---

			float minCost = 1000;
			float minCostAV = 0;

			for (int i = 0; i < minRes + 1; i++) {

				// Set loadstate from load state before running the nn again.
				readState(this, &loadState);

				float avSamplePoint = -1 + 2 * i / float(minRes);
				neuron->setValue(avSamplePoint);
				float curCost = this->getCostP(&exout);

				if (curCost < minCost) {

					minCost = curCost;
					minCostAV = avSamplePoint;

				}

			}

			//---Now we should have the target av that brings the cost to its lowest.---

			// Update the centroid.

			// Get the list of pointers to its connected neurons (inputs).
			std::vector<Neuron*> connections = neuron->getConnections();

			for (int n = 0; n < connections.size(); n++) {

				connections.at(n)->setDone();
				centroid.at(n) = (centroid.at(n) * numSamples + connections[n]->getValue()) / float(numSamples + 1);
				samplePoints.push_back(connections.at(n)->getValue());

			}

			centroid.back() = (centroid.back() * numSamples + minCostAV) / float(numSamples + 1);
			samplePoints.push_back(minCostAV);

			numSamples++;

			//--------------------------------------------------------------------------------
			// OLD METHOD. Not used because it doesn't calculate optimal bias.
			/*
			// Cost function if neuron was decreased and increased.
			float lCost, hCost;

			// Reset the nn and calculate cost of higher neuron av.
			readState(this, &loadState);
			n->setValue(n->getValue() + strength);
			n->setDone();
			hCost = this->getCostP(&exout);

			// Reset the nn and calculate cost of lower neuron av.
			readState(this, &loadState);
			n->setValue(n->getValue() - strength);
			n->setDone();
			lCost = this->getCostP(&exout);

			// Set the activation value target to be the lower of the two.
			float avAim = (lCost < hCost) ? lCost : hCost;
			*/
			//--------------------------------------------------------------------------------

		}

		// Then calculate plane of best fit and merge with previous plane of best fit.

		// Stores the average plane weights.
		std::vector<float> weights(neuron->getNumConnections());
		unsigned int weightCount = 0;
		float bias = 0;

		// Used for accessing the samplePoints vector.
		unsigned int globalIndex = 0;
		// Adds up all the planes calculated by the sample points to create an average plane of best fit.
		for (int s = 0; s < sampleSize; s++) {

			float addedDist = 0;

			// Calculate local distances from centroid specific to each axis.
			for (int n = 0; n < centroid.size(); n++) {

				samplePoints.at(globalIndex) -= centroid.at(n);
				addedDist += abs(samplePoints.at(globalIndex));

				globalIndex++;

			}

			// Last element of the previous for loop.
			float zDist = samplePoints.at(globalIndex - 1);

			globalIndex -= centroid.size();

			// weight = (localDist from centroid) / (added dist from centroid) * zDistance.

			for (int n = 0; n < weights.size(); n++) {

				float localWeight = samplePoints.at(globalIndex) / addedDist * zDist;

				weights.at(n) = (weights.at(n) * weightCount + localWeight) / float(weightCount + 1);

				globalIndex++;

			}

			// Calculate the bias given weights and centroid.
			float zVal = 0;
			for (float w = 0; w < weights.size(); w++) {

				// z = a * x + b * y + ...
				zVal += weights.at(w) * centroid.at(w);

			}

			float newBias = centroid.back() - zVal;

			bias = (bias * weightCount + newBias) / float(weightCount + 1);

			weightCount++;
			globalIndex++;

		}
		// Now finally merge the plane of best fit with current weights/bias.

		float strength = 1;
		neuron->setConnections(weights, strength);

		float newBias = neuron->getBias() * (1 - strength) + bias * strength;
		neuron->setBias(newBias);

	}

	file.close();

}
