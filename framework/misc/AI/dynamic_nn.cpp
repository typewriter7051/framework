#include "dynamic_nn.h"
#include <iostream>
#include <cmath>
#include <algorithm>
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

std::vector<DynamicNeuron*> DynamicNeuralNetwork::getArray( unsigned int start, unsigned int end) {

	std::vector<DynamicNeuron*> temp(end - start);

	for (int i = 0; i < end - start; i++)
		temp.at(i) = &neurons.at(start + i);

	return temp;
}
//==============================================================================
// Runs the neural network and returns the outputs in a list.

std::vector<float> DynamicNeuralNetwork::runNeuralNetwork( std::vector<float>* finputs, int profile) {
	if (finputs->size() != inputs.size()) {
		std::cout << "WARNING: input array doesn't match nn inputs! (" << finputs->size() << " vs " << inputs.size() << ")\n";
		return std::vector<float>(1);
	}
	if (profile < 0 || profile >= profiles.size()) {
		std::cout << "WARNING: CALLED runNeuralNetwork() WITH OUT OF BOUNDS PROFILE\n";
		return std::vector<float>(1);
	}

	// Set up the completion record.
	std::vector<bool> cr(neurons.size(), false);
	// Set up the input neurons.
	for (int i = 0; i < inputs.size(); i++)
		profiles.at(profile).at(i) = finputs->at(i);
	// Vector to be returned.
	std::vector<float> rv(outputs.size());

	// Call getValue() for all output neurons and copy results to returnVector.
	for (int n = 0; n < outputs.size(); n++)
		rv[n] = outputs[n]->getValue(&profiles.at(profile), &profiles.at(profile), &cr);

	return rv;
}
//==============================================================================
// Calculates the cost of the neural network using MSE.

float DynamicNeuralNetwork::getCost( std::vector<float>* finputs, std::vector<float>* foutputs, int profile) {
	std::vector<float> actualOutput = runNeuralNetwork(finputs, profile);
	if (foutputs->size() != actualOutput.size()) {
		std::cout << "\nWARNING: EXPECTED OUTPUTS SIZE DOESNT MATCH NN OUTPUT SIZE";
		std::cout << " outputs passed (" << foutputs->size() << ") expected (" << actualOutput.size() << ")";
		return 1;
	}

	// Calculate standard deviation from expected output (cost).
	float sd = 0;
	for (int i = 0; i < actualOutput.size(); i++)
		sd += (actualOutput.at(i) - foutputs->at(i)) * (actualOutput.at(i) - foutputs->at(i));

	sd = sqrt(sd) / float(actualOutput.size());
	return sd;
}
//==============================================================================
// Network wrangling.

// Sets up the input and output nodes.
void DynamicNeuralNetwork::setNeurons( unsigned int numInputs, unsigned int numOutputs, unsigned int h) {
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
	for (int n = 0; n < neurons.size(); n++)
		neurons[n].setupAverageConnections(min, max);
}

void DynamicNeuralNetwork::fullyConnectNeurons(
	std::vector<DynamicNeuron*> layerB,
	std::vector<DynamicNeuron*> layerA) {

	for (DynamicNeuron* b : layerB) {
		for (DynamicNeuron* a : layerA) {
			b->addConnection(a);
		}
	}
}

void DynamicNeuralNetwork::connectNeurons(int indexB, int indexA, bool isRecursive) {
	neurons[indexB].addConnection(&neurons[indexA]);
}

void DynamicNeuralNetwork::setActivationFunction( std::vector<DynamicNeuron*> neurons, ActivationFunction::NonLinearMethod method) {
	for (DynamicNeuron* n : neurons)
		n->setActivationFunction(method);
}

void DynamicNeuralNetwork::removeNeuron(unsigned int ID) {
	if (ID < is + os) {
		std::cout << "WARNING: ATTEMPTED TO CALL removeNeuron() TO REMOVE INPUT OR OUTPUT NEURON!\n";
		return;
	}

	// Remove connections to the removed neuron.
	for (int n = is; n < neurons.size(); n++)
		neurons.at(n).removeConnection(ID);
	// Decrement the pointer to every neuron after the one removed.
	for (int n = is; n < neurons.size(); n++)
		neurons.at(n).decrementConnections(ID);
	// Decrement the ID of every neuron after the one removed.
	for (int n = ID + 1; n < neurons.size(); n++)
		neurons.at(n).decrementID();
	//std::cout << "Erasing neuron " << ID << std::endl;
	// Finally erase the neuron object from the list.
	neurons.erase(neurons.begin() + ID);
	hn--;
}

void DynamicNeuralNetwork::trimDead(float threshold, int profile) {
	float neuronAvg = 0, ncAvg = 0;
	std::vector<unsigned int> removedNeurons;
	
	for (int n = 0; n < neurons.size(); n++) {
		ncAvg += neurons.at(n).getAvgConnection() / float(neurons.size());
		neuronAvg += abs(profiles.at(profile).at(n)) / float(neurons.size());
	}

	for (int n = is; n < neurons.size(); n++) {
		neurons.at(n).removeDeadConnections(ncAvg * threshold);

		// TODO: this only compares the neuron's current value to the threshold instead of its average value.
		if (abs(profiles.at(profile).at(n)) < neuronAvg * threshold && n >= is + os)
			removeNeuron(n);
	}
}
//==============================================================================
// TODO

void DynamicNeuralNetwork::growNeuron() {



}

