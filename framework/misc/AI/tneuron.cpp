#include "tneuron.h"
#include <random>
#include <cmath> // For inverseNonlinear()

using namespace ActivationFunction;

TrainingNeuron::TrainingNeuron() {

	// No need to do ID handling or anything since it's
	// included in the parent class' constructor.

	// Placeholder.
	pos.x = 10;
	pos.y = 10;

}

//================================================================================
// Getters & setters.

unsigned int TrainingNeuron::getNumConnections() {

	return ncs.size();

}

Neuron* TrainingNeuron::getChild(int index) {

	if (index < 0 || index >= ncs.size()) {

		std::cout << "ERROR: called getChild() index out of bounds.\n";

	}
	
	return ncs[index].prevNeuron;

}

float TrainingNeuron::getBias() {

	return bias;

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
	for (NeuralConnection nc : ncs) {

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
