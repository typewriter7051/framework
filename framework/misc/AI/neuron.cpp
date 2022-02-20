#include "neuron.h"
#include <time.h>
#include <memory>
#include <cmath>

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

unsigned int Neuron::getID() {

	return ID;

}

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

std::vector<Neuron*> Neuron::getConnections() {

	std::vector<Neuron*> returnList;

	for (NeuralConnection nc : ncs) {

		returnList.push_back(nc.prevNeuron);

	}

	return returnList;

}

void Neuron::setValue(float f) {

	av = f;

	// Ensures that the neuron directly returns activation value without calling connected neurons.
	finished = true;

}

void Neuron::setDone() {

	finished = true;

}

// Clears finished status for next iteration.
void Neuron::setUndone() {

	finished = false;

}

void Neuron::addConnection(Neuron* n) {

	ncs.push_back(NeuralConnection(n));

}

void Neuron::addConnection(Neuron* n, float w) {

	ncs.push_back(NeuralConnection(n, w));

}

void Neuron::applyNonlinear() {

	//av = tanh(av);

}

void Neuron::resetIDCounter() {

	idCounter = 0;

}
