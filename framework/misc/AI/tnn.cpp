#include <cmath>
#include "tnn.h"

//================================================================================
// Constructors.

TrainingNeuralNetwork::TrainingNeuralNetwork() {

	recordMode = false;
	is = 0;
	os = 0;
	hn = 0;

}

//================================================================================
// Getters.

float TrainingNeuralNetwork::getCost(std::vector<float>* finputs, std::vector<float>* foutputs) {

	std::vector<float> actualOutput = runNeuralNetwork(finputs);

	if (foutputs->size() != actualOutput.size()) {

		std::cout << "\nWARNING: EXPECTED OUTPUTS SIZE DOESNT MATCH NN OUTPUT SIZE";
		std::cout << " outputs passed (" << foutputs->size() << ") expected (" << actualOutput.size() << ")";
		return 1;

	}

	// Calculate standard deviation from expected output (cost).

	float sd = 0;

	for (int i = 0; i < actualOutput.size(); i++) {

		sd += (actualOutput.at(i) - foutputs->at(i)) * (actualOutput.at(i) - foutputs->at(i));
		//std::cout << "Expected output vs actual output: " << foutputs->at(i) << ", " << actualOutput.at(i) << std::endl;

	}

	sd = sqrt(sd) / float(actualOutput.size());

	return sd;

}

float TrainingNeuralNetwork::getCostP(std::vector<float>* foutputs) {

	std::vector<float> actualOutput = rerunNeuralNetwork();

	if (foutputs->size() != actualOutput.size()) {

		std::cout << "\nWARNING: EXPECTED OUTPUTS SIZE DOESNT MATCH NN OUTPUT SIZE";
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

std::vector<TrainingNeuron*> TrainingNeuralNetwork::getInputs() {

	return inputs;

}

std::vector<TrainingNeuron*> TrainingNeuralNetwork::getOutputs() {

	return outputs;

}

int TrainingNeuralNetwork::getNumHiddenNeurons() {

	return neurons.size() - inputs.size() - outputs.size();

}

int TrainingNeuralNetwork::getNumUnhiddenNeurons() {

	return inputs.size() + outputs.size();

}

int TrainingNeuralNetwork::getNumNeurons() {

	return neurons.size();

}


//================================================================================
// Setters.

TrainingNeuron* TrainingNeuralNetwork::getNeuron(unsigned int index) {

	return &neurons.at(index);

}

std::vector<TrainingNeuron*> TrainingNeuralNetwork::getArray(unsigned int start, unsigned int end) {

	std::vector<TrainingNeuron*> temp(end - start + 1);

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
	is = numInputs;
	os = numOutputs;
	hn = h;

	for (int i = 0; i < numInputs; i++) { inputs.push_back(&neurons[i]); }
	for (int o = 0; o < numOutputs; o++) { outputs.push_back(&neurons[numInputs + o]); }

}

void TrainingNeuralNetwork::setupWeights(float min, float max) {

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].setupAverageConnections(min, max);

	}

}

void TrainingNeuralNetwork::fullyConnectNeurons(std::vector<TrainingNeuron*> layerB, std::vector<TrainingNeuron*> layerA) {

	for (Neuron* b : layerB) {
		for (Neuron* a : layerA) {

			b->addConnection(a);

		}
	}

}

//--------------------------------------------------------------------------------

