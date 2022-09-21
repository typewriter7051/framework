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

	bias = 0;
	af = identity;
	numParents = 0;

	// Placeholder.
	pos.x = 10;
	pos.y = 10;

}

//================================================================================
// Getters & setters.

float DynamicNeuron::getValue(std::vector<float>* profile, std::vector<bool>* completionRecord) {

	// Mark the node as "done" in case future nodes wish to retrieve its value.
	// It's important to keep this before the for loop to avoid infinite recursion.
	completionRecord->at(ID) = true;
	float temp = 0;

	for (DynamicNeuron::DynamicNeuralConnection nc : ncs) {

		int prevID = nc.prevNeuron->getID();
		bool isComplete = completionRecord->at(prevID);

		if (!isComplete)
			nc.prevNeuron->getValue(profile, completionRecord);

		temp += profile->at(prevID) * nc.weight;

	}

	// Add bias and apply nonlinear transform.
	profile->at(ID) = temp + bias;
	applyNonlinear(profile);

	return profile->at(ID);

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

float DynamicNeuron::getBias() {

	return bias;

}

void DynamicNeuron::setBias(float b) {

	bias = b;

}

float DynamicNeuron::getAvgConnection() {

	float avg = 0;
	for (int nc = 0; nc < ncs.size(); nc++) {

		avg += abs(ncs.at(nc).weight) / float(ncs.size());

	}

	return avg;

}

void DynamicNeuron::getDerivative(std::vector<float>* profile, std::vector<int>* countRecord, std::vector<std::vector<float>>* derivRecord, float dcost_) {

	/*
	* The derivative of the cost with respect to this neuron's activation value
	* is not fully calculated until all parent neurons have recursed to this neuron.
	* After the derivative is "complete" then the neuron can recurse the function to
	* its child connections.
	*/

	// Cost derivative with respect to neuron activation before activation function.
	float preAFDeriv = dcost_ * getAVDerivative(profile);

	// DO NOT shorten to if else, the double if is required for the edge case that
	// countRecord is exactly 1 below completion.
	if (countRecord->at(this->ID) < numParents) {

		// Update the thread records.
		countRecord->at(this->ID)++;
		derivRecord->at(this->ID).at(0) += preAFDeriv;

	}

	if (countRecord->at(this->ID) >= numParents) {

		// Derivative w/ respect to bias is the same as w/ respect to av before activation function.
		// No need to do anything for the bias.

		for (int nc = 0; nc < ncs.size(); nc++) {

			// Derivative of cost w/ respect to connection = child neuron value * dervative of cost w/ respect to parent neuron.
			derivRecord->at(this->ID).at(nc + 1) = profile->at(ncs.at(nc).prevNeuron->getID()) * derivRecord->at(this->ID).at(0);

			// Derivative of cost w/ respect to child av (after activation function).
			float childDerivative = derivRecord->at(this->ID).at(0) * ncs.at(nc).weight;

			ncs.at(nc).prevNeuron->getDerivative(profile, countRecord, derivRecord, childDerivative);

		}

	}

}

float DynamicNeuron::getAVDerivative(std::vector<float>* profile) {

	float a, b, c;
	float av = profile->at(ID);

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

void DynamicNeuron::applyNonlinear(std::vector<float>* profile) {

	float av = profile->at(ID);

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
	for (int nc = 0; nc < ncs.size(); nc++)
		ncs[nc].weight = (*dis)(rng) / float(ncs.size());

	// Randomize the bias.
	rng.seed(ID);
	bias = (*dis)(rng);

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

void DynamicNeuron::incrementChildParents(std::vector<bool>* completionRecord) {

	if ((*completionRecord)[ID]) return;

	// Mark the node as "done" in case future nodes wish to retrieve its value.
	// It's important to keep this before the for loop to avoid infinite recursion.
	(*completionRecord)[ID] = true;

	for (int nc = 0; nc < ncs.size(); nc++) {

		// Weight multiplication is already done in retrieveValue().
		ncs[nc].incrementChildParent(completionRecord);

	}

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
	file->write((char*) &af, sizeof(int));

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

void DynamicNeuron::resetIDCounter() {

	DynamicNeuron::idCounter = 0;

}

void DynamicNeuron::decrementID() {

	ID--;

}

void DynamicNeuron::decrementConnections(unsigned int ID) {

	for (int nc = 0; nc < ncs.size(); nc++) {

		if (ncs.at(nc).prevNeuron->getID() > ID)
			ncs.at(nc).prevNeuron--;

	}

}

// Deletes the connection to a specific neuron if it exists.
// Also updates the connection ID of neurons whose position changed during the removal.
void DynamicNeuron::removeConnection(unsigned int neuronID) {

	// Delete connection to specific neuron.
	for (int nc = 0; nc < ncs.size(); nc++) {

		if (ncs.at(nc).prevNeuron->getID() == neuronID)
			ncs.erase(ncs.begin() + nc);

	}

	// Should not need to update numParents since the backprop is already over when this is called.

}

// Deletes any connections under a threshold.
void DynamicNeuron::removeDeadConnections(float threshold) {

	for (int nc = 0; nc < ncs.size(); nc++) {

		if (abs(ncs.at(nc).weight) < threshold) {

			//std::cout << "removing connection with value of " << ncs.at(nc).weight << std::endl;
			ncs.erase(ncs.begin() + nc);

		}

	}

}