void DynamicNeuralNetwork::refreshNumParents() {
	for (int n = 0; n < neurons.size(); n++)
		neurons.at(n).resetNumParents();

	std::vector<bool> cr(neurons.size(), false);

	for (DynamicNeuron* o : outputs)
		o->incrementChildParents(&cr);
}

void DynamicNeuralNetwork::trainNeuralNetwork( std::vector<float>* samples, float stepSize, int profile) {
	if (samples->size() % (inputs.size() + outputs.size()) != 0) {
		std::cout << "\nWARNING: In trainNeuralNetwork() size of list not valid!\n";
		return;
	}

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

	std::vector<std::vector<float>> avgDerivRecord(neurons.size());
	unsigned int batchSize = samples->size() / float(is + os);
	float numParams = 0;

	for (int n = 0; n < neurons.size(); n++) { // For all neurons.
		// The +1 is for including the bias.
		avgDerivRecord[n].resize(neurons[n].getNumConnections() + 1);
		numParams += neurons[n].getNumConnections() + 1;
	}

	std::vector<int> countRecord;
	countRecord.resize(neurons.size());
	std::vector<std::vector<float>> derivRecord = avgDerivRecord;
	refreshNumParents();

	for (int i = 0; i < batchSize; i++) {
		//----------------------------------------------------------------------------
		// Read the next inputs and outputs.

		int index = i * (is + os);
		// Upper bound for std::vector<> constructor is exclusive so no need for -1 at the end.
		std::vector<float> newInputs(
			samples->begin() + index,
			samples->begin() + index + is);
		std::vector<float> newExpectedOutputs(
			samples->begin() + index + is,
			samples->begin() + index + is + os);
		//----------------------------------------------------------------------------
		// Reset and initialize records for next sample.

		float cost = getCost(&newInputs, &newExpectedOutputs, profile);
		if (isnan(cost)) {
			std::cout << "\nWARNING: Cost has diverged to infinity (possibly due to gradient explosion).";
			return;
		}
		// Reset countRecord.
		std::fill(countRecord.begin(), countRecord.end(), 0);
		// Reset derivRecord.
		for (int i = 0; i < derivRecord.size(); i++)
			std::fill(derivRecord.at(i).begin(), derivRecord.at(i).end(), 0);
		//----------------------------------------------------------------------------
		// Calculate derivatives.

		// Create completionRecord for the current profile.
		// We want all values to be true because we already ran getCost().
		std::vector<bool> cr(neurons.size(), true);

		for (int o = 0; o < os; o++) {
			// Because calling getCost() already runs the neural network, we can simply retrieve
			// the output values from the network for finding the residual.
			float residual = outputs.at(o)->getValue(&profiles.at(profile), &profiles.at(profile), &cr) - newExpectedOutputs.at(o);
			float dCost = residual / (outputs.size() * cost);

			// Manually initialize the derivative record for the output neuron.
			// This is needed because the getDerivative() function relies on
			// the neurons having parent connections (which outputs do not have).
			derivRecord.at(is + o).at(0) = dCost;

			outputs.at(o)->getDerivative(&profiles.at(profile), &countRecord, &derivRecord, dCost);
		}
		//----------------------------------------------------------------------------
		// Once derivRecord is complete, add it to the average.

		float scalingConst = 1 / float(batchSize * numParams);
		for (int n = 0; n < neurons.size(); n++) {
			// Original.
			///*
			for (int nc = 0; nc < neurons.at(n).getNumConnections() + 1; nc++)
				avgDerivRecord.at(n).at(nc) -= derivRecord.at(n).at(nc) * scalingConst;
			//*/

			// Using std::transform() is faster but it crashes a lot.
			/*
			std::transform(
				derivRecord[i].begin(), derivRecord[i].end(),
				derivRecord[i].begin(), [scalingConst](float& c) { return c * scalingConst; }
			);

			std::transform(
				derivRecord[i].begin(), derivRecord[i].end(),
				avgDerivRecord[i].begin(), avgDerivRecord[i].begin(), std::minus<float>()
			);
			//*/
		}
	}
	// Update the weights/bias.
	moveMembers(&avgDerivRecord, stepSize);
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
		file.read((char*)&af, sizeof(int));
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
	// TODO: make it clear the file if it already exists.

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

	for (DynamicNeuron n : neurons)
		n.saveConnectionsStatus(&file);

	file.close();
}
//================================================================================
// Profiles.

void DynamicNeuralNetwork::addProfile() {
	profiles.push_back(std::vector<float>(neurons.size(), 0));
}

unsigned int DynamicNeuralNetwork::getNumProfiles() {
	return profiles.size();
}

void DynamicNeuralNetwork::setNumProfiles(unsigned int n) {
	profiles.resize(n);
}
//================================================================================
// Training.

void DynamicNeuralNetwork::moveMembers(std::vector<std::vector<float>>* values, float strength) {
	// First check the size of the first dimension.
	if (values->size() != neurons.size()) {
		std::cout << "\nWARNING: called function moveMembers() with invalid vector size!\n";
		return;
	}

	for (int n = 0; n < neurons.size(); n++) {
		///*
		// Check the size of each secondary list.
		if (values->at(n).size() != neurons.at(n).getNumConnections() + 1) {
			std::cout << "\nWARNING: called function moveMembers() with invalid vector size!\n";
			return;
		}
		//*/
		neurons[n].moveMembers(&values->at(n), strength);
	}
}