// Runs the neural network and returns the outputs in a list.
std::vector<float> TrainingNeuralNetwork::runNeuralNetwork(std::vector<float>* finputs) {

	if (finputs->size() != inputs.size()) {

		std::cout << "WARNING: input array doesn't match nn inputs! (" << finputs->size() << " vs " << inputs.size() << ")\n";
		return std::vector<float>(1);

	}

	// Clear finished status for all neurons.
	for (int n = 0; n < neurons.size(); n++)
		neurons[n].setUndone();

	// Set up the input neurons.
	setInputs(finputs);

	// Vector to be returned.
	std::vector<float> rv;

	// Call getValue() for all output neurons and copy results to returnVector.
	for (Neuron* n : outputs) {

		rv.push_back(n->getValue());

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

// Does not overwrite inputs/outputs.
void TrainingNeuralNetwork::readState(TrainingNeuralNetwork* nn, TrainingNeuralNetwork* on) {

	if (nn->neurons.size() != on->neurons.size() ||
		nn->getNumUnhiddenNeurons() != on->getNumUnhiddenNeurons()) {

		std::cout << "WARNING: ATTEMPTED TO COPY STATE OF UNIDENTICAL NETWORKS!";
		return;

	}

	for (int neuron = nn->getNumUnhiddenNeurons(); neuron < nn->neurons.size(); neuron++) {

		float av = on->neurons.at(neuron).getValue();
		nn->neurons.at(neuron).setValue(av);

	}

}

//--------------------------------------------------------------------------------

void TrainingNeuralNetwork::trainNeuralNetwork(std::vector<float> samples, float stepSize, float strength) {

	if (samples.size() % (inputs.size() + outputs.size()) != 0) {

		std::cout << "\nWARNING: In trainNeuralNetwork() size of list not valid!\n";
		return;

	}

	//--------------------------------------------------------------------------------
	// Member definitions.

	is = inputs.size();
	os = outputs.size();
	hn = neurons.size() - is - os;

	TrainingNeuralNetwork loadState;
	loadState.setNeurons(is, os, hn);

	unsigned int batchSize = samples.size() / float(is + os);

	// List of list of each neuron's derivatives (including bias for each neuron).
	std::vector<std::vector<float>> derivatives;

	// Initialize the derivatives list.
	derivatives.clear();
	derivatives.resize(neurons.size());

	for (int n = 0; n < neurons.size(); n++) {

		// The +1 is for including the bias.
		derivatives.at(n).resize(neurons.at(n).getNumConnections() + 1);

	}

	//--------------------------------------------------------------------------------
	// 

	for (int i = 0; i < batchSize; i++) {

		//--------------------------------------------------------------------------------
		// Read the next inputs and outputs and create the loadstate.

		int index = i * (is + os);

		// When passing iterators to the vector constructor, the upper range is exclusive (no need for "- 1").
		std::vector<float> newInputs(samples.begin() + index, samples.begin() + index + is);
		std::vector<float> newOutputs(samples.begin() + index + is, samples.begin() + index + is + os);

		// Set up the input neurons.
		setInputs(&newInputs);

		readState(&loadState, this);

		//--------------------------------------------------------------------------------
		// Update the derivatives list.

		// Iterate through every neuron (except inputs because they have no child neurons).
		for (int n = is; n < neurons.size(); n++) {

			// Retrieve the neuron pointer from the network.
			TrainingNeuron* neuron = &neurons.at(n);

			// Get the list of pointers to its child neurons (inputs).
			std::vector<Neuron*> connections = neuron->getConnections();

			readState(this, &loadState);
			float cost = this->getCostP(&newOutputs);

			// Iterate through weights and find the
			// cost's derivative with respect to weight.
			for (int cn = 0; cn < neuron->getNumConnections(); cn++) {

				// Weight.
				readState(this, &loadState);
				neuron->moveWeight(cn, stepSize);
				float cost2 = this->getCostP(&newOutputs);
				neuron->moveWeight(cn, -stepSize);

				float dcost = (cost2 - cost) / stepSize;
				derivatives.at(n).at(cn) -= dcost / float(batchSize);

			}

			// Bias.
			readState(this, &loadState);
			neuron->moveBias(stepSize);
			float cost2 = this->getCostP(&newOutputs);
			neuron->moveBias(-stepSize);

			float dcost = (cost2 - cost) / stepSize;
			derivatives.at(n).back() -= dcost / float(batchSize);

		}

	}

	//--------------------------------------------------------------------------------
	// Move the members after calculating gradient.

	moveMembers(&derivatives, strength);

}

void TrainingNeuralNetwork::setInputs(std::vector<float>* i) {

	if (i->size() != inputs.size()) {

		std::cout << "\nWARNING: called function setInputs() with invalid vector size!\n";
		return;

	}

	for (int n = 0; n < inputs.size(); n++) {

		inputs.at(n)->setValue(i->at(n));
		inputs.at(n)->setDone();

	}

}

void TrainingNeuralNetwork::moveMembers(std::vector<std::vector<float>>* values, float strength) {

	if (values->size() != neurons.size()) {

		std::cout << "\nWARNING: called function moveMenbers() with invalid vector size!\n";
		return;

	}

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].moveMembers(&values->at(n), strength);

	}

}

//================================================================================
// File handling.

/*

* The training neural network (tnn) file contains a few extra details including 
* the extra data from training neuron as opposed to regular neurons.
* 
* 
* 
* 
* 
* 
* 
* 
*/

void TrainingNeuralNetwork::loadFromFile(std::string fileName) {

	fileName += ".tnn";

	std::ifstream file;
	file.open(fileName, std::ios::binary);

	// Read network info.
	unsigned int is, os, hn;
	file.read((char*) &is, sizeof(unsigned int));
	file.read((char*) &os, sizeof(unsigned int));
	file.read((char*) &hn, sizeof(unsigned int));
	setNeurons(is, os, hn);

	for (int n = 0; n < neurons.size(); n++) {

		// Read activation function.
		ActivationFunction::NonLinearMethod af;
		file.read((char*)&af, sizeof(uint8_t));
		neurons.at(n).setActivationFunction(af);

		// Read bias.
		float bias = 0;
		file.read((char*)&bias, sizeof(float));
		neurons.at(n).setBias(bias);

		// Read number of connections(weights).
		unsigned int numConnections;
		file.read((char*)&numConnections, sizeof(unsigned int));

		// Read connections.
		for (int c = 0; c < numConnections; c++) {

			unsigned int nID;
			file.read((char*)&nID, sizeof(unsigned int));

			float nWeight;
			file.read((char*)&nWeight, sizeof(float));

			neurons[n].addConnection(&neurons[nID], nWeight);

		}

	}

}

void TrainingNeuralNetwork::saveToFile(std::string fileName) {

	fileName += ".tnn";

	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);

	unsigned int is, os, hn;
	is = inputs.size();
	os = outputs.size();
	hn = neurons.size() - inputs.size() - outputs.size();

	file.write((char*)&is, sizeof(int));
	file.write((char*)&os, sizeof(int));
	file.write((char*)&hn, sizeof(int));

	for (TrainingNeuron n : neurons) {

		n.saveConnectionsStatus(&file);

	}

	file.close();

}
