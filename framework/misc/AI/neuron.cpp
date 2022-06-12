#include "neuron.h"
#include <time.h>
#include <memory>
#include <cmath>

using namespace ActivationFunction;

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
	af = identity;

}

unsigned int Neuron::getID() {

	return ID;

}

// If recurse is set to false, the neuron will simply return it's previous/un-updated activation value.
// This is used so that some neurons can have a recursive (memory) connection.

// Recursive feedback connections can still function expectedly if the child neuron already has "finished" status when such recursive neuron is reached.
float Neuron::getValue(bool recurse) {

	if (finished)
		return av;

	float temp = 0, avReturn = av;

	// Mark the node as "done" in case future nodes wish to retrieve its value.
	// It's important to keep this before the for loop to avoid infinite recursion.
	finished = true;

	for (int nc = 0; nc < ncs.size(); nc++) {

		// Weight multiplication is already done in retrieveValue().
		temp += ncs[nc].retrieveValue();

	}

	// Add bias and apply nonlinear transform.
	av = temp + bias;
	applyNonlinear();

	// The neuron's activation value is updated regardless, but
	// the old value is returned if `recurse` is set to false.
	return (recurse) ? av : avReturn;

}

std::vector<Neuron*> Neuron::getConnections() {

	std::vector<Neuron*> returnList;

	for (NeuralConnection nc : ncs) {

		returnList.push_back(nc.getPrevNeuron());

	}

	return returnList;

}

void Neuron::setValue(float f) {

	av = f;

	finished = false;

}

void Neuron::moveValue(float v, float strength) {

	av += v * strength;

	// Ensures that the neuron directly returns activation value without calling connected neurons.
	finished = true;

}

void Neuron::setBias(float b) {

	bias = b;

}

void Neuron::moveBias(float b) {

	bias += b;

	finished = false;

}

void Neuron::setActivationFunction(ActivationFunction::NonLinearMethod a) {

	af = a;

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

	switch (af) {

	case arcHyperTan: av = atanh(av); break;
	case ELU: av = (av < 0) ? exp(av) - 1 : av; break;
	case hyperTan: av = tanh(av); break;
	case identity:; break;
	case mish: av = av * tanh( log(1 + exp(av)) );
	case ReLU: av = (av < 0) ? 0 : av; break;
	case step: av = (av < 0) ? 0 : 1; break;
	case sigmoid: av = 1 / (1 + exp(-av)); break;
	case softplus: av = log(1 + exp(av)); break;
	case swish: av = av / (1 + exp(-av)); break;
	default:; break;

	}

}

void Neuron::resetIDCounter() {

	idCounter = 0;

}
