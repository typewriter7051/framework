#include "neuron.h"
#include <random>
#include <time.h>

// Static member definition.
unsigned int Neuron::idCounter = 0;

//================================================================================
// Constructors.

Neuron::Neuron() {

	ID = idCounter;
	idCounter++;

	av = 0;
	finished = false;
	bias = 0;

}

//================================================================================
// Getters & setters.

float Neuron::getValue() {

	float temp = 0;

	if (finished)
		return av;

	else {

		// Mark the node as "done" in case future nodes wish to retrieve its value.
		// It's important to keep this before the for loop to avoid infinite recursion.
		finished = true;

		for (int nc = 0; nc < ncs.size(); nc++) {

			// Weight multiplication is already done in retrieveValue().
			temp += ncs[nc].retrieveValue();

		}

	}

	// Add bias and apply nonlinear transform.
	av = temp + bias;
	applyNonlinear();

	return av;

}

unsigned int Neuron::getID() {

	return ID;

}

unsigned int Neuron::getNumConnections() {

	return ncs.size();

}

std::vector<Neuron*> Neuron::getConnections() {

	std::vector<Neuron*> returnList;

	for (NeuralConnection nc : ncs) {

		returnList.push_back(nc.prevNeuron);

	}

	return returnList;

}

float Neuron::getBias() {

	return bias;

}

void Neuron::setBias(float b) {

	bias = b;

}

void Neuron::setValue(float f) {

	av = f;

	// Ensures that the neuron directly returns activation value without calling connected neurons.
	finished = true;

}

// Clears finished status for next iteration.
void Neuron::setUndone() {

	finished = false;

}

void Neuron::setDone() {

	finished = true;

}

void Neuron::setupAverageConnections(float min, float max) {
	
	std::mt19937 rng;
	std::unique_ptr<std::uniform_real_distribution<float>> dis;
	dis = std::make_unique<std::uniform_real_distribution<float>>(min, max);

	for (int nc = 0; nc < ncs.size(); nc++) {

		rng.seed(ID * ncs[nc].prevNeuron->getID());
		ncs[nc].weight = (*dis)(rng);

	}

}

void Neuron::setConnections(std::vector<float> values, float strength) {

	if (values.size() != ncs.size()) {

		std::cout << "YOU STUPID";
		return;

	}

	for (int val = 0; val < ncs.size(); val++) {

		ncs[val].weight = ncs[val].weight * (1 - strength) + values[val] * strength;

	}

}

//================================================================================
// File handling.

void Neuron::saveConnectionsStatus(std::ofstream* file) {

	//*file << ncs.size() << "\n";
	int size = ncs.size();
	file->write((char*) &size, sizeof(int));

	for (NeuralConnection nc : ncs) {

		//*file << nc.prevNeuron->getID() << "\n" << nc.weight << "\n";
		unsigned int ID = nc.prevNeuron->getID();
		file->write((char*) &ID, sizeof(unsigned int));
		file->write((char*) &nc.weight, sizeof(float));

	}

}

//================================================================================
// Misc.

void Neuron::addConnection(Neuron* n) {

	ncs.push_back(NeuralConnection(n));

}

void Neuron::addConnection(Neuron* n, float w) {

	ncs.push_back(NeuralConnection(n, w));

}

void Neuron::clearValues() {

	values.clear();

}

void Neuron::resetIDCounter() {

	idCounter = 0;

}

void Neuron::applyNonlinear() {

	av = tanh(av);

}