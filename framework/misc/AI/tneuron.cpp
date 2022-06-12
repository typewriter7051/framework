#include "tneuron.h"
#include <iostream>
#include <random>
#include <cmath> // For inverseNonlinear()

using namespace ActivationFunction;

TrainingNeuron::TrainingNeuron() {

	// No need to do ID handling or anything since it's
	// included in the parent class' constructor.

	// Placeholder.
	pos.x = 10;
	pos.y = 10;

	numParents = 0;
	dCost = 0;

}

//================================================================================
// Getters & setters.

float TrainingNeuron::getValue(bool recurse) {

	if (recurse) numParents++;

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

void TrainingNeuron::setValue(float v) {

	av = v;

}

void TrainingNeuron::setUndone() {

	finished = false;

}

void TrainingNeuron::setDone() {

	finished = true;

}

unsigned int TrainingNeuron::getNumConnections() {

	return ncs.size();

}

void TrainingNeuron::addConnection(TrainingNeuron* n) {

	ncs.push_back(TrainingNeuralConnection(n));

}

void TrainingNeuron::addConnection(TrainingNeuron* n, float w) {

	ncs.push_back(TrainingNeuralConnection(n, w));

}

unsigned int TrainingNeuron::getID() {

	return ID;

}

TrainingNeuron* TrainingNeuron::getChild(int index) {

	if (index < 0 || index >= ncs.size()) {

		std::cout << "ERROR: called getChild() index out of bounds.\n";

	}
	
	return ncs[index].prevNeuron;

}

float TrainingNeuron::getBias() {

	return bias;

}

void TrainingNeuron::setBias(float b) {

	bias = b;

}

void TrainingNeuron::getDerivative(std::vector<int>* countRecord, std::vector<float>* derivRecord, float dcost_) {

	/*
	* The derivative of the cost with respect to this neuron's activation value
	* is not fully calculated until all parent neurons have recursed to this neuron.
	* After the derivative is "complete" then the neuron can recurse the function to
	* its child connections.
	*/

	// Cost derivative with respect to neuron before nonlinear activation function.
	float preAFDeriv = dcost_ * getAVDerivative();

	if (!isComplete(countRecord->at(this->ID))) {

		// Update the thread records.
		countRecord->at(this->ID)++;
		derivRecord->at(this->ID) += preAFDeriv;

	}

	// DO NOT shorten to if else, the double if is required for the edge case that
	// countRecord is exactly 1 below completion.
	if (isComplete(countRecord->at(this->ID))) {

		for (TrainingNeuralConnection nc : ncs) {

			float childDerivative = preAFDeriv * nc.weight;

			nc.prevNeuron->getDerivative(countRecord, derivRecord, childDerivative);

		}

	}

}

float TrainingNeuron::getAVDerivative() {

	switch (af) {

	case arcHyperTan: return 1 / (1 - av * av);
	case ELU: return (av < 0) ? exp(av) : 1;
	case hyperTan:
		float temp = tanh(av);
		return 1 - temp * temp;
	case identity: return 1;
	case mish:
		float a = 1 + exp(av);
		float b = log(a);
		float c = tanh(b);
		return c + av * (1 - c * c) * (a - 1) / a;
	case ReLU: return (av < 0) ? 0 : 1;
	case step: return 0;
	case sigmoid:
		float temp = 1 + exp(-av);
		return -1 / temp / temp;
	case softplus:
		float a = exp(av);
		return a / (a + 1);
	case swish:
		a = exp(-av);
		return (1 + a * (av + 1)) / (1 + a) / (1 + a);
	default: return 0;

	}

}

void TrainingNeuron::applyNonlinear() {

	switch (af) {

	case arcHyperTan: av = atanh(av); break;
	case ELU: av = (av < 0) ? exp(av) - 1 : av; break;
	case hyperTan: av = tanh(av); break;
	case identity:; break;
	case mish: av = av * tanh(log(1 + exp(av)));
	case ReLU: av = (av < 0) ? 0 : av; break;
	case step: av = (av < 0) ? 0 : 1; break;
	case sigmoid: av = 1 / (1 + exp(-av)); break;
	case softplus: av = log(1 + exp(av)); break;
	case swish: av = av / (1 + exp(-av)); break;
	default:; break;

	}

}

void TrainingNeuron::setupAverageConnections(float min, float max) {

	// Set up rng.
	std::mt19937 rng;
	std::unique_ptr<std::uniform_real_distribution<float>> dis;
	dis = std::make_unique<std::uniform_real_distribution<float>>(min, max);

	// Randomize weights.
	for (int nc = 0; nc < ncs.size(); nc++) {

		rng.seed(ID * ncs[nc].prevNeuron->getID());
		ncs[nc].weight = (*dis)(rng) / float(ncs.size());

	}

	// Randomize the bias.
	rng.seed(ID);
	bias = (*dis)(rng);

}

void TrainingNeuron::moveWeight(int index, float value) {

	if (index < 0 || index >= ncs.size()) return;

	ncs[index].weight += value;

	// Manually set finished to false since AV needs to be recalculated.
	finished = false;

}

void TrainingNeuron::moveMembers(std::vector<float>* values, float strength) {

	if (values->size() != ncs.size() + 1) {

		std::cout << "ERROR: called moveMembers() with invalid vector size.\n";
		return;

	}

	for (int val = 0; val < ncs.size(); val++) {

		ncs[val].weight += values->at(val) * strength;

	}

	bias += values->back() * strength;

	if (abs(bias) > 1) {

		int asdf = 0;
		asdf += 1;

	}

}

void TrainingNeuron::setActivationFunction(ActivationFunction::NonLinearMethod method) {

	af = method;

}

//================================================================================
// numParents

void TrainingNeuron::incrementParent() {

	numParents++;

}

bool TrainingNeuron::isComplete(unsigned int np) {

	return (np >= numParents);

}

void TrainingNeuron::resetNumParents() {

	numParents = 0;

}

//================================================================================
// File handling.

void TrainingNeuron::saveConnectionsStatus(std::ofstream* file) {

	// Write activation function.
	file->write((char*) &af, sizeof(uint8_t));

	// Write bias.
	file->write((char*)&bias, sizeof(float));

	// Write num connections.
	int size = ncs.size();
	file->write((char*) &size, sizeof(int));

	// Write the actual connections.
	for (TrainingNeuralConnection nc : ncs) {

		unsigned int ID = nc.prevNeuron->getID();
		file->write((char*) &ID, sizeof(unsigned int));
		file->write((char*) &nc.weight, sizeof(float));

	}

}

//================================================================================
// Misc.

void TrainingNeuron::clearValues() {

	values.clear();

}

void TrainingNeuron::resetIDCounter() {

	idCounter = 0;

}