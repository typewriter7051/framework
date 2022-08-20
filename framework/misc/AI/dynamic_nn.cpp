#include "dynamic_nn.h"
#include <iostream>
#include <cmath>

//================================================================================
// Constructors.

DynamicNeuralNetwork::DynamicNeuralNetwork() {

	is = 0;
	os = 0;
	hn = 0;

}

//================================================================================
// Getters.

std::vector<DynamicNeuron*> DynamicNeuralNetwork::getInputs() {

	return inputs;

}

std::vector<DynamicNeuron*> DynamicNeuralNetwork::getOutputs() {

	return outputs;

}

std::vector<DynamicNeuron*> DynamicNeuralNetwork::getNeurons() {

	std::vector<DynamicNeuron*> n;

	for (DynamicNeuron tn : neurons)
		n.push_back(&tn);

	return n;

}

int DynamicNeuralNetwork::getNumHiddenNeurons() {

	return neurons.size() - inputs.size() - outputs.size();

}

int DynamicNeuralNetwork::getNumUnhiddenNeurons() {

	return inputs.size() + outputs.size();

}

int DynamicNeuralNetwork::getNumNeurons() {

	return neurons.size();

}

DynamicNeuron* DynamicNeuralNetwork::getNeuron(unsigned int index) {

	return &neurons.at(index);

}

std::vector<DynamicNeuron*> DynamicNeuralNetwork::getArray(unsigned int start, unsigned int end) {

	std::vector<DynamicNeuron*> temp(end - start + 1);

	for (int i = 0; i <= end - start; i++) {

		temp.at(i) = &neurons.at(start + i);

	}

	return temp;

}

// Runs the neural network and returns the outputs in a list.
std::vector<float> DynamicNeuralNetwork::runNeuralNetwork(std::vector<float>* finputs) {

	if (finputs->size() != inputs.size()) {

		std::cout << "WARNING: input array doesn't match nn inputs! (" << finputs->size() << " vs " << inputs.size() << ")\n";
		return std::vector<float>(1);

	}

	// Clear any metadata for all neurons.
	resetNeurons();

	// Set up the input neurons.
	setInputs(finputs);

	// Vector to be returned.
	std::vector<float> rv;

	// Call getValue() for all output neurons and copy results to returnVector.
	for (DynamicNeuron* n : outputs) {

		rv.push_back(n->getValue());

	}

	return rv;

}

float DynamicNeuralNetwork::getCost(std::vector<float>* finputs, std::vector<float>* foutputs) {

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

	}

	sd = sqrt(sd) / float(actualOutput.size());

	return sd;

}

//================================================================================
// Network wrangling.

// Sets up the input and output nodes.
void DynamicNeuralNetwork::setNeurons(unsigned int numInputs, unsigned int numOutputs, unsigned int h) {

	// Completely clear the network and reset neuron ID counter.
	neurons.clear();
	inputs.clear();
	outputs.clear();
	DynamicNeuron::resetIDCounter();

	// Reset and re-initialize the input/output pointer lists.
	neurons.resize(numInputs + numOutputs + h);
	is = numInputs;
	os = numOutputs;
	hn = h;

	for (int i = 0; i < numInputs; i++) { inputs.push_back(&neurons[i]); }
	for (int o = 0; o < numOutputs; o++) { outputs.push_back(&neurons[numInputs + o]); }

}

void DynamicNeuralNetwork::setupWeights(float min, float max) {

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].setupAverageConnections(min, max);

	}

}

void DynamicNeuralNetwork::fullyConnectNeurons(std::vector<DynamicNeuron*> layerB, std::vector<DynamicNeuron*> layerA) {

	for (DynamicNeuron* b : layerB) {
		for (DynamicNeuron* a : layerA) {

			b->addConnection(a);

		}
	}

}

void DynamicNeuralNetwork::setActivationFunction(std::vector<DynamicNeuron*> neurons, ActivationFunction::NonLinearMethod method) {

	for (DynamicNeuron* n : neurons)
		n->setActivationFunction(method);

}

void DynamicNeuralNetwork::resetNeurons() {

	for (int n = 0; n < neurons.size(); n++) {

		neurons[n].setUndone();
		neurons[n].resetNumParents();

	}

}

