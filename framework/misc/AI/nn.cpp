#include <fstream>
#include <iostream>
#include <math.h>
#include "nn.h"

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

// Runs the neural network and returns the outputs in a list.
std::vector<float> NeuralNetwork::runNeuralNetwork(std::vector<float>* finputs) {

	if (finputs->size() != inputs.size()) {

		std::cout << "input array doesn't match nn inputs! (" << finputs->size() << " vs " << inputs.size() << ")\n";
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

//================================================================================
// File handling.

/*

* The neural network file is quite simple in format. The file beings with the following:
* 
* --------------------------------------------------------------------------------
* # of input neurons "in" (unsigned int)
* # of output neurons "on" (unsigned int)
* # of hidden neurons "hn" (unsigned int)
*
* Then continues on for "in + on + hn" (just the total) number of neurons with each one containing:
*
*	- Type of activation function (enum).
*	- Bias (float).
*	- # of connections to PREVIOUS neurons "numConnections" (unsigned int). Also acts as the # of weights.
*	Then "numConnections" amount of:
* 
*		- ID of previous neuron.
*		- Weight.
* 
* - EOF
* --------------------------------------------------------------------------------

*/

void NeuralNetwork::loadFromFile(std::string fileName) {

	fileName += ".nn";

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
		file.read((char*) &numConnections, sizeof(unsigned int));

		// Read connections.
		for (int c = 0; c < numConnections; c++) {

			unsigned int nID;
			file.read((char*) &nID, sizeof(unsigned int));

			float nWeight;
			file.read((char*) &nWeight, sizeof(float));

			neurons[n].addConnection(&neurons[nID], nWeight);

		}

	}

}