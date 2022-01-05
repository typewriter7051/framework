#include "tnn.h"

//================================================================================
// Constructors.

TrainingNeuralNetwork::TrainingNeuralNetwork() {

	recordMode = false;

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

	}

	sd = sqrt(sd) / float(actualOutput.size());

	return sd;

}

float TrainingNeuralNetwork::getCostP(std::vector<float>* foutputs) {

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

// Runs the neural network without resetting input values.
std::vector<float> TrainingNeuralNetwork::runNeuralNetwork() {

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

	for (Neuron n : neurons) {

		n.saveConnectionsStatus(&file);

	}

	file.close();

}

//================================================================================
// Recording.

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

void TrainingNeuralNetwork::readState(NeuralNetwork* nn, std::ifstream* trainFile) {

	// stupid fucking piece of shit one liner.
	//trainFile->read((char*) nn->neurons.data(), sizeof(float) * nn->neurons.size());

	for (int neuron = 0; neuron < nn->neurons.size(); neuron++) {

		float av;
		trainFile->read((char*)&av, sizeof(float));

		nn->neurons.at(neuron).setValue(av);

	}

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

float TrainingNeuralNetwork::findMinAV(TrainingNeuron* neuron, TrainingNeuralNetwork& loadState, int minRes) {

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

	return minCostAV;

}

//--------------------------------------------------------------------------------

void TrainingNeuralNetwork::getSamplePoints(Neuron* neuron, std::vector<float>* centroid,
	std::vector<float>* samplePoints, int minRes, std::ifstream& file) {

	unsigned int numSamples = 0;

	// Iterate through sampleSize samples and calculate the centroid.
	for (int s = 0; s < sampleSize; s++) {

		// Read the next loadstate from file.
		readState(&loadState, &file);

		if (file.eof()) {

			file.close();
			return;

		}

		// Read the expected output data.
		file.read((char*)exout.data(), sizeof(float) * os);

		//---Find the optimal neuron av and calculate weight/bias of best fit.---

		float minCostAV = findMinAV(neuron, loadState, minRes);

		//--------------------------------------------------------------------------------
		// Update the centroid.

		// Get the list of pointers to its connected neurons (inputs).
		std::vector<Neuron*> connections = neuron->getConnections();

		for (int n = 0; n < connections.size(); n++) {

			connections.at(n)->setDone(); // Just for efficeincy. No need to re-calculate the child node values.
			centroid.at(n) = (centroid.at(n) * numSamples + connections[n]->getValue()) / float(numSamples + 1);
			samplePoints.push_back(connections.at(n)->getValue());

		}

		centroid.back() = (centroid.back() * numSamples + minCostAV) / float(numSamples + 1);
		samplePoints.push_back(minCostAV);

		numSamples++;

	}

}

void TrainingNeuralNetwork::trainNeuralNetwork(std::string fileName,
	TrainingNeuron* neuron, unsigned int sampleSize, int minRes) {

	std::ifstream file;
	unsigned int is, os, hn;

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

	// List to hold expected outputs of each state.
	std::vector<float> exout(os);

	while (!file.eof()) {

		// The +1 is for including the neuron output (av) value.
		centroid.resize(neuron->getNumConnections() + 1);
		samplePoints.clear();

		// Retrives all the neuron sample points and average centroid.
		getSamplePoints(neuron, &centroid, &samplePoints, minRes, file);

		//---Then calculate plane of best fit and merge with previous plane of best fit.---

		// Stores the average plane weights.
		std::vector<float> weights(neuron->getNumConnections());
		unsigned int weightCount = 0;
		float bias = 0;

		// Used for accessing the samplePoints vector.
		unsigned int globalIndex = 0;
		// Adds up all the planes calculated by the sample points to create an average plane of best fit.
		for (int s = 0; s < sampleSize; s++) {

			//================================================================================
			//---Calculate the plane of best fit. This is done by averaging all the---
			//---planes created by connecting each point to the centroid.---

			// Local weight and bias, is later added into the average.
			std::vector<float> localW(neuron->getNumConnections());
			float localB = 0;
			float addedDist = 0;
			float Sd = 0;
			float b = 0;

			// Find sum of the distance from centroid in each axis
			// (not including dependent axis)
			for (int n = 0; n < centroid.size() - 1; n++) {

				samplePoints.at(globalIndex) -= centroid.at(n);
				addedDist += samplePoints.at(globalIndex);
				Sd += samplePoints.at(globalIndex) * samplePoints.at(globalIndex);

				globalIndex++;

			}

			// Find zdist.
			samplePoints.at(globalIndex) -= centroid.back();
			float zDist = samplePoints.at(globalIndex);

			// Only find and merge plane if the selected
			// point isn't directly above the centroid.
			if (addedDist != 0) {

				// Calculate S (in formula).
				float S = addedDist * zDist / Sd;

				// Reset globalIndex to be reused in the next for loop.
				globalIndex -= centroid.size() + 1;

				//================================================================================
				//---Calculate optimal weights and merge them with average.---

				for (int n = 0; n < weights.size(); n++) {

					float localWeight = S * samplePoints.at(globalIndex) / addedDist;
					b -= samplePoints.at(globalIndex) / addedDist * centroid.at(n);

					weights.at(n) = (weights.at(n) * weightCount + localWeight) / float(weightCount + 1);

					globalIndex++;

				}

				// Calculate optimal bias and merge with average.
				localB = S * b;
				bias = (bias * weightCount + localB) / float(weightCount + 1);

			}

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