void DynamicNeuralNetwork::trainNeuralNetwork(std::vector<float> samples, float stepSize) {

	if (samples.size() % (inputs.size() + outputs.size()) != 0) {

		std::cout << "\nWARNING: In trainNeuralNetwork() size of list not valid!\n";
		return;

	}

	unsigned int batchSize = samples.size() / float(is + os);

	/*
	The derivative record is a 2D list where the first dimension is the neuron
	and the 2nd dimension is the bias + weights.

	- Neuron 1:
		- AV before activation function/Bias (they're the same).
		- Weight 1
		- Weight 2
		...
	-Neuron 2:
		- AV before activation function/Bias
		- Weight 1
		- Weight 2
		...
	...

	Example: bias of neuron 2 would be derivRecord[1][0].
	*/
	std::vector<std::vector<float>> avgDerivRecord;
	float numParams = 0;

	for (int n = 0; n < neurons.size(); n++) { // For all neurons.

		std::vector<float> temp;
		temp.resize(neurons.at(n).getNumConnections() + 1); // The +1 is for including the bias.
		numParams += neurons.at(n).getNumConnections() + 1;
		avgDerivRecord.push_back(temp);

	}

	std::vector<int> countRecord;
	countRecord.resize(neurons.size());
	std::vector<std::vector<float>> derivRecord = avgDerivRecord;

	for (int i = 0; i < batchSize; i++) {

		//----------------------------------------------------------------------------
		// Read the next inputs and outputs.

		int index = i * (is + os);

		// Upper bound for std::vector<> constructor is exclusive so no need for -1 at the end.
		std::vector<float> newInputs(samples.begin() + index, samples.begin() + index + is);
		std::vector<float> newExpectedOutputs(samples.begin() + index + is, samples.begin() + index + is + os);

		float cost = getCost(&newInputs, &newExpectedOutputs);

		// Reset countRecord.
		for (int i = 0; i < countRecord.size(); i++) countRecord.at(i) = 0;

		//----------------------------------------------------------------------------
		// Calculate derivatives.

		for (int o = 0; o < os; o++) {

			// Because calling getCost() already runs the neural network, we can simply retrieve
			// the output values from the network for finding the residual.
			float residual = outputs.at(o)->getValue() - newExpectedOutputs.at(o);
			float dCost = residual / (outputs.size() * cost);

			// Manually initialize the derivative record for the output neuron.
			// This is needed because the getDerivative() function relies on
			// the neurons having parent connections (which outputs do not have).
			derivRecord.at(is + o).at(0) = dCost;

			outputs.at(o)->getDerivative(&countRecord, &derivRecord, dCost);

		}

		int derivativesDone = 0;

		//----------------------------------------------------------------------------
		// Once derivRecord is complete, add it to the average.

		for (int n = 0; n < neurons.size(); n++) {
			for (int nc = 0; nc < neurons.at(n).getNumConnections() + 1; nc++) {

				avgDerivRecord.at(n).at(nc) -= derivRecord.at(n).at(nc) / (float(batchSize) * numParams);

			}
		}

		int avgDone = 0;

	}

	// Update the weights/bias.
	moveMembers(&avgDerivRecord, stepSize);

	// TODO: Trim neurons if needed.

}

void DynamicNeuralNetwork::setInputs(std::vector<float>* i) {

	if (i->size() != inputs.size()) {

		std::cout << "\nWARNING: called function setInputs() with invalid vector size!\n";
		return;

	}

	for (int n = 0; n < inputs.size(); n++) {

		inputs.at(n)->setValue(i->at(n));
		inputs.at(n)->setDone();

	}

}

void DynamicNeuralNetwork::moveMembers(std::vector<std::vector<float>>* values, float strength) {

	// First check the size of the first dimension.
	if (values->size() != neurons.size()) {

		std::cout << "\nWARNING: called function moveMembers() with invalid vector size!\n";
		return;

	}

	for (int n = 0; n < neurons.size(); n++) {

		// Check the size of each secondary list.
		if (values->at(n).size() != neurons.at(n).getNumConnections() + 1) {

			std::cout << "\nWARNING: called function moveMembers() with invalid vector size!\n";
			return;

		}

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

void DynamicNeuralNetwork::loadFromFile(std::string fileName) {

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

void DynamicNeuralNetwork::saveToFile(std::string fileName) {

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

	for (DynamicNeuron n : neurons) {

		n.saveConnectionsStatus(&file);

	}

	file.close();

}
