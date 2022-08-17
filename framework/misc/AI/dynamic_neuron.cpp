#include "dynamic_neuron.h"
#include <iostream>
#include <random>
#include <cmath> // For inverseNonlinear()

using namespace ActivationFunction;

// Static member definition.
unsigned int DynamicNeuron::idCounter = 0;

//================================================================================
// Constructors.

DynamicNeuron::DynamicNeuron() {

	ID = idCounter;
	idCounter++;

	av = 0;
	finished = false;
	bias = 0;
	af = identity;
	numParents = 0;

	// Placeholder.
	pos.x = 10;
	pos.y = 10;

}

//================================================================================
// Getters & setters.

float DynamicNeuron::getValue() {

	if (finished)
		return av;

	float temp = 0;

	// Mark the node as "done" in case future nodes wish to retrieve its value.
	// It's important to keep this before the for loop to avoid infinite recursion.
	finished = true;

	for (int nc = 0; nc < ncs.size(); nc++) {

		// Weight multiplication is already done in retrieveValue().
		temp += ncs[nc].retrieveValue(true);

	}

	// Add bias and apply nonlinear transform.
	av = temp + bias;
	applyNonlinear();

	// The neuron's activation value is updated regardless, but
	// the old value is returned if `recurse` is set to false.
	return av;

}

void DynamicNeuron::setValue(float v) {

	av = v;

}

void DynamicNeuron::setUndone() {

	finished = false;
	numParents = 0;

}

void DynamicNeuron::setDone() {

	finished = true;

}

unsigned int DynamicNeuron::getNumConnections() {

	return ncs.size();

}

void DynamicNeuron::addConnection(DynamicNeuron* n) {

	ncs.push_back(DynamicNeuralConnection(n));

}

void DynamicNeuron::addConnection(DynamicNeuron* n, float w) {

	ncs.push_back(DynamicNeuralConnection(n, w));

}

unsigned int DynamicNeuron::getID() {

	return ID;

}

DynamicNeuron* DynamicNeuron::getChild(int index) {

	if (index < 0 || index >= ncs.size()) {

		std::cout << "ERROR: called getChild() index out of bounds.\n";

	}
	
	return ncs[index].prevNeuron;

}

float DynamicNeuron::getBias() {

	return bias;

}

void DynamicNeuron::setBias(float b) {

	bias = b;

}

void DynamicNeuron::getDerivative(std::vector<int>* countRecord, std::vector<std::vector<float>>* derivRecord, float dcost_) {

	/*
	* The derivative of the cost with respect to this neuron's activation value
	* is not fully calculated until all parent neurons have recursed to this neuron.
	* After the derivative is "complete" then the neuron can recurse the function to
	* its child connections.
	*/

	// Cost derivative with respect to neuron activation before activation function.
	float preAFDeriv = dcost_ * getAVDerivative();

	// DO NOT shorten to if else, the double if is required for the edge case that
	// countRecord is exactly 1 below completion.
	if (!isComplete(countRecord->at(this->ID))) {

		// Update the thread records.
		countRecord->at(this->ID)++;
		derivRecord->at(this->ID).at(0) += preAFDeriv;

	}

	if (isComplete(countRecord->at(this->ID))) {

		// Derivative w/ respect to bias is the same as w/ respect to av before activation function.
		// No need to do anything for the bias.

		for (int nc = 0; nc < ncs.size(); nc++) {

			// Derivative of cost w/ respect to connection = child neuron value * dervative of cost w/ respect to parent neuron.
			derivRecord->at(this->ID).at(nc + 1) = ncs.at(nc).retrieveValue(false) * derivRecord->at(this->ID).at(0);

			// Derivative of cost w/ respect to child av (after activation function).
			float childDerivative = derivRecord->at(this->ID).at(0) * ncs.at(nc).weight;

			ncs.at(nc).prevNeuron->getDerivative(countRecord, derivRecord, childDerivative);

		}

	}

}

float DynamicNeuron::getAVDerivative() {

	float a, b, c;

	switch (af) {

	case arcHyperTan: return 1 / (1 - av * av);
	case ELU: return (av < 0) ? exp(av) : 1;
	case hyperTan:
		a = tanh(av);
		return 1 - a * a;
	case identity: return 1;
	case mish:
		a = 1 + exp(av);
		b = log(a);
		c = tanh(b);
		return c + av * (1 - c * c) * (a - 1) / a;
	case ReLU: return (av < 0) ? 0 : 1;
	case step: return 0;
	case sigmoid:
		a = 1 + exp(-av);
		return -1 / (a * a);
	case softplus:
		a = exp(av);
		return a / (a + 1);
	case swish:
		a = exp(-av);
		return (1 + a * (av + 1)) / (1 + a) / (1 + a);
	default: return 0;

	}

}

void DynamicNeuron::applyNonlinear() {

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

void DynamicNeuron::setupAverageConnections(float min, float max) {

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

void DynamicNeuron::moveWeight(int index, float value) {

	if (index < 0 || index >= ncs.size()) return;

	ncs[index].weight += value;

	// Manually set finished to false since AV needs to be recalculated.
	finished = false;

}

void DynamicNeuron::moveMembers(std::vector<float>* values, float strength) {

	if (values->size() != ncs.size() + 1) {

		std::cout << "ERROR: called moveMembers() with invalid vector size.\n";
		return;

	}

	bias += values->at(0) * strength;

	for (int val = 0; val < ncs.size(); val++) {

		ncs[val].weight += values->at(val + 1) * strength;

	}

}

void DynamicNeuron::setActivationFunction(ActivationFunction::NonLinearMethod method) {

	af = method;

}

//================================================================================
// numParents

void DynamicNeuron::incrementParent() {

	numParents++;

}

bool DynamicNeuron::isComplete(unsigned int np) {

	return (np >= numParents);

}

void DynamicNeuron::resetNumParents() {

	numParents = 0;

}

//================================================================================
// File handling.

/*
Each neuron is saved to file in the following format:

- Activation Function ID
- Bias
- # of connections to other neurons
	- ID of what neuron to connect to
	- Weight
	- ID of what neuron to connect to
	- Weight
	...

There are no delimiters between neurons as the number of
connections and thus the length is known beforehand.
*/
void DynamicNeuron::saveConnectionsStatus(std::ofstream* file) {

	// Write activation function.
	file->write((char*) &af, sizeof(uint8_t));

	// Write bias.
	file->write((char*) &bias, sizeof(float));

	// Write num connections.
	int size = ncs.size();
	file->write((char*) &size, sizeof(int));

	// Write the actual connections.
	for (DynamicNeuralConnection nc : ncs) {

		unsigned int ID = nc.prevNeuron->getID();
		file->write((char*) &ID, sizeof(unsigned int));
		file->write((char*) &nc.weight, sizeof(float));

	}

}

//================================================================================
// Misc.

void DynamicNeuron::clearValues() {

	values.clear();

}

void DynamicNeuron::resetIDCounter() {

	DynamicNeuron::idCounter = 0